/*************************************************************************
【文件名】                 checktranslation.cpp
【功能模块和目的】          CheckTranslation类实现
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/


#include "checktranslation.h"
#include "ui_checktranslation.h"
#include "lastsubmittal.h"
#include "cfmdialog.h"
#include <QDebug>
#include <QMessageBox>


/*************************************************************************
【函数名称】       CheckTranslation
【函数功能】       CheckTranslation类构造函数 构造该页面
【参数】
                  QWidget* parent               输入
                  P_MNG    mng                  输入
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
CheckTranslation::CheckTranslation(QWidget* parent, P_MNG mng) :
    QMainWindow(parent),
    ui(new Ui::CheckTranslation),
    mng(mng)
{
    ui->setupUi(this);
    connect(ui->return_2, &QPushButton::clicked, this,
            &CheckTranslation::ReturnLast2);
    TranslatorInitialize();
    TableInitialize();
    connect(ui->accept, &QPushButton::clicked, this,
            &CheckTranslation::AcceptTranslation);
}


/*************************************************************************
【函数名称】       ~CheckTranslation
【函数功能】       CheckTranslation类析构函数
【参数】           void
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
CheckTranslation::~CheckTranslation()
{
    delete ui;
}


/*************************************************************************
【函数名称】       TranslatorInitialize
【函数功能】       翻译者列表初始化
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void CheckTranslation::TranslatorInitialize()
{
    int rowNum = static_cast<int>(mng->GetSubMissions().size());
    ui->translators->setRowCount(rowNum);
    ui->translators->setColumnCount(2);      //translator, subMstate
    ui->translators->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->translators->horizontalHeader()->setSectionResizeMode(1,
            QHeaderView::ResizeToContents);
    ui->translators->verticalHeader()->setSectionResizeMode(
        QHeaderView::Interactive);
    ui->translators->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->translators->setSelectionBehavior (
        QAbstractItemView::SelectRows);               //设置选择行为，以行为单位
    ui->translators->setSelectionMode (
        QAbstractItemView::SingleSelection);              //设置选择模式，选择单行

    QStringList header;
    header << "" << "Translation State";
    ui->translators->setHorizontalHeaderLabels(header);

    for (ULL i = 0; i != static_cast<ULL>(mng->GetSubMissions().size()); i++)
    {
        P_SUB sub = mng->GetSubMissions()[i];

        if (!sub.exist())
        {
            qDebug() << "Error : mng->subMissions[i] doesn't exist! ";
            continue;
        }

        ui->translators->setItem(static_cast<int>(i), 0,
                                 new QTableWidgetItem(QString::fromStdString(sub->GetTranslator() ) ) );
        ui->translators->setItem(static_cast<int>(i), 1,
                                 new QTableWidgetItem(QString::fromStdString(sub->GetSubMissionStateStr() ) ) );
    }

    ui->translators->selectRow(0);
    connect(ui->translators, &QTableWidget::itemSelectionChanged, this,
            &CheckTranslation::TableInitialize);

    //最终提交
    ui->complete->setVisible(CompleteVisible());

    if (CompleteVisible())
    {
        connect(ui->complete, &QPushButton::clicked, this,
                &CheckTranslation::LastSubmit);
    }
}


/*************************************************************************
【函数名称】       TableInitialize
【函数功能】       其他位置初始化
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void CheckTranslation::TableInitialize()
{
    ULL crtId = 0;

    if (ui->translators->currentRow() >= 0)
    {
        crtId = static_cast<ULL>(ui->translators->currentRow());
    }

    ui->srcSubText->setReadOnly(true);
    crtSub = mng->GetSubMissions()[crtId];
    ui->srcSubText->setPlainText(QString::fromStdString(crtSub->GetSrcSubText() ) );
    edit1 = new QPlainTextEdit;

    for (int i = ui->feedbackTable->rowCount() - 1; i >= 0  ; i--)
    {
        ui->feedbackTable->removeRow(i);
    }

    int rowNum = static_cast<int>(crtSub->GetHistory().size() + 1);
    ui->feedbackTable->setRowCount(rowNum);
    ui->feedbackTable->setColumnCount(2);      //my translation, manager feedback
    ui->feedbackTable->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Stretch);
    ui->feedbackTable->verticalHeader()->setSectionResizeMode(
        QHeaderView::Interactive);
    ui->feedbackTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QStringList header;
    header << "Translation" << "Feedback";
    ui->feedbackTable->setHorizontalHeaderLabels(header);

    SubMission::SubMissionState s = crtSub->GetSubMissionState();

    if (s == SubMission::T_WAIT_FOR_TRANS)
    {
        ui->feedbackTable->setItem(0, 0,
                                   new QTableWidgetItem( "No translation has been submitted."));
        edit1->setReadOnly(true);
    }
    else if (s == SubMission::T_WAIT_FOR_MODIFY || s == SubMission::T_ACCEPTED)
    {
        std::vector<KEY_SUB> history = crtSub->GetHistory();
        for (ULL i = 0; i != static_cast<ULL>(history.size()); i++)
        {
            ui->feedbackTable->setItem(static_cast<int>(i), 0,
                new QTableWidgetItem(QString::fromStdString(history[i].first) ) );
            ui->feedbackTable->setItem(static_cast<int>(i), 1,
                new QTableWidgetItem(QString::fromStdString(history[i].second) ) );
        }

        edit1->setReadOnly(true);
    }
    else if (s == SubMission::T_SUBMITTED)
    {
        std::vector<KEY_SUB> history = crtSub->GetHistory();
        for (ULL i = 0; i != static_cast<ULL>(history.size() - 1); i++)
        {
            ui->feedbackTable->setItem(static_cast<int>(i), 0,
                new QTableWidgetItem(QString::fromStdString(history[i].first) ) );
            ui->feedbackTable->setItem(static_cast<int>(i), 1,
                new QTableWidgetItem(QString::fromStdString(history[i].second) ) );
        }

        std::string trans = history[history.size() - 1].first;
        ui->feedbackTable->setItem(static_cast<int>(history.size() - 1), 0,
                                   new QTableWidgetItem(QString::fromStdString(trans) ) );

        ui->feedbackTable->setCellWidget(static_cast<int>(history.size() - 1),
                                         1, edit1);

        QPushButton* btn = new QPushButton("反馈");
        ui->feedbackTable->setCellWidget(static_cast<int>(history.size()) , 1,
                                         btn);
        connect(btn, &QPushButton::clicked, this, &CheckTranslation::SetFeedback);
    }

}


/*************************************************************************
【函数名称】       SetFeedback
【函数功能】       设置反馈
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void CheckTranslation::SetFeedback()
{
    std::string feedbk = edit1->document()->toPlainText().toStdString();

    if (feedbk == "")
    {
        QMessageBox* warn = new QMessageBox(QMessageBox::Warning, "Notice",
            "Feed back is empty!",
            QMessageBox::Yes, this);
        warn->show();
    }
    else if(edit1->document()->toPlainText().contains(QRegExp("[()\"#|;]")))
    {
        QMessageBox* warn = new QMessageBox(QMessageBox::Warning, "Warning",
            "Feedback cannot contain special symbols : \n\
            ()\"#|;", QMessageBox::Ok, this);
        warn->show();
    }
    else
    {
        Platform::m_submit_feedback(crtSub->GetManager(), crtSub, feedbk);
        edit1->setPlainText("");
        ui->feedbackTable->removeCellWidget(
            static_cast<int>(crtSub->GetHistory().size() -1), 1);

        TranslatorInitialize();
        TableInitialize();
    }
}


/*************************************************************************
【函数名称】       AcceptTranslation
【函数功能】       接受译文
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void CheckTranslation::AcceptTranslation()
{
    SubMission::SubMissionState s = crtSub->GetSubMissionState();

    if (s == SubMission::T_ACCEPTED || s == SubMission::T_SUBMITTED ||
        s == SubMission::T_WAIT_FOR_TRANS)
    {
        QMessageBox* warn = new QMessageBox(QMessageBox::Warning, "Notice",
            "Cannot accept anything on this page.",
            QMessageBox::Yes, this);
        warn->show();
    }
    else
    {
        CfmDialog* confirm = new CfmDialog(this, this,
            "Are you sure to accept the last version of the current\
            Translator? \n Your operation cannot be canceled.");
        confirm->show();
        connect(confirm, &CfmDialog::s_confirmed, this,
                &CheckTranslation::AcceptSucceed);
    }
}


/*************************************************************************
【函数名称】       AcceptSucceed
【函数功能】       接受译文成功
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void CheckTranslation::AcceptSucceed(CfmDialog* cfmpge)
{
    qDebug() << "Accept succeed.";
    Platform::m_accept_translation(mng->GetManager(), crtSub);

    if (cfmpge != nullptr)
    {
        cfmpge->close();
    }

    TranslatorInitialize();
    TableInitialize();
}


/*************************************************************************
【函数名称】       CompleteVisible
【函数功能】       判断完成按钮可见性
【参数】           void
【返回值】         bool 表示完成按钮是否可见
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
bool CheckTranslation::CompleteVisible()
{
    for (ULL i = 0; i != mng->GetSubMissions().size(); i++)
    {
        P_SUB temp = mng->GetSubMissions()[i];

        if (temp->GetSubMissionState() != SubMission::T_ACCEPTED)
        {
            return false;
        }
    }

    return true;
}


/*************************************************************************
【函数名称】       LastSubmit
【函数功能】       进入最终提交译文页
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void CheckTranslation::LastSubmit()
{
    LastSubmittal* nxtpge = new LastSubmittal(this, mng);
    nxtpge->show();
    this->hide();
    connect(nxtpge, &LastSubmittal::s_returnLast, this,
            &CheckTranslation::ReturnLast);

}


/*************************************************************************
【函数名称】       ReturnLast
【函数功能】       返回上一页并关闭下一页面
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void CheckTranslation::ReturnLast(LastSubmittal* nxtpge)
{
    this->show();
    nxtpge->close();
    emit s_return(this);
}


/*************************************************************************
【函数名称】       ReturnLast2
【函数功能】       仅返回上一页
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void CheckTranslation::ReturnLast2()
{
    emit s_return(this);
}

