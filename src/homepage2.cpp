/*************************************************************************
【文件名】                 homepage.cpp
【功能模块和目的】          HomePage类实现-PART II
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/

#include "homepage.h"
#include "ui_homepage.h"
#include <QDebug>


/*************************************************************************
【函数名称】       SetRlsMissionOprtButton
【函数功能】       设置发布阶段任务操作按钮
【参数】
                  QPushButton*  btn      输入
                  P_MSN         mission  输入
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void HomePage::SetRlsMissionOprtButton(QPushButton* btn, P_MSN mission)
{
    if (!mission.exist())
    {
        return;
    }

    Mission::ReleaseState state = mission->GetReleaseState();
    QFont bF = btn ->font();
    bF.setBold(true);

    switch (state)
    {
    case Mission::R_RCRT_M_FAILED :
    {
        //招募负责人失败操作页
        btn->setText("Go to proceed.");
        btn->setFont(bF);
        btn->setStyleSheet("QPushButton{background-color:white;}");

        QString name = QString::fromStdString(mission->GetMissionName());
        btn->setProperty("Mission", name);
        connect(btn, &QPushButton::clicked, this, &HomePage::SetBRcrtMFail);
        break;
    }

    case Mission::R_CHOOSE_M :
    {
        //选择负责人页
        btn->setText("Go to choose.");
        btn->setFont(bF);
        btn->setStyleSheet("QPushButton{background-color:white;}");

        QString name = QString::fromStdString(mission->GetMissionName());
        btn->setProperty("Mission", name);
        connect(btn, &QPushButton::clicked, this, &HomePage::SetBChooseM);
        break;
    }

    case Mission::R_WAIT_FOR_PAY :
    {
        //支付页
        btn->setText("Go to pay");
        btn->setFont(bF);
        btn->setStyleSheet("QPushButton{background-color:white;}");

        QString name = QString::fromStdString(mission->GetMissionName());
        btn->setProperty("Mission", name);
        connect(btn, &QPushButton::clicked, this, &HomePage::SetBPayForMission);
        break;
    }

    case Mission::R_RECRUIT_M :
    case Mission::R_CANCELED :
    case Mission::R_TRANSLATING :
    case Mission::R_ACCOMPLISHED :
    {
        //查看详情页
        btn->setText("View Details");
        btn->setStyleSheet("QPushButton{background-color:white;}");

        QString name = QString::fromStdString(mission->GetMissionName());
        btn->setProperty("Mission", name);
        connect(btn, &QPushButton::clicked, this, &HomePage::SetBMissionInfo);
        break;
    }

    }
}


/*************************************************************************
【函数名称】       SetMngMissionOprtButton
【函数功能】       设置负责阶段任务操作按钮（+1重载）
【参数】
                  QPushButton*  btn      输入
                  P_MNG         mng      输入
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void HomePage::SetMngMissionOprtButton(QPushButton* btn, P_MNG mng)
{
    if (!mng.exist())
    {
        return;
    }

    QFont bF = btn ->font();
    bF.setBold(true);

    switch (mng->GetManageState())
    {
    case ManageMission::M_RECRUIT_T :
    {
        //设置报名截止时间页【未添加】, 默认为确定负责人时间的3天后
        btn->setText("Set recruit time.");
        btn->setFont(bF);
        btn->setStyleSheet("QPushButton{background-color:white;}");
        break;
    }

    case ManageMission::M_RCRT_T_FAILED :
    {
        //招募译者失败处理页【未添加】
        btn->setText("Go to proceed.");
        btn->setFont(bF);
        btn->setStyleSheet("QPushButton{background-color:white;}");
        break;
    }

    case ManageMission::M_CHS_T_AND_ASSIGN :
    {
        //选择译者页
        btn->setText("Chooce and assign.");
        btn->setFont(bF);
        btn->setStyleSheet("QPushButton{background-color:white;}");

        QString name = QString::fromStdString(mng->GetMissionName());
        btn->setProperty("MngMission", name);
        connect(btn, &QPushButton::clicked, this, &HomePage::SetBChooseT);
        break;
    }

    case ManageMission::M_CHECKING :
    {
        //查看译文和反馈页
        btn->setText("Check and feedback.");
        btn->setFont(bF);
        btn->setStyleSheet("QPushButton{background-color:white;}");

        QString name = QString::fromStdString(mng->GetMissionName());
        btn->setProperty("MngMission", name);
        connect(btn, &QPushButton::clicked, this, &HomePage::SetBCheckTrans);
        break;
    }

    case ManageMission::M_TIME_OUT :
    case ManageMission::M_SUBMITTED :
    case ManageMission::M_ACCOMPLISHED :
    {
        //查看详情页
        btn->setText("View Details");
        btn->setStyleSheet("QPushButton{background-color:white;}");

        QString name = QString::fromStdString(mng->GetMissionName());
        btn->setProperty("MngMission", name);
        connect(btn, &QPushButton::clicked, this, &HomePage::SetBMissionInfo);
        break;
    }

    }
}

/*************************************************************************
【函数名称】       SetMngMissionOprtButton
【函数功能】       设置负责阶段任务操作按钮（+2重载）
【参数】
                  QPushButton*  btn      输入
                  P_MSN         mission  输入
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void HomePage::SetMngMissionOprtButton(QPushButton* btn, P_MSN mission)
{
    if (!mission.exist())
    { return; }

    Mission::ApplyMState aplState = mission->GetAplMState(user->GetUserName());
    QFont bF = btn ->font();
    bF.setBold(true);

    switch (aplState)
    {
    case Mission::A_APPLYING_M :
    case Mission::A_APPLY_M_FAILED :
    {
        //查看详情页
        btn->setText("View Details");
        btn->setStyleSheet("QPushButton{background-color:white;}");

        QString name = QString::fromStdString(mission->GetMissionName());
        btn->setProperty("Mission", name);
        connect(btn, &QPushButton::clicked, this, &HomePage::SetBMissionInfo);
        break;
    }

    default:
        qDebug() << "Error: HomePage::setMngMissionOprButton";
        break;
    }
}


/*************************************************************************
【函数名称】       SetPtcpMissionOprtButton
【函数功能】       设置参加翻译任务操作按钮（+2重载）
【参数】
                  QPushButton*  btn      输入
                  P_SUB         sub      输入
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void HomePage::SetPtcpMissionOprtButton(QPushButton* btn, P_SUB sub)
{
    if (!sub.exist())
    {
        return;
    }

    QFont bF = btn ->font();
    bF.setBold(true);

    switch (sub->GetSubMissionState())
    {
    case SubMission::T_WAIT_FOR_TRANS :
    case SubMission::T_WAIT_FOR_MODIFY :
    case SubMission::T_SUBMITTED :
    {
        //设置翻译/修改页
        btn->setText("Translate / Modify");
        btn->setFont(bF);
        btn->setStyleSheet("QPushButton{background-color:white;}");

        QString name = QString::fromStdString(sub->GetMissionName());
        btn->setProperty("SubMission", name);
        connect(btn, &QPushButton::clicked, this, &HomePage::SetBSubTrans);
        break;
    }

    case SubMission::T_ACCEPTED :
    case SubMission::T_ACCOMPLISHED :
    {
        //查看详情页
        btn->setText("View Details");
        btn->setStyleSheet("QPushButton{background-color:white;}");

        QString name = QString::fromStdString(sub->GetMissionName());
        btn->setProperty("SubMission", name);
        connect(btn, &QPushButton::clicked, this, &HomePage::SetBMissionInfo);
        break;
    }
    }
}


/*************************************************************************
【函数名称】       SetPtcpMissionOprtButton
【函数功能】       设置参加翻译任务操作按钮（+1重载）
【参数】
                  QPushButton*  btn      输入
                  P_MNG         mng      输入
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void HomePage::SetPtcpMissionOprtButton(QPushButton* btn, P_MNG mng)
{
    if (!mng.exist())
    {
        return;
    }

    ManageMission::ApplyTState aplTState = mng->GetAplTState(user->GetUserName());

    switch (aplTState)
    {
    case ManageMission::A_APPLYING_T :
    case ManageMission::A_APPLY_T_FAILED :
    {
        //查看详情页
        btn->setText("View Details");
        btn->setStyleSheet("QPushButton{background-color:white;}");

        QString name = QString::fromStdString(mng->GetMissionName());
        btn->setProperty("MngMission", name);
        connect(btn, &QPushButton::clicked, this, &HomePage::SetBMissionInfo);
        break;
    }

    default:
        qDebug() << "Error: HomePage::setMngMissionOprButton";
        break;
    }
}


/*************************************************************************
【函数名称】       SetBChooseM
【函数功能】       设置选择负责人按钮
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void HomePage::SetBChooseM()
{
    std::string s = sender()->property("Mission").toString().toStdString();
    P_MSN mission = s;

    if (mission.exist())
    {
        ChooseManager* choosePge = new ChooseManager(this, mission);
        choosePge->show();
        connect(choosePge, &ChooseManager::s_chsCancel, this, &HomePage::ChooseMCancel);
        connect(choosePge, &ChooseManager::s_chsSucceed, this,
                &HomePage::ChooseMSucceed);
    }
}


/*************************************************************************
【函数名称】       SetBPayForMission
【函数功能】       设置支付按钮
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void HomePage::SetBPayForMission()
{
    std::string s = sender()->property("Mission").toString().toStdString();
    P_MSN mission = s;

    if (mission.exist())
    {
        PayForMission* pay = new PayForMission(this, mission);
        pay->show();
        connect(pay, &PayForMission::s_canceled, this, &HomePage::PayCancel);
        connect(pay, &PayForMission::s_succeed, this, &HomePage::PaySucceed);
    }
}


/*************************************************************************
【函数名称】       SetBCheckTrans
【函数功能】       设置检查译文按钮
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void HomePage::SetBCheckTrans()
{
    std::string s2 = sender()->property("MngMission").toString().toStdString();
    P_MNG mng = s2;

    if (mng.exist())
    {
        CheckTranslation* chkPge = new CheckTranslation(this, mng);
        chkPge->setWindowTitle("众包翻译平台-审核译文");
        chkPge->show();
        connect(chkPge, &CheckTranslation::s_return, this, &HomePage::CheckTransReturn);
        return;
    }
}


/*************************************************************************
【函数名称】       SetBChooseT
【函数功能】       设置选择翻译者按钮
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void HomePage::SetBChooseT()
{
    std::string s2 = sender()->property("MngMission").toString().toStdString();
    P_MNG mng = s2;

    if (mng.exist())
    {
        ChooseTranslator* choosePge = new ChooseTranslator(this, mng);
        choosePge->show();
        connect(choosePge, &ChooseTranslator::s_chsCancel, this,
                &HomePage::ChooseTCancel);
        connect(choosePge, &ChooseTranslator::s_chsSucceed, this,
                &HomePage::ChooseTSucceed);
        return;
    }
}


/*************************************************************************
【函数名称】       SetBSubTrans
【函数功能】       设置提交译文按钮
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void HomePage::SetBSubTrans()
{
    std::string s3 = sender()->property("SubMission").toString().toStdString();
    P_SUB sub = KEY_SUB(s3, user->GetUserName());

    if (sub.exist())
    {
        SubmitTranslation* submitPge = new SubmitTranslation(this, sub);
        submitPge->setWindowTitle("众包翻译平台-提交译文");
        submitPge->show();
        connect(submitPge, &SubmitTranslation::s_return, this,
                &HomePage::SubmitTransReturn);
        return;
    }
}


/*************************************************************************
【函数名称】       SetBRcrtMFail
【函数功能】       设置招募负责人失败处理按钮
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void HomePage::SetBRcrtMFail()
{
    std::string s1 = sender()->property("Mission").toString().toStdString();
    P_MSN mission = s1;

    if (mission.exist())
    {
        RcrtMFailProc* process = new RcrtMFailProc(this, mission);
        process->show();
        connect(process, &RcrtMFailProc::s_returnLast, this,
                &HomePage::RcrtMFailReturn);
        return;
    }
}


/*************************************************************************
【函数名称】       SetBMissionInfo
【函数功能】       设置任务页按钮
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void HomePage::SetBMissionInfo()
{
    std::string s1 = sender()->property("Mission").toString().toStdString();
    P_MSN mission = s1;

    if (mission.exist())
    {
        MissionInfo* info = new MissionInfo(this, mission);
        info->show();
        connect(info, &MissionInfo::s_return, this, &HomePage::MsnInfoReturn);
        return;
    }

    std::string s2 = sender()->property("MngMission").toString().toStdString();
    P_MNG mng = s2;

    if (mng.exist())
    {
        MissionInfo* info = new MissionInfo(this, mng);
        info->show();
        connect(info, &MissionInfo::s_return, this, &HomePage::MsnInfoReturn);
        return;
    }

    std::string s3 = sender()->property("SubMission").toString().toStdString();
    P_SUB sub = KEY_SUB(s3, user->GetUserName());

    if (sub.exist())
    {
        MissionInfo* info = new MissionInfo(this, sub);
        info->show();
        connect(info, &MissionInfo::s_return, this, &HomePage::MsnInfoReturn);
        return;
    }
}


