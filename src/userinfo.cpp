/*************************************************************************
【文件名】                 userinfo.cpp
【功能模块和目的】          UserInfo类实现
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/


#include "userinfo.h"
#include "ui_userinfo.h"
#include "missioninfo.h"
#include <QDebug>


/*************************************************************************
【函数名称】        UserInfo
【函数功能】        UserInfo类构造函数 构造该页面
【参数】
                  QWidget* parent               输入
                  P_USER user                   输入
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
UserInfo::UserInfo(QWidget* parent, P_USER user) :
    QDialog(parent),
    ui(new Ui::UserInfo),
    user(user)
{
    ui->setupUi(this);
    TableInitialize();
    connect(ui->back, &QPushButton::clicked, this, &UserInfo::ReturnLast);

    if (user->GetRlsMissions().size() == 0)
    {
        ui->releasedMissions->setEnabled(false);
    }

    if (user->GetInchgMissions().size() == 0)
    {
        ui->inChargeMissions->setEnabled(false);
    }

    if (user->GetPtcpMissions().size() == 0)
    {
        ui->partcptMissions->setEnabled(false);
    }
}


/*************************************************************************
【函数名称】        ~UserInfo
【函数功能】        UserInfo类析构 析构该页面
【参数】           void
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
UserInfo::~UserInfo()
{
    delete ui;
}



/*************************************************************************
【函数名称】        TableInitialize
【函数功能】        对页面中的所有表格进行初始化
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void UserInfo::TableInitialize()
{
    BasicInitial();
    RlsInitial();
    MngInitial();
    PtcpInitial();
}


/*************************************************************************
【函数名称】        BasicInitial
【函数功能】        对基本信息表格进行初始化
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void UserInfo::BasicInitial()
{
    ULL rowNum1 = 4;                    //用户名，真实姓名，积分，email
    ui->basicInfo->setRowCount(static_cast<int>(rowNum1));
    ui->basicInfo->setColumnCount(2);
    ui->basicInfo->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->basicInfo->verticalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    ui->basicInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QHeaderView* headerView = ui->basicInfo->verticalHeader();
    headerView->setHidden(true);

    ui->basicInfo->setItem(0, 0, new QTableWidgetItem("User Name"));
    ui->basicInfo->setItem(0, 1,
                           new QTableWidgetItem(QString::fromStdString(user->GetUserName())));
    ui->basicInfo->setItem(1, 0, new QTableWidgetItem("Real Name"));
    ui->basicInfo->setItem(1, 1,
                           new QTableWidgetItem(QString::fromStdString(user->GetRealName())));
    ui->basicInfo->setItem(2, 0, new QTableWidgetItem("Score"));
    ui->basicInfo->setItem(2, 1,
                           new QTableWidgetItem(QString::number(user->GetScore())));
    ui->basicInfo->setItem(3, 0, new QTableWidgetItem("E-mail"));
    ui->basicInfo->setItem(3, 1,
                           new QTableWidgetItem(QString::fromStdString(user->GetEMail())));
}


/*************************************************************************
【函数名称】        RlsInitial
【函数功能】        对发布过的任务表格进行初始化
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void UserInfo::RlsInitial()
{
    ULL rowNum2 = (user->GetRlsMissions().size());
    ui->releasedMissions->setRowCount(static_cast<int>(rowNum2));
    ui->releasedMissions->setColumnCount(
        4);          //Mission Name, Release State, Introduction, Details";
    ui->releasedMissions->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Interactive);
    ui->releasedMissions->horizontalHeader()->setSectionResizeMode(1,
            QHeaderView::ResizeToContents);
    ui->releasedMissions->horizontalHeader()->setSectionResizeMode(2,
            QHeaderView::ResizeToContents);
    ui->releasedMissions->verticalHeader()->setSectionResizeMode(
        QHeaderView::Interactive);
    ui->releasedMissions->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QStringList header;
    header << "Mission Name" << "Release State" << "Introduction" << "Details";
    ui->releasedMissions->setHorizontalHeaderLabels(header);

    for (ULL i = 0; i < rowNum2; i++)
    {
        P_MSN p1(user->GetRlsMissions()[i]);  //任务名、任务状态、简介、任务页

        if (p1.exist())
        {
            ui->releasedMissions->setItem(static_cast<int>(i), 0,
                                          new QTableWidgetItem(QString::fromStdString(p1->GetMissionName())));
            ui->releasedMissions->setItem(static_cast<int>(i), 1,
                                          new QTableWidgetItem(QString::fromStdString(p1->GetReleaseStateStr())));
            ui->releasedMissions->setItem(static_cast<int>(i), 2,
                                          new QTableWidgetItem(QString::fromStdString(p1->GetIntroduction())));

            QPushButton* opr = new QPushButton;                            //操作
            opr->setText("View Details");
            opr->setStyleSheet("QPushButton{background-color:white;}");
            QString name = QString::fromStdString(p1->GetMissionName());
            opr->setProperty("Mission", name);
            connect(opr, &QPushButton::clicked, this, &UserInfo::SetMissionBtn);

            ui->releasedMissions->setCellWidget(static_cast<int>(i), 3, opr);
        }
    }
}


/*************************************************************************
【函数名称】        MngInitial
【函数功能】        对负责的任务表格进行初始化
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void UserInfo::MngInitial()
{
    ULL rowNum3 = (user->GetInchgMissions().size());
    ui->inChargeMissions->setRowCount(static_cast<int>(rowNum3));
    ui->inChargeMissions->setColumnCount(
        4);          //Mission Name, Release State, Introduction, Details";
    ui->inChargeMissions->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Interactive);
    ui->inChargeMissions->horizontalHeader()->setSectionResizeMode(1,
            QHeaderView::ResizeToContents);
    ui->inChargeMissions->horizontalHeader()->setSectionResizeMode(2,
            QHeaderView::ResizeToContents);
    ui->inChargeMissions->verticalHeader()->setSectionResizeMode(
        QHeaderView::Interactive);
    ui->inChargeMissions->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QStringList header;
    header << "Mission Name" << "Release State" << "Introduction" << "Details";
    ui->inChargeMissions->setHorizontalHeaderLabels(header);

    for (ULL i = 0; i < rowNum3; i++)
    {
        P_MNG p2(user->GetInchgMissions()[i]);  //任务名、任务状态、简介、任务页

        if (p2.exist())
        {
            ui->inChargeMissions->setItem(static_cast<int>(i), 0,
                                          new QTableWidgetItem(QString::fromStdString(p2->GetMissionName())));
            ui->inChargeMissions->setItem(static_cast<int>(i), 1,
                                          new QTableWidgetItem(QString::fromStdString(p2->GetShowingMode())));
            ui->inChargeMissions->setItem(static_cast<int>(i), 2,
                                          new QTableWidgetItem(QString::fromStdString(p2->GetIntroduction())));

            QPushButton* opr = new QPushButton;                            //操作
            opr->setText("View Details");
            opr->setStyleSheet("QPushButton{background-color:white;}");
            QString name = QString::fromStdString(p2->GetMissionName());
            opr->setProperty("MngMission", name);
            connect(opr, &QPushButton::clicked, this, &UserInfo::SetMissionBtn);

            ui->inChargeMissions->setCellWidget(static_cast<int>(i), 3, opr);
        }
    }
}


/*************************************************************************
【函数名称】        MngInitial
【函数功能】        对参与的任务表格进行初始化
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void UserInfo::PtcpInitial()
{
    ULL rowNum4 = (user->GetPtcpMissions().size());
    ui->partcptMissions->setRowCount(static_cast<int>(rowNum4));
    ui->partcptMissions->setColumnCount(
        4);          //Mission Name, Release State, Introduction, Details";
    ui->partcptMissions->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Interactive);
    ui->partcptMissions->horizontalHeader()->setSectionResizeMode(1,
            QHeaderView::ResizeToContents);
    ui->partcptMissions->horizontalHeader()->setSectionResizeMode(2,
            QHeaderView::ResizeToContents);
    ui->partcptMissions->verticalHeader()->setSectionResizeMode(
        QHeaderView::Interactive);
    ui->partcptMissions->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QStringList header;
    header << "Mission Name" << "Release State" << "Introduction" << "Details";
    ui->partcptMissions->setHorizontalHeaderLabels(header);

    for (ULL i = 0; i < rowNum4; i++)
    {
        KEY_SUB k1(user->GetPtcpMissions()[i], user->GetUserName());
        P_SUB p3(k1);               //任务名、任务状态、简介、任务页

        if (p3.exist())
        {
            ui->partcptMissions->setItem(static_cast<int>(i), 0,
                                         new QTableWidgetItem(QString::fromStdString(p3->GetMissionName())));
            ui->partcptMissions->setItem(static_cast<int>(i), 1,
                                         new QTableWidgetItem(QString::fromStdString(p3->GetShowingMode())));
            ui->partcptMissions->setItem(static_cast<int>(i), 2,
                                         new QTableWidgetItem(QString::fromStdString(p3->GetIntroduction())));


            QPushButton* opr = new QPushButton;                            //操作
            opr->setText("View Details");
            opr->setStyleSheet("QPushButton{background-color:white;}");
            QString name = QString::fromStdString(p3->GetMissionName());
            opr->setProperty("SubMission", name);
            connect(opr, &QPushButton::clicked, this, &UserInfo::SetMissionBtn);

            ui->partcptMissions->setCellWidget(static_cast<int>(i), 3, opr);
        }
    }
}


/*************************************************************************
【函数名称】        SetMissionBtn
【函数功能】        设置任务页按钮
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void UserInfo::SetMissionBtn()
{
    std::string s1 = sender()->property("Mission").toString().toStdString();
    P_MSN mission = s1;

    if (mission.exist())
    {
        MissionInfo* info = new MissionInfo(this, mission);
        info->show();
        connect(info, &MissionInfo::s_return, this, &UserInfo::MsnInfoReturn);
        return;
    }

    std::string s2 = sender()->property("MngMission").toString().toStdString();
    P_MNG mng = s2;

    if (mng.exist())
    {
        MissionInfo* info = new MissionInfo(this, mng);
        info->show();
        connect(info, &MissionInfo::s_return, this, &UserInfo::MsnInfoReturn);
        return;
    }

    std::string s3 = sender()->property("SubMission").toString().toStdString();
    P_SUB sub = KEY_SUB(s3, user->GetUserName());

    if (sub.exist())
    {
        MissionInfo* info = new MissionInfo(this, sub);
        info->show();
        connect(info, &MissionInfo::s_return, this, &UserInfo::MsnInfoReturn);
        return;
    }

}


/*************************************************************************
【函数名称】        MsnInfoReturn
【函数功能】        任务页返回
【参数】
                  MissionInfo* infoPge             输入
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void UserInfo::MsnInfoReturn(MissionInfo* infoPge)
{
    this->show();

    if (infoPge != nullptr)
    {
        infoPge->close();
    }
}


/*************************************************************************
【函数名称】        ReturnLast
【函数功能】        返回上一页
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void UserInfo::ReturnLast()
{
    emit s_return(this);
}


