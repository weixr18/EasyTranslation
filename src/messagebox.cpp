#include "messagebox.h"
#include "ui_messagebox.h"
#include <QMessageBox>

MessageBox::MessageBox(QWidget *parent, P_USER user) :
    QMainWindow(parent),
    ui(new Ui::MessageBox),
    user(user)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this, &MessageBox::ReturnLast);
    TableInitialize();
}

MessageBox::~MessageBox()
{
    delete ui;
}

void MessageBox::GetUserMessages()
{
    userMessages.clear();

    std::vector<int> temp = Datum::SearchMessages(user->GetUserName());
    for (auto id : temp)
    {
        if (Datum::MessageIdExist(id))
        {
            Message msg;
            Datum::GetMessageByID(id, msg);
            userMessages.push_back(msg);
        }
    }

}

void MessageBox::TableInitialize()
{
    GetUserMessages();
    int rowNum = static_cast<int>(userMessages.size());
    ui->messages->setRowCount(rowNum);
    ui->messages->setColumnCount(4);
    ui->messages->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->messages->horizontalHeader()->setSectionResizeMode(0,
            QHeaderView::ResizeToContents);
    ui->messages->horizontalHeader()->setSectionResizeMode(2,
            QHeaderView::ResizeToContents);
    ui->messages->horizontalHeader()->setSectionResizeMode(3,
            QHeaderView::ResizeToContents);
    ui->messages->verticalHeader()->setSectionResizeMode(
        QHeaderView::Interactive);
    ui->messages->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QStringList header;
    header << "Sender" << "Content" << "Send Time" << "Read";
    ui->messages->setHorizontalHeaderLabels(header);

    for (ULL i = 0; i < userMessages.size(); i++)
    {
        Message msg = userMessages[i];

        if (msg.GetID() > -1)
        {
            ui->messages->setItem(static_cast<int>(i), 0,
                new QTableWidgetItem(QString::fromStdString(msg.GetSender() ) ) );
            ui->messages->setItem(static_cast<int>(i), 1,
                new QTableWidgetItem(QString::fromStdString(msg.GetContent() ) ) );

            //此处的grid显示的是截止时间
            std::string time = Mission::TimeToString(msg.GetSendTime() );
            ui->messages->setItem(static_cast<int>(i), 2,
                new QTableWidgetItem(QString::fromStdString(time) ) );

            //操作按钮
            QPushButton* opr = new QPushButton;
            opr->setText("Set Read.");
            opr->setStyleSheet("QPushButton{background-color:white;}");
            opr->setProperty("MessageID", QString::number(msg.GetID()));
            if (msg.GetReadState())
            {
                opr->setEnabled(false);
            }
            connect(opr, &QPushButton::clicked, this, &MessageBox::ReadMessage);
            ui->messages->setCellWidget(static_cast<int>(i), 3, opr);
        }
    }

    ui->messages->resizeRowsToContents();
}


void MessageBox::ReadMessage()
{
    QObject* obj = sender();
    int id = obj->property("MessageID").toInt();
    if (id > -1)
    {
        QMessageBox* cfm = new QMessageBox(QMessageBox::Question, "Confirm",
            "Set this message read. Continue?",
            QMessageBox::Yes | QMessageBox::No, this);
        cfm->show();

        connect(cfm, &QMessageBox::rejected, cfm, &QMessageBox::close);
        cfm->setProperty("MessageID", QString::number(id));
        connect(cfm, &QMessageBox::accepted, this, &MessageBox::ReadMessageSuccess);
    }
}

void MessageBox::ReadMessageSuccess()
{
    QObject* obj = sender();
    int id = obj->property("MessageID").toInt();

    Datum::ReadMessage(id);
    TableInitialize();
    this->repaint();
}


void MessageBox::ReturnLast()
{
    emit s_returnLast();
}


