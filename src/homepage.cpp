/*************************************************************************
【文件名】                 homepage.cpp
【功能模块和目的】          HomePage类实现-PART I
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/


#include "homepage.h"
#include "ui_homepage.h"
#include <QDebug>


/*************************************************************************
【函数名称】       HomePage
【函数功能】       HomePage类构造函数 构造该页面
【参数】
                  QWidget* parent          输入
                  P_USER   user            输入
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
HomePage::HomePage(QWidget* parent, P_USER user) :
    QMainWindow(parent),
    ui(new Ui::HomePage),
    pS(new StateUpdateW),
    user(user)
{
    if (user.exist())
    {
        ui->setupUi(this);
        connect(ui->exit, &QPushButton::clicked, this, &HomePage::Exit_clicked);
        ui->welcomeBro->setText(QString("Welcome, ") + QString::fromStdString(
                                    user->GetUserName()));

        connect(ui->releaseMission, &QPushButton::clicked, this,
                &HomePage::GoReleaseMission);             //发布新任务
        connect(ui->missionHall, &QPushButton::clicked, this,
                &HomePage::GoMissionHall);                 //任务大厅
        connect(ui->myAccount, &QPushButton::clicked, this,
                &HomePage::GoMyAccount);                    //我的账户
        connect(ui->myMessage, &QPushButton::clicked, this,
                &HomePage::GoMessageBox);
        connect(pS, &StateUpdateW::s_timeUp, this, &HomePage::PageRefresh);

        TableInitialize();
    }
}

/*************************************************************************
【函数名称】       ~HomePage
【函数功能】       HomePage类构析构函数
【参数】           void
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
HomePage::~HomePage()
{
    Datum::UpdateDB();
    delete ui;
    delete pS;
}

//*****************************页面显示设置********************************


/*************************************************************************
【函数名称】       TableInitialize
【函数功能】       表格初始化
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void HomePage::TableInitialize()
{
    GetUserMissions();
    pS->CheckAndUpdate1();
    pS->CheckAndUpdate2();

    RlsTableInitialize();
    MngTableInitialize();
    PtcpTableInitialize();
}



/*************************************************************************
【函数名称】       GetUserMissions
【函数功能】       获取用户有关的任务列表
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void HomePage::GetUserMissions()
{
    releasedMissions.clear();

    for (ULL i = 0; i != user->GetRlsMissions().size(); i++)
    {
        P_MSN temp = user->GetRlsMissions()[i];

        if (temp.exist())
        {
            releasedMissions.push_back(temp->GetMissionName());
        }
    }

    inChargeMissions.clear();

    for (ULL i = 0; i != user->GetInchgMissions().size(); i++)
    {
        P_MSN temp = user->GetInchgMissions()[i];

        if (temp.exist())
        {
            inChargeMissions.push_back(temp->GetMissionName());
        }

    }

    participatingMissions.clear();

    for (ULL i = 0; i != user->GetPtcpMissions().size(); i++)
    {
        P_MNG temp = user->GetPtcpMissions()[i];

        if (temp.exist())
        {
            participatingMissions.push_back(temp->GetMissionName());
        }
    }
}


/*************************************************************************
【函数名称】       RlsTableInitialize
【函数功能】       发布任务的表格初始化
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void HomePage::RlsTableInitialize()
{
    ULL rowNum =  (releasedMissions.size() + inChargeMissions.size() +
                   participatingMissions.size());
    ui->myMissions->setRowCount(static_cast<int>(rowNum));
    ui->myMissions->setColumnCount(5);
    //missionName, my participation, releaseState, recruitMTime, Button

    ui->myMissions->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->myMissions->horizontalHeader()->setSectionResizeMode(1,
            QHeaderView::ResizeToContents);
    ui->myMissions->horizontalHeader()->setSectionResizeMode(2,
            QHeaderView::ResizeToContents);
    ui->myMissions->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QStringList header;
    header << "Mission Name" << "My participation" << "Mission Status" <<
           "Inportant Info" << "Operations";
    ui->myMissions->setHorizontalHeaderLabels(header);

    for (ULL i = 0; i < releasedMissions.size(); i++)
    {
        P_MSN temp = releasedMissions[i];

        if (temp.exist())
        {
            ui->myMissions->setItem(static_cast<int>(i), 0,
                new QTableWidgetItem(QString::fromStdString(temp ->GetMissionName() ) ) );
            ui->myMissions->setItem(static_cast<int>(i), 1,
                new QTableWidgetItem("Release"));
            ui->myMissions->setItem(static_cast<int>(i), 2,
                new QTableWidgetItem(QString::fromStdString(
                temp->GetReleaseStateStr() ) ) );           //任务发布状态

            std::string time = Mission::TimeToString(temp->GetRecruitMTime());
            ui->myMissions->setItem(static_cast<int>(i), 3,
                new QTableWidgetItem(QString::fromStdString("Recruit M Time:\n" + time)));

            QPushButton* opr = new QPushButton;
            SetRlsMissionOprtButton(opr, temp);
            ui->myMissions->setCellWidget(static_cast<int>(i), 4, opr);
        }

        for (int j = 0; j < 5; j++)
        {
            QTableWidgetItem* temp = ui->myMissions->item(static_cast<int>(i), j);

            if (temp != nullptr)
            {
                temp->setTextAlignment(Qt::AlignCenter);
            }
        }
    }

    ui->myMissions->resizeRowsToContents();
}


/*************************************************************************
【函数名称】       MngTableInitialize
【函数功能】       负责任务的表格初始化
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void HomePage::MngTableInitialize()
{
    ULL preL = releasedMissions.size() ;

    for (ULL i = 0; i < inChargeMissions.size(); i++)
    {
        P_MSN temp = inChargeMissions[i];
        ui->myMissions->setItem(static_cast<int>(preL + i), 0,
                                new QTableWidgetItem(QString::fromStdString(temp ->GetMissionName() ) ));

        P_MNG m1(inChargeMissions[i]);

        if (m1.exist())
        {
            Mission::ApplyMState s1 = m1->GetAplMState(user->GetUserName());

            if (s1 == Mission::A_APPLY_M_SUCCEED)
            {
                ui->myMissions->setItem(static_cast<int>(preL + i), 1,
                                        new QTableWidgetItem("Manage"));
                ui->myMissions->setItem(static_cast<int>(preL + i), 2,
                    new QTableWidgetItem(QString::fromStdString(temp->GetManageStateStr() ) ) );
                std::string time = Mission::TimeToString(m1->GetRecruitTTime());
                ui->myMissions->setItem(static_cast<int>(preL + i), 3,
                    new QTableWidgetItem(QString::fromStdString("Recruit T Time:\n" + time)));

                QPushButton* opr = new QPushButton;
                SetMngMissionOprtButton(opr, m1);
                ui->myMissions->setCellWidget(static_cast<int>(preL + i), 4, opr);
            }
            else
            {
                ui->myMissions->setItem(static_cast<int>(preL + i), 1,
                                        new QTableWidgetItem("Apply for manager"));
                //我的参与方式
                ui->myMissions->setItem(static_cast<int>(preL + i), 2,
                    new QTableWidgetItem(QString::fromStdString(Mission::ApplyMStateToString(
                    s1) ) ) );

                //显示申请状态
                QPushButton* opr = new QPushButton;
                SetMngMissionOprtButton(opr, temp);
                ui->myMissions->setCellWidget(static_cast<int>(preL + i), 4, opr);
            }
        }
        else
        {
            Mission::ApplyMState s2 = temp->GetAplMState(user->GetUserName());
            ui->myMissions->setItem(static_cast<int>(preL + i), 1,
                                    new QTableWidgetItem("Apply for manager"));
            ui->myMissions->setItem(static_cast<int>(preL + i), 2,
                                    new QTableWidgetItem(QString::fromStdString(Mission::ApplyMStateToString(
                                                s2) ) ) );

            std::string time = Mission::TimeToString(
                                   temp->GetRecruitMTime());
            ui->myMissions->setItem(static_cast<int>(preL + i), 3,
                                    new QTableWidgetItem(QString::fromStdString("Recruit M Time:\n" + time)));
            //显示申请状态
            QPushButton* opr = new QPushButton;
            SetMngMissionOprtButton(opr, temp);
            ui->myMissions->setCellWidget(static_cast<int>(preL + i), 4, opr);
        }

        for (int j = 0; j < 5; j++)
        {
            QTableWidgetItem* temp = ui->myMissions->item(static_cast<int>(preL + i), j);

            if (temp != nullptr)
            {
                temp->setTextAlignment(Qt::AlignCenter);
            }
        }


    }

    ui->myMissions->resizeRowsToContents();
}


/*************************************************************************
【函数名称】       PtcpTableInitialize
【函数功能】       参与翻译任务的表格初始化
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void HomePage::PtcpTableInitialize()
{
    ULL preL = (releasedMissions.size() + inChargeMissions.size());

    for (ULL i = 0; i < participatingMissions.size(); i++)
    {
        P_MNG temp = participatingMissions[i];
        ui->myMissions->setItem(static_cast<int>(preL + i), 0,
            new QTableWidgetItem(QString::fromStdString(temp->GetMissionName() ) ) );
        ui->myMissions->setItem(static_cast<int>(preL + i), 1,
            new QTableWidgetItem("Apply for translator."));                   //我的参与方式

        ManageMission::ApplyTState s = temp->GetAplTState(user->GetUserName());
        ui->myMissions->setItem(static_cast<int>(preL + i), 2,
            new QTableWidgetItem(QString::fromStdString(ManageMission::ApplyTStateToString(s) ) ) );

        if (s == ManageMission::A_APPLY_T_SUCCEED)
        {
            P_SUB sub(KEY_SUB(participatingMissions[i], user->GetUserName()));
            ui->myMissions->setItem(static_cast<int>(preL + i), 1,
                new QTableWidgetItem("Translate"));
            ui->myMissions->setItem(static_cast<int>(preL + i), 2,
                new QTableWidgetItem(QString::fromStdString(sub->GetSubMissionStateStr() ) ) );

            std::string DDL = Mission::TimeToString(temp->GetMissionDDL());
            ui->myMissions->setItem(static_cast<int>(preL + i), 3,
                new QTableWidgetItem(QString::fromStdString("Mission DDL:\n" + DDL)));

            QPushButton* opr = new QPushButton;
            SetPtcpMissionOprtButton(opr, sub);
            ui->myMissions->setCellWidget(static_cast<int>(preL + i), 4, opr);
        }
        else if (s == ManageMission::A_APPLYING_T)
        {
            std::string time = Mission::TimeToString(  temp->GetRecruitTTime());
            ui->myMissions->setItem(static_cast<int>(preL + i), 3,
                new QTableWidgetItem(QString::fromStdString("Recruit T Time:\n" + time)));

            QPushButton* opr = new QPushButton;
            SetPtcpMissionOprtButton(opr, temp);
            ui->myMissions->setCellWidget(static_cast<int>(preL + i), 4, opr);
        }
        else
        {
            QPushButton* opr = new QPushButton;
            SetPtcpMissionOprtButton(opr, temp);
            ui->myMissions->setCellWidget(static_cast<int>(preL + i), 4, opr);
        }


        for (int j = 0; j < 5; j++)
        {
            QTableWidgetItem* temp = ui->myMissions->item(static_cast<int>(preL + i), j);

            if (temp != nullptr)
            {
                temp->setTextAlignment(Qt::AlignCenter);
            }
        }

    }

    ui->myMissions->resizeRowsToContents();
}



//******************************页面跳转处理*****************************



/*************************************************************************
【函数名称】       GoMissionHall
【函数功能】       进入任务大厅
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void HomePage::GoMissionHall()
{
    missionHall = new MissionHall(this, user);
    missionHall->setWindowTitle("众包翻译平台-任务大厅");
    connect(missionHall, &MissionHall::s_returnHomePage, this,
            &HomePage::CloseMissionHall);     //任务大厅返回
    missionHall->show();
    this->hide();
}


/*************************************************************************
【函数名称】       CloseMissionHall
【函数功能】       任务大厅返回
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void HomePage::CloseMissionHall()
{
    TableInitialize();
    this->show();

    if (missionHall != nullptr)
    {
        missionHall->close();
    }
}


/*************************************************************************
【函数名称】       GoReleaseMission
【函数功能】       发布任务
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void HomePage::GoReleaseMission()
{
    releasePg  = new ReleaseMission(this, user);
    releasePg->setWindowTitle("众包翻译平台-发布任务");
    connect(this->releasePg, &ReleaseMission::s_rlsCancel, this,
            &HomePage::CloseRelease);                    //发布取消
    connect(this->releasePg, &ReleaseMission::s_rlsSucceed, this,
            &HomePage::CloseRelease);                //发布成功
    releasePg->show();
    this->hide();
}


/*************************************************************************
【函数名称】       CloseRelease
【函数功能】       发布任务页返回
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void HomePage::CloseRelease()
{
    TableInitialize();
    this->show();

    if (releasePg != nullptr)
    {
        releasePg->close();
    }
}


void HomePage::GoMessageBox()
{
    messageBox = new MessageBox(this, user);
    messageBox->setWindowTitle("众包翻译平台-消息盒子");
    connect(this->messageBox, &MessageBox::s_returnLast, this,
            &HomePage::CloseMessageBox);                    //返回

    messageBox->show();
    this->hide();
}

void HomePage::CloseMessageBox()
{
    TableInitialize();
    this->show();

    if (messageBox != nullptr)
    {
        messageBox->close();
    }
}



/*************************************************************************
【函数名称】       GoMyAccount
【函数功能】       进入个人账户页
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void HomePage::GoMyAccount()
{
    userAccount = new UserAccount(this, user);
    userAccount->setWindowTitle("众包翻译平台-个人信息");
    connect(userAccount, &UserAccount::s_returnLast, this,
            &HomePage::CloseAccount);                //个人信息页
    userAccount->show();
    this->hide();
}


/*************************************************************************
【函数名称】       CloseAccount
【函数功能】       个人账户页返回
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void HomePage::CloseAccount()
{
    TableInitialize();
    this->show();

    if (userAccount != nullptr)
    {
        userAccount->close();
    }
}


/*************************************************************************
【函数名称】       ChooseMCancel
【函数功能】       选择负责人取消
【参数】
                  ChooseManager* choosePge      输入
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void HomePage::ChooseMCancel(ChooseManager* choosePge)
{
    this->show();

    if (choosePge != nullptr)
    {
        choosePge->close();
    }
}


/*************************************************************************
【函数名称】       ChooseMSucceed
【函数功能】       选择负责人成功
【参数】
                  ChooseManager* choosePge      输入
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void HomePage::ChooseMSucceed(ChooseManager* choosePge)
{
    TableInitialize();
    this->show();

    if (choosePge != nullptr)
    {
        choosePge->close();
    }
}


/*************************************************************************
【函数名称】       ChooseTCancel
【函数功能】       选择翻译者取消
【参数】
                  ChooseTranslator* choosePge      输入
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void HomePage::ChooseTCancel(ChooseTranslator* choosePge)
{
    this->show();

    if (choosePge != nullptr)
    {
        choosePge->close();
    }
}


/*************************************************************************
【函数名称】       ChooseTSucceed
【函数功能】       选择翻译者和分配任务成功
【参数】
                  ChooseTranslator* choosePge      输入
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void HomePage::ChooseTSucceed(ChooseTranslator* choosePge)
{
    TableInitialize();
    this->show();

    if (choosePge != nullptr)
    {
        choosePge->close();
    }
}


/*************************************************************************
【函数名称】       SubmitTransReturn
【函数功能】       提交译文页返回
【参数】
                  SubmitTranslation* subPge      输入
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void HomePage::SubmitTransReturn(SubmitTranslation* subPge)
{
    TableInitialize();
    this->show();

    if (subPge != nullptr)
    {
        subPge->close();
    }
}


/*************************************************************************
【函数名称】       CheckTransReturn
【函数功能】       审核译文页返回
【参数】
                  CheckTranslation* chkPge      输入
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void HomePage::CheckTransReturn(CheckTranslation* chkPge)
{
    TableInitialize();
    this->show();

    if (chkPge != nullptr)
    {
        chkPge->close();
    }
}


/*************************************************************************
【函数名称】       PayCancel
【函数功能】       支付酬金取消
【参数】
                  PayForMission* payPge      输入
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void HomePage::PayCancel(PayForMission* payPge)
{
    this->show();

    if (payPge != nullptr)
    {
        payPge->close();
    }
}


/*************************************************************************
【函数名称】       PaySucceed
【函数功能】       支付酬金成功
【参数】
                  PayForMission* payPge      输入
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void HomePage::PaySucceed(PayForMission* payPge)
{
    TableInitialize();
    this->show();

    if (payPge != nullptr)
    {
        payPge->close();
    }
}


/*************************************************************************
【函数名称】       RcrtMFailReturn
【函数功能】       招募负责人失败处理页返回
【参数】
                  RcrtMFailProc* pcspge      输入
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void HomePage::RcrtMFailReturn(RcrtMFailProc* pcspge)
{
    TableInitialize();
    this->show();

    if (pcspge != nullptr)
    {
        pcspge->close();
    }
}


/*************************************************************************
【函数名称】       MsnInfoReturn
【函数功能】       任务信息页返回
【参数】
                  MissionInfo* infoPge      输入
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void HomePage::MsnInfoReturn(MissionInfo* infoPge)
{
    this->show();

    if (infoPge != nullptr)
    {
        infoPge->close();
    }
}


/*************************************************************************
【函数名称】       PageRefresh
【函数功能】       页面刷新
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void HomePage::PageRefresh()
{
    TableInitialize();
    this->repaint();
}


/*************************************************************************
【函数名称】       Exit_clicked
【函数功能】       退出登录
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void HomePage::Exit_clicked()
{
    Datum::UpdateDB();
    emit s_returnMain();
    this->close();
}


