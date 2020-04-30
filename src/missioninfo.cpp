/*************************************************************************
【文件名】                 MissionInfo.cpp
【功能模块和目的】          MissionInfo类实现
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/


#include "missioninfo.h"
#include "ui_missioninfo.h"
#include <QDebug>


/*************************************************************************
【函数名称】        MissionInfo
【函数功能】        MissionInfo类构造函数 构造该页面
【参数】
                  QWidget* parent          输入
                  P_MSN mission            输入
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
MissionInfo::MissionInfo(QWidget* parent, P_MSN mission) :
    QMainWindow(parent),
    ui(new Ui::MissionInfo)
{
    ui->setupUi(this);
    connect(ui->back, &QPushButton::clicked, this, &MissionInfo::ReturnLast);

    if (mission.exist())
    {
        BasicInitial(mission);
        P_MNG mng = mission->GetMissionName();

        if (mng.exist())
        {
            MngInfoInitial(mng);
            ManageMission::ManageState s = mng->GetManageState();

            if (s == ManageMission::M_CHECKING ||
                s == ManageMission::M_SUBMITTED ||
                s == ManageMission::M_ACCOMPLISHED )
            {
                TrslInfoInitial(mng);

                if (s == ManageMission::M_ACCOMPLISHED)
                {
                    ResultInitial(mng);
                }
                else
                {
                    ui->missionResult->setEnabled(false);
                }
            }
            else
            {
                ui->trsInfo->setEnabled(false);
                ui->missionResult->setEnabled(false);
            }
        }
        else
        {
            ui->manageInfo_2->setEnabled(false);
            ui->trsInfo->setEnabled(false);
            ui->missionResult->setEnabled(false);
        }
    }
}


/*************************************************************************
【函数名称】        MissionInfo
【函数功能】        MissionInfo类构造函数 构造该页面
【参数】
                  QWidget* parent          输入
                  P_MNG mng                输入
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
MissionInfo::MissionInfo(QWidget* parent, P_MNG mng) :
    QMainWindow(parent),
    ui(new Ui::MissionInfo)
{
    ui->setupUi(this);
    connect(ui->back, &QPushButton::clicked, this, &MissionInfo::ReturnLast);

    if (mng.exist())
    {
        BasicInitial(mng->GetMissionName());
        MngInfoInitial(mng);
        ManageMission::ManageState s = mng->GetManageState();

        if (s == ManageMission::M_CHECKING ||
            s == ManageMission::M_SUBMITTED ||
            s == ManageMission::M_ACCOMPLISHED )
        {
            TrslInfoInitial(mng);
        }

        if (s == ManageMission::M_ACCOMPLISHED)
        {
            ResultInitial(mng);
        }
    }
}


/*************************************************************************
【函数名称】        MissionInfo
【函数功能】        MissionInfo类构造函数 构造该页面
【参数】
                  QWidget* parent          输入
                  P_SUB sub                输入
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
MissionInfo::MissionInfo(QWidget* parent, P_SUB sub) :
    QMainWindow(parent),
    ui(new Ui::MissionInfo)
{
    ui->setupUi(this);
    connect(ui->back, &QPushButton::clicked, this, &MissionInfo::ReturnLast);

    if (sub.exist())
    {
        BasicInitial(sub->GetMissionName());
        MngInfoInitial(sub->GetMissionName());
        TrslInfoInitial(sub->GetMissionName());

        P_MNG mng = sub->GetMissionName();
        ManageMission::ManageState s = mng->GetManageState();

        if (s == ManageMission::M_ACCOMPLISHED)
        {
            ResultInitial(mng);
        }
    }
}


/*************************************************************************
【函数名称】        ~MissionInfo
【函数功能】        MissionInfo类析构函数
【参数】           void
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
MissionInfo::~MissionInfo()
{
    delete ui;
}


/*************************************************************************
【函数名称】        BasicInitial
【函数功能】        基本信息初始化
【参数】
                  P_MSN pMission       输入
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void MissionInfo::BasicInitial(P_MSN pMission)
{
    int rowNum1 = 9;
    ui->basicInfo->setRowCount(rowNum1);
    ui->basicInfo->setColumnCount(2);
    ui->basicInfo->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->basicInfo->verticalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    ui->basicInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QHeaderView* headerView = ui->basicInfo->verticalHeader();
    headerView->setHidden(true);
    QHeaderView* headerView2 = ui->basicInfo->horizontalHeader();
    headerView2->setHidden(true);

    ui->basicInfo->setItem(0, 0, new QTableWidgetItem("Mission Name"));
    ui->basicInfo->setItem(0, 1,
                           new QTableWidgetItem(QString::fromStdString(pMission->GetMissionName())));
    ui->basicInfo->setItem(1, 0, new QTableWidgetItem("Releaser"));
    ui->basicInfo->setItem(1, 1,
                           new QTableWidgetItem(QString::fromStdString(pMission->GetReleaser())));

    ui->basicInfo->setItem(2, 0, new QTableWidgetItem("Source Language"));

    std::string src = Mission::LanguageToStr(pMission->GetSrcLanguage());
    ui->basicInfo->setItem(2, 1, new QTableWidgetItem(QString::fromStdString(src)));

    ui->basicInfo->setItem(3, 0, new QTableWidgetItem("Target Language"));

    std::string tar = Mission::LanguageToStr(pMission->GetTarLanguage());
    ui->basicInfo->setItem(3, 1, new QTableWidgetItem(QString::fromStdString(tar)));


    ui->basicInfo->setItem(4, 0, new QTableWidgetItem("Introduction"));
    ui->basicInfo->setItem(4, 1,
                           new QTableWidgetItem(QString::fromStdString(pMission->GetIntroduction())));

    ui->basicInfo->setItem(5, 0, new QTableWidgetItem("Mission DDL"));
    ui->basicInfo->setItem(5, 1, new QTableWidgetItem(
                               QString::fromStdString(Mission::TimeToString(pMission->GetMissionDDL() ) ) ) );

    ui->basicInfo->setItem(6, 0, new QTableWidgetItem("Recruit M Time"));
    ui->basicInfo->setItem(6, 1, new QTableWidgetItem(
                               QString::fromStdString(Mission::TimeToString(pMission->GetRecruitMTime() ) ) ));

    ui->basicInfo->setItem(7, 0, new QTableWidgetItem("Award Amount"));
    ui->basicInfo->setItem(7, 1,
                           new QTableWidgetItem(QString::number(pMission->GetAwardAmount() ) ) );

    ui->basicInfo->setItem(8, 0, new QTableWidgetItem("Release State"));
    ui->basicInfo->setItem(8, 1,
                           new QTableWidgetItem(QString::fromStdString(
                                       pMission->GetReleaseStateStr() ) ) );
}


/*************************************************************************
【函数名称】        MngInfoInitial
【函数功能】        负责人信息初始化
【参数】
                  P_MNG pMng          输入
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void MissionInfo::MngInfoInitial(P_MNG pMng)
{
    int rowNum2 = 3;                    //负责人，招募截止时间，负责状态，
    ui->manageInfo_2->setRowCount(rowNum2);
    ui->manageInfo_2->setColumnCount(2);
    ui->manageInfo_2->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Stretch);
    ui->manageInfo_2->verticalHeader()->setSectionResizeMode(
        QHeaderView::Interactive);
    ui->manageInfo_2->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QHeaderView* headerView = ui->manageInfo_2->verticalHeader();
    headerView->setHidden(true);
    QHeaderView* headerView2 = ui->manageInfo_2->horizontalHeader();
    headerView2->setHidden(true);

    ui->manageInfo_2->setItem(0, 0, new QTableWidgetItem("Manager"));
    ui->manageInfo_2->setItem(0, 1,
                              new QTableWidgetItem(QString::fromStdString(pMng->GetManager() ) ) );
    ui->manageInfo_2->setItem(1, 0, new QTableWidgetItem("Recruit T Time"));
    ui->manageInfo_2->setItem(1, 1, new QTableWidgetItem(
                                  QString::fromStdString(Mission::TimeToString(pMng->GetRecruitTTime() ) ) ) );
    ui->manageInfo_2->setItem(2, 0, new QTableWidgetItem("Manage State"));
    ui->manageInfo_2->setItem(2, 1,
                              new QTableWidgetItem(QString::fromStdString(pMng->GetManageStateStr() ) ) );

}


/*************************************************************************
【函数名称】        TrslInfoInitial
【函数功能】        翻译者信息初始化
【参数】
                  P_MNG pMng          输入
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void MissionInfo::TrslInfoInitial(P_MNG pMng)
{
    ULL rowNum3 = pMng->GetTranslators().size();
    ui->trsInfo->setRowCount(static_cast<int>(rowNum3));
    ui->trsInfo->setColumnCount(3);      //userName, subState, viewInfo
    ui->trsInfo->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->trsInfo->verticalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    ui->trsInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QStringList header;
    header << "Translator" << "Translate State" << "View Info";
    ui->trsInfo->setHorizontalHeaderLabels(header);

    int i = 0;

    for (auto key : pMng->GetSubMissions())
    {
        P_SUB sub(key);
        P_USER trsl(sub->GetTranslator());

        if (sub.exist() && trsl.exist())
        {
            ui->trsInfo->setItem(static_cast<int>(i), 0,
                                 new QTableWidgetItem(QString::fromStdString(sub->GetTranslator() ) ) );
            ui->trsInfo->setItem(static_cast<int>(i), 1,
                                 new QTableWidgetItem(QString::fromStdString(sub->GetSubMissionStateStr() ) ) );

            QPushButton* info = new QPushButton;
            info->setText("View details.");
            info->setStyleSheet("QPushButton{background-color:white;}");

            QString name = QString::fromStdString(sub->GetTranslator());
            info->setProperty("User", name);
            connect(info, &QPushButton::clicked, this, &MissionInfo::SetBUserInfo);
            ui->trsInfo->setCellWidget(static_cast<int>(i), 2, info);
        }

        i++;
    }
}


/*************************************************************************
【函数名称】        ResultInitial
【函数功能】        任务成果信息初始化
【参数】
                  P_MNG pMng          输入
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void MissionInfo::ResultInitial(P_MNG pMng)
{
    int rownum4 = 1;
    ui->missionResult->setRowCount(rownum4);
    ui->missionResult->setColumnCount(2);
    ui->missionResult->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Stretch);
    ui->missionResult->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->missionResult->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QStringList header;
    header << "Source Text" << "Translation Text";
    ui->missionResult->setHorizontalHeaderLabels(header);
    QHeaderView* headerView = ui->missionResult->verticalHeader();
    headerView->setHidden(true);

    ui->missionResult->setItem(0, 0,
                               new QTableWidgetItem(QString::fromStdString(pMng->GetSrcText() ) ) );
    ui->missionResult->setItem(0, 1,
                               new QTableWidgetItem(QString::fromStdString(pMng->GetLastTranslation() ) ) );

}


/*************************************************************************
【函数名称】        SetBUserInfo
【函数功能】        设置查看用户信息页按钮
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void MissionInfo::SetBUserInfo()
{
    std::string s = sender()->property("User").toString().toStdString();
    P_USER p_user = s;

    if (p_user.exist())
    {
        UserInfo* infoPage = new UserInfo(this, p_user);
        infoPage->setWindowTitle("个人信息");
        infoPage->show();
        connect(infoPage, &UserInfo::s_return, this, &MissionInfo::ViewUserReturn);
    }
}


/*************************************************************************
【函数名称】        SetBUserInfo
【函数功能】        用户信息页返回响应
【参数】
                  UserInfo* userinfo
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void MissionInfo::ViewUserReturn(UserInfo* userinfo)
{
    userinfo->close();
}


/*************************************************************************
【函数名称】        ReturnLast
【函数功能】        返回上一页
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void MissionInfo::ReturnLast()
{
    emit s_return(this);
}

