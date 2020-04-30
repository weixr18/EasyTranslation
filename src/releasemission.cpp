/*************************************************************************
【文件名】                 releasemission.cpp
【功能模块和目的】          ReleaseMission类实现
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/


#include "releasemission.h"
#include "ui_releasemission.h"
#include "Datum.h"
#include <QDebug>

/*************************************************************************
【函数名称】        ReleaseMission
【函数功能】        ReleaseMission类构造函数 构造该页面
【参数】
                  QWidget*             parent      输入
                  P_USER               user        输入
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
ReleaseMission::ReleaseMission(QWidget* parent, P_USER user) :
    QMainWindow(parent),
    ui(new Ui::ReleaseMission),
    user(user),
    m_srcBtnGrp(new QButtonGroup),
    m_tarBtnGrp(new QButtonGroup)
{
    ui->setupUi(this);
    connect(ui->cancel, &QPushButton::clicked, this,
            &ReleaseMission::RlsCancel);        //“取消”
    connect(ui->continue_2, &QPushButton::clicked, this,
            &ReleaseMission::RlsContinue);        //“继续”
    m_srcBtnGrp->addButton(ui->Chn_1, 0);
    m_srcBtnGrp->addButton(ui->Eng_1, 1);
    m_srcBtnGrp->addButton(ui->Fre_1, 2);
    m_srcBtnGrp->addButton(ui->Spn_1, 3);

    m_tarBtnGrp->addButton(ui->Chn_2, 0);
    m_tarBtnGrp->addButton(ui->Eng_2, 1);
    m_tarBtnGrp->addButton(ui->Fre_2, 2);
    m_tarBtnGrp->addButton(ui->Spn_2, 3);
}


/*************************************************************************
【函数名称】        ~ReleaseMission
【函数功能】        ReleaseMission类析构函数
【参数】           void
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
ReleaseMission::~ReleaseMission()
{
    delete m_srcBtnGrp;
    delete m_tarBtnGrp;
    delete ui;
}


/*************************************************************************
【函数名称】        RlsContinue
【函数功能】        继续发布任务
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void ReleaseMission::RlsContinue()
{    
    if (FormatCheckPass())
    {
        //处理信息

        tempName = ui->e_missionName->text().toStdString();
        tempText =  ui->e_srcText->toPlainText().toStdString();
        tempIntro = ui->e_missionIntro->toPlainText().toStdString();

        //准备下一页面
        nxtpge = new ReleaseMission_2(this, user, tempName, tempText, tempIntro,
                                      tempSrcLang, tempTarLang);
        nxtpge->setWindowTitle("众包翻译平台-发布任务");
        connect(nxtpge, &ReleaseMission_2::s_rlsCancel, this,
                &ReleaseMission::RlsCancel);                     //监听下一页面取消
        connect(nxtpge, &ReleaseMission_2::s_rlsSucceed, this,
                &ReleaseMission::RlsSucceed);               //监听下一页面成功
        this->hide();
        nxtpge->show();
    }
}


/*************************************************************************
【函数名称】        FormatCheckPass
【函数功能】        检查输入格式
【参数】           void
【返回值】         bool 指示格式是否全部符合要求
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
bool ReleaseMission::FormatCheckPass()
{
    if (ui->e_missionName->text().isEmpty() ||
        ui->e_srcText->toPlainText().isEmpty() ||
        ui->e_missionIntro->toPlainText().isEmpty()
        )
    {
        QMessageBox* warn1 = new QMessageBox(QMessageBox::Warning, "WARNING",
              "Please fill in all the infomation blanks.",
              QMessageBox::Ok, this);
        warn1->show();
        return false;
    }
    else if (Datum::MissionNameExist(ui->e_missionName->text().toStdString()))
    {
        QMessageBox* warn1 = new QMessageBox(QMessageBox::Warning, "WARNING",
                                             tr( "This missionName already exists. Please try another one."),
                                             QMessageBox::Ok, this);
        warn1->show();
        return false;
    }
    else if (ui->e_missionName->text().contains(QRegExp("[()\"#|;]")))
    {
        QMessageBox* warn = new QMessageBox(QMessageBox::Warning, "Warning",
            "Mission name cannot contain special symbols : \n\
            ()\"#|;", QMessageBox::Ok, this);
        warn->show();
        return false;
    }
    else if (ui->e_missionIntro->toPlainText().contains(QRegExp("[()\"#|;]")))
    {
        QMessageBox* warn = new QMessageBox(QMessageBox::Warning, "Warning",
            "Mission introduction cannot contain special symbols : \n\
            ()\"#|;", QMessageBox::Ok, this);
        warn->show();
        return false;
    }
    else if (ui->e_srcText->toPlainText().contains(QRegExp("[()\"#|;]")))
    {
        QMessageBox* warn = new QMessageBox(QMessageBox::Warning, "Warning",
            "Source text cannot contain special symbols : \n\
            ()\"#|;", QMessageBox::Ok, this);
        warn->show();
        return false;
    }
    else if(!LanguageChecked())
    {
        return false;
    }
    return true;
}


bool ReleaseMission::LanguageChecked()
{
    if (m_srcBtnGrp->checkedId() == -1)
    {
        QMessageBox* warn = new QMessageBox(QMessageBox::Warning, "Warning",
            "Must choose a source language.", QMessageBox::Ok, this);
        warn->show();
        return false;
    }
    else if (m_tarBtnGrp->checkedId() == -1)
    {
        QMessageBox* warn = new QMessageBox(QMessageBox::Warning, "Warning",
            "Must choose a target language.", QMessageBox::Ok, this);
        warn->show();
        return false;
    }
    else
    {
        tempSrcLang = Mission::IntToLanguage(m_srcBtnGrp->checkedId());
        tempTarLang = Mission::IntToLanguage(m_tarBtnGrp->checkedId());

        if (tempSrcLang == tempTarLang)
        {
            QMessageBox* warn = new QMessageBox(QMessageBox::Warning, "Warning",
                "Source and target language cannot be the same.", QMessageBox::Ok, this);
            warn->show();
            return false;
        }
        return true;
    }
}

/*************************************************************************
【函数名称】        RlsSucceed
【函数功能】        发布成功处理
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void ReleaseMission::RlsSucceed(P_MSN mission)
{
    emit  s_rlsSucceed(mission);
}


/*************************************************************************
【函数名称】        RlsCancel
【函数功能】        发布取消处理
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void ReleaseMission::RlsCancel()
{
    emit s_rlsCancel();
}


