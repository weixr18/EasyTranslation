/*************************************************************************
【文件名】                 missionhall.cpp
【功能模块和目的】          MissionHall类实现
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/


#include "missionhall.h"
#include "ui_missionhall.h"
#include "aplmcfmdialog.h"
#include "apltcfmdialog.h"
#include <QDebug>
#include <QMessageBox>


/*************************************************************************
【函数名称】        MissionHall
【函数功能】        MissionHall类构造函数 构造该页面
【参数】
                  QWidget* parent          输入
                  P_USER user              输入
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
MissionHall::MissionHall(QWidget* parent, P_USER user) :
    QMainWindow(parent),
    ui(new Ui::MissionHall),
    user(user)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this,
            &MissionHall::ReturnHomePage);
    TableInitialize();
}


/*************************************************************************
【函数名称】        ~MissionHall
【函数功能】        MissionHall类析构函数
【参数】           void
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
MissionHall::~MissionHall()
{
    Datum::UpdateDB();
    delete ui;
}



//****************************页面初始化****************************************



/*************************************************************************
【函数名称】        SetUserHallMissions
【函数功能】        初始化在任务大厅显示的任务
【参数】           void
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void MissionHall::SetUserHallMissions()
{
    if (!userHallMissions.empty())
    { userHallMissions.clear(); }

    if (!userHallMngMissions.empty())
    { userHallMngMissions.clear(); }

    std::vector<std::string> res =
        Datum::SearchMissions("");       //此处根据页面输入可添加搜索条件

    for (auto name : res)
    {
        if (Datum::MngMsnNameExist(name))
        {
            P_MNG temp(name);

            if (Platform::mng_show_in_user_hall(temp, user))
            {
                userHallMngMissions.push_back(temp);
            }
        }
        else if (Datum::MissionNameExist(name))
        {
            P_MSN temp(name);

            if (Platform::msn_show_in_user_hall(temp, user))
            {
                userHallMissions.push_back(temp);
            }
        }
    }

}


/*************************************************************************
【函数名称】        TableInitialize
【函数功能】        表头初始化
【参数】            void
【返回值】          void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void MissionHall::TableInitialize()
{
    //missionName, releaseState, recruitMTime, ViewMission, OperationBtn
    SetUserHallMissions();
    int rowNum = static_cast<int>(userHallMissions.size() +
                                  userHallMngMissions.size());
    ui->allMissions->setRowCount(rowNum);
    ui->allMissions->setColumnCount(5);
    ui->allMissions->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->allMissions->verticalHeader()->setSectionResizeMode(
        QHeaderView::Interactive);
    ui->allMissions->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QStringList header;
    header << "Mission Name" << "Release Status" << "Key Info" << "Details" <<
           "Operations";
    ui->allMissions->setHorizontalHeaderLabels(header);

    RlsTableInitialize();
    MngTableInitialize();
}


/*************************************************************************
【函数名称】        RlsTableInitialize
【函数功能】        发布阶段表格初始化
【参数】            void
【返回值】          void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void MissionHall::RlsTableInitialize()
{
    for (ULL i = 0; i < userHallMissions.size(); i++)
    {
        P_MSN temp = userHallMissions[i];

        if (temp.exist())
        {
            ui->allMissions->setItem(static_cast<int>(i), 0,
                new QTableWidgetItem(QString::fromStdString(temp->GetMissionName() ) ) );
            ui->allMissions->setItem(static_cast<int>(i), 1,
                new QTableWidgetItem(QString::fromStdString(temp->GetShowingMode() ) ) );

            //此处的grid显示的是截止时间
            std::string time = Mission::TimeToString(temp->GetRecruitMTime() );
            ui->allMissions->setItem(static_cast<int>(i), 2,
                new QTableWidgetItem(QString::fromStdString(time) ) );

            //查看详情页
            QPushButton* det = new QPushButton;
            det->setText("View Details");
            det->setStyleSheet("QPushButton{background-color:white;}");
            QString name = QString::fromStdString(userHallMissions[i]->GetMissionName());
            det->setProperty("Mission", name);
            connect(det, &QPushButton::clicked, this, &MissionHall::SetBMissionInfo);
            ui->allMissions->setCellWidget(static_cast<int>(i), 3, det);

            //操作按钮
            QPushButton* opr = new QPushButton;
            SetMissionOprtButton(opr, userHallMissions[i]);
            ui->allMissions->setCellWidget(static_cast<int>(i), 4, opr);
        }
    }
}


/*************************************************************************
【函数名称】        MngTableInitialize
【函数功能】        负责阶段表格初始化
【参数】            void
【返回值】          void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void MissionHall::MngTableInitialize()
{
    ULL preL = (userHallMissions.size());

    for (ULL i = 0; i < userHallMngMissions.size(); i++)
    {
        P_MNG temp = userHallMngMissions[i];

        if (temp.exist())
        {
            ui->allMissions->setItem(static_cast<int>(preL + i), 0,
                new QTableWidgetItem(QString::fromStdString(temp->GetMissionName() ) ) );
            ui->allMissions->setItem(static_cast<int>(preL + i), 1,
                new QTableWidgetItem(QString::fromStdString(temp->GetShowingMode() ) ) );

            //此处的grid显示的是截止时间
            std::string time = Mission::TimeToString(temp->GetRecruitMTime());
            ui->allMissions->setItem(static_cast<int>(preL + i), 2,
                new QTableWidgetItem(QString::fromStdString(time) ) );

            //查看详情页
            QPushButton* det = new QPushButton;
            det->setText("View Details");
            det->setStyleSheet("QPushButton{background-color:white;}");
            QString name = QString::fromStdString(userHallMngMissions[i]->GetMissionName());
            det->setProperty("MngMission", name);
            connect(det, &QPushButton::clicked, this, &MissionHall::SetBMissionInfo);
            ui->allMissions->setCellWidget(static_cast<int>(preL + i), 3, det);

            QPushButton* opr = new QPushButton;
            SetMissionOprtButton(opr, userHallMngMissions[i]);
            ui->allMissions->setCellWidget(static_cast<int>(preL + i), 4, opr);
        }
    }
}


/*************************************************************************
【函数名称】        SetMissionOprtButton
【函数功能】        设置
【参数】            QPushButton* btn          输入
                   P_MSN mission             输入
【返回值】          void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void MissionHall::SetMissionOprtButton(QPushButton* btn, P_MSN mission)
{
    switch (mission->GetReleaseState())
    {
    case (Mission::R_RECRUIT_M):
    {
        //报名负责人
        btn->setText("Apply for manager.");
        btn->setStyleSheet("QPushButton{background-color:white;}");

        //确认对话框
        if (mission->GetReleaser() != user->GetUserName())
        {
            AplMCfmDialog* confirm = new AplMCfmDialog(this, this, mission,
                    "Are you sure to apply for this mission's manager?", user);
            connect(btn, &QPushButton::clicked, confirm, &CfmDialog::show);
            connect(confirm, SIGNAL(s_returnM3(P_MSN, CfmDialog*, bool)),
                    this, SLOT(ApplyMReturn(P_MSN , CfmDialog*, bool)));
        }
        else
        {btn->setEnabled(false);}

        break;
    }

    default:
    {
        btn->setEnabled(false);
        btn->setStyleSheet("QPushButton{background-color:white;}");
        break;
    }
    }
}


/*************************************************************************
【函数名称】        SetMissionOprtButton
【函数功能】        设置操作按钮
【参数】            QPushButton* btn          输入
                   P_MNG mng                 输入
【返回值】          void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void MissionHall::SetMissionOprtButton(QPushButton* btn, P_MNG mng)
{
    switch (mng->GetReleaseState())
    {
    case (Mission::R_TRANSLATING):
    {
        switch (mng->GetManageState())
        {
        case ManageMission::M_RECRUIT_T:                                //报名翻译者
        {
            //设置确认报名dialog
            btn->setText("Apply for translator.");
            btn->setStyleSheet("QPushButton{background-color:white;}");

            AplTCfmDialog* confirm = new AplTCfmDialog(this, this, mng,
                    "Are you sure to apply for this mission's translator?");
            connect(btn, &QPushButton::clicked, confirm, &CfmDialog::show);
            connect(confirm, SIGNAL(s_returnM2(P_MNG, CfmDialog* )),
                    this, SLOT(ApplyTSucceed(P_MNG, CfmDialog*)));
        }
        break;

        default:
        {
            btn->setEnabled(false);
            btn->setVisible(false);
            btn->setStyleSheet("QPushButton{background-color:white;}");
            break;
        }
        }

        break;
    }

    default:
    {
        btn->setEnabled(false);
        btn->setStyleSheet("QPushButton{background-color:white;}");
        break;
    }
    }
}



//**********************************页面跳转****************************************


/*************************************************************************
【函数名称】        ApplyMSucceed
【函数功能】        申请负责人成功
【参数】            P_MSN mission         输入
                   CfmDialog* cfmPge     输入
【返回值】          void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void MissionHall::ApplyMReturn(P_MSN mission, CfmDialog* cfmPge, bool result)
{
    cfmPge->close();
    if (!mission.exist())
    {
        qDebug() << "Error 1  任务不存在！\
            \n\t from : MissionHall::applyMSucceed(Mission* mission, CfmDialog* cfmPge)";
    }
    else if (result)
    {
        //信息处理
        Platform::u_apl_manager(user, mission);
    }
    else
    {
        //Du nothing.
    }

    TableInitialize();                                     //刷新列表
}



/*************************************************************************
【函数名称】        ApplyMSucceed
【函数功能】        申请翻译者成功
【参数】
                   P_MNG mng             输入
                   CfmDialog* cfmPge     输入
【返回值】          void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void MissionHall::ApplyTSucceed(P_MNG mng, CfmDialog* cfmPge)
{
    cfmPge->close();

    if (!mng.exist())
    {qDebug() << "Error: applyTSucceed: 任务不存在！";}
    else
    {
        //信息处理
        Platform::u_apl_transltr(user, mng);
    }
    TableInitialize();                                     //刷新列表
}


/*************************************************************************
【函数名称】        SetBMissionInfo
【函数功能】        设置任务信息页按钮
【参数】            void
【返回值】          void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void MissionHall::SetBMissionInfo()
{
    std::string s1 = sender()->property("Mission").toString().toStdString();
    P_MSN mission = s1;

    if (mission.exist())
    {
        MissionInfo* info = new MissionInfo(this, mission);
        info->show();
        connect(info, &MissionInfo::s_return, this, &MissionHall::MsnInfoReturn);
        return;
    }

    std::string s2 = sender()->property("MngMission").toString().toStdString();
    P_MNG mng = s2;

    if (mng.exist())
    {
        MissionInfo* info = new MissionInfo(this, mng);
        info->show();
        connect(info, &MissionInfo::s_return, this, &MissionHall::MsnInfoReturn);
        return;
    }

    std::string s3 = sender()->property("SubMission").toString().toStdString();
    P_SUB sub = KEY_SUB(s3, user->GetUserName());

    if (sub.exist())
    {
        MissionInfo* info = new MissionInfo(this, sub);
        info->show();
        connect(info, &MissionInfo::s_return, this, &MissionHall::MsnInfoReturn);
        return;
    }
}


/*************************************************************************
【函数名称】        MsnInfoReturn
【函数功能】        任务信息页返回
【参数】
                   MissionInfo* infoPge       输入
【返回值】          void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void MissionHall::MsnInfoReturn(MissionInfo* infoPge)
{
    this->show();

    if (infoPge != nullptr)
    {
        infoPge->close();
    }
}


/*************************************************************************
【函数名称】        ReturnHomePage
【函数功能】        返回个人主页
【参数】            void
【返回值】          void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void MissionHall::ReturnHomePage()
{
    emit s_returnHomePage();
}

