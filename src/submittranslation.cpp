/*************************************************************************
【文件名】                 submittranslation.cpp
【功能模块和目的】          SubmitTranslation类实现
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/


#include "submittranslation.h"
#include "ui_submittranslation.h"
#include "QMessageBox"
#include <QDebug>


/*************************************************************************
【函数名称】        SubmitTranslation
【函数功能】        SubmitTranslation类构造函数 构造该页面
【参数】
                  QWidget* parent               输入
                  P_SUB subMission              输入
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
SubmitTranslation::SubmitTranslation(QWidget* parent, P_SUB subMission) :
    QMainWindow(parent),
    ui(new Ui::SubmitTranslation),
    subMission(subMission)
{
    ui->setupUi(this);
    connect(ui->return_2, &QPushButton::clicked, this,
            &SubmitTranslation::ReturnLast);
    ui->srcSubText->setPlainText(QString::fromStdString(
                                     subMission->GetSrcSubText() ) );
    ui->srcSubText->setReadOnly(true);
    TableInitialize();
    connect(ui->submit, &QPushButton::clicked, this,
            &SubmitTranslation::SubmitClicked);

}


/*************************************************************************
【函数名称】        ~SubmitTranslation
【函数功能】        SubmitTranslation类析构函数
【参数】           void
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
SubmitTranslation::~SubmitTranslation()
{
    delete ui;
}


/*************************************************************************
【函数名称】        TableInitialize
【函数功能】        表格初始化
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void SubmitTranslation::TableInitialize()
{
    edit1 = new QPlainTextEdit;

    for (int i = ui->submitTable->rowCount() - 1; i >= 0  ; i--)
    {
        ui->submitTable->removeRow(i);
    }

    int rowNum = 0;
    SubMission::SubMissionState s = subMission->GetSubMissionState();
    std::vector<KEY_SUB> history = subMission->GetHistory();

    if (s == SubMission::T_WAIT_FOR_MODIFY || s == SubMission::T_WAIT_FOR_TRANS)
    {
        rowNum = static_cast<int>(history.size() + 1);
    }
    else
    {
        rowNum = static_cast<int>(history.size());
        ui->submit->setEnabled(false);
        edit1->setReadOnly(true);
    }

    ui->submitTable->setRowCount(rowNum);
    ui->submitTable->setColumnCount(2);      //my translation, manager feedback
    ui->submitTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->submitTable->verticalHeader()->setSectionResizeMode(
        QHeaderView::Interactive);
    ui->submitTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QStringList header;
    header << "My Translation" << "Manager Feedback";
    ui->submitTable->setHorizontalHeaderLabels(header);

    for (ULL i = 0; i != static_cast<ULL>(history.size()); i++)
    {
        ui->submitTable->setItem(static_cast<int>(i), 0,
            new QTableWidgetItem(QString::fromStdString(history[i].first) ) );
        ui->submitTable->setItem(static_cast<int>(i), 1,
            new QTableWidgetItem(QString::fromStdString(history[i].second) ) );
    }

    if (s == SubMission::T_WAIT_FOR_MODIFY || s == SubMission::T_WAIT_FOR_TRANS)
    {

        ui->submitTable->setCellWidget(static_cast<int>(history.size()),
                                       0, edit1);
        QPlainTextEdit* edit2 = new QPlainTextEdit;
        edit2->setEnabled(false);
        ui->submitTable->setCellWidget(static_cast<int>(history.size()),
                                       1, edit2);
    }

}


/*************************************************************************
【函数名称】        SubmitClicked
【函数功能】        提交按钮响应
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void SubmitTranslation::SubmitClicked()
{

    if(subMission->GetSubMissionState() == SubMission::T_SUBMITTED ||
            subMission->GetSubMissionState() == SubMission::T_ACCEPTED)
    {
        QMessageBox* warn = new QMessageBox(QMessageBox::Warning, "Notice",
            "Nothing can be submitted now.",
            QMessageBox::Yes, this);
        warn->show();
    }
    else if (edit1->document()->isEmpty())
    {
        QMessageBox* warn = new QMessageBox(QMessageBox::Warning, "Notice",
            "You have entered nothing yet.",
            QMessageBox::Yes, this);
        warn->show();
    }
    else if(edit1->document()->toPlainText().contains(QRegExp("[()\"#|;]")))
    {
        QMessageBox* warn = new QMessageBox(QMessageBox::Warning, "Warning",
            "Translation cannot contain special symbols : \n\
            ()\"#|;", QMessageBox::Ok, this);
        warn->show();
    }
    else
    {
        std::string s = edit1->document()->toPlainText().toStdString();
        KEY_SUB key(this->subMission->GetMissionName(),
                    this->subMission->GetTranslator() );
        Platform::t_submit_translation(this->subMission->GetTranslator(), key, s);

        QMessageBox* succeed = new QMessageBox(QMessageBox::Information, "Notice",
            "Submit Succeed.\n You can view the submission status on your home page.",
            QMessageBox::Ok, this);
        succeed->show();
        TableInitialize();
    }
}

/*************************************************************************
【函数名称】        ReturnLast
【函数功能】        返回上一页面
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void SubmitTranslation::ReturnLast()
{
    emit s_return(this);
}

