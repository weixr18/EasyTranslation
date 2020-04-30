/*************************************************************************
【文件名】                 Platform.cpp
【功能模块和目的】          Platform类实现-PART II
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/

#include "Platform.h"
#include <iostream>


//负责人组合译文并提交
bool Platform::m_last_submittal(const P_USER& manager, const P_MNG& mng,
                                const std::string& allTrans)
{
    if (!manager.exist() || !mng.exist())
    { return false; }
    else if (mng->GetManageState() != ManageMission::M_CHECKING)
    { return false; }
    else if (manager->GetUserName() != mng->GetManager())
    { return false; }
    else if (allTrans == std::string(""))
    { return false; }
    else if (mng->m_SubMissions.size() < 1)
    { return false; }

    for (ULL i = 0; i != mng->m_SubMissions.size(); i++)
    {
        P_SUB ps(mng->m_SubMissions[i]);

        if (!ps.exist())
        { return false; }
        else if (ps->GetSubMissionState() != SubMission::T_ACCEPTED)
        { return false; }
        else if (ps->GetTranslation() == std::string(""))
        { return false; }
    }

    mng->SetLastTranslation(allTrans);
    mng->SetManageState(ManageMission::M_SUBMITTED);
    mng->SetReleaseState(Mission::R_WAIT_FOR_PAY);

    //发送消息
    std::string Msg =
        "I have submitted the whole translation of " + mng->GetMissionName() +
        " . Please check.";
    Datum::AddNewMessage(manager->GetUserName(), mng->GetReleaser(), Msg);

    return true;
}


//发布者付钱
bool Platform::r_pay_award(const P_USER& releaser, const P_MNG& mng)
{
    //操作可行性判断
    if (!releaser.exist() || !mng.exist())
    { return false; }
    else if (mng->GetReleaseState() != Mission::R_WAIT_FOR_PAY)
    { return false; }
    else if (mng->GetReleaser() != releaser->GetUserName())
    { return false; }
    else if (mng->m_Translators.size() < 1)
    { return false; }
    else if (releaser->GetBalance() < mng->GetAwardAmount())
    { return false; }

    P_USER manager = mng->GetManager();

    if (!mng.exist())
    { return false; }

    for (auto key : mng->m_SubMissions)
    {
        P_SUB sub = key;

        if (!sub.exist())
        { return false; }
    }

    //付钱 加积分
    double awardSum = mng->GetAwardAmount();
    double mAward = awardSum * 0.3;
    double sumwork = mng->GetSrcText().size();

    releaser->Pay(awardSum);
    manager->GetPay(mAward);

    for (auto submission : mng->m_SubMissions )
    {
        P_USER tempu = submission.second;
        P_SUB ptemp = submission;
        double contribution = ptemp->GetSrcSubText().size() / sumwork;
        double trslAward = (awardSum * 0.7) * contribution;
        tempu->GetPay(trslAward);
        tempu->ScorePlus();
    }

    //任务状态设置
    mng->SetReleaseState(Mission::R_ACCOMPLISHED);
    mng->SetManageState(ManageMission::M_ACCOMPLISHED);

    for (auto key : mng->m_SubMissions)
    {
        P_SUB sub = key;
        sub->SetSubMissionState(SubMission::T_ACCOMPLISHED);
    }

    //发送消息
    std::string Msg =
        "I have already paid for the mission " + mng->GetMissionName() +
        " . Thanks for your work.";
    Datum::AddNewMessage(releaser->GetUserName(), mng->GetManager(), Msg);

    for (auto user : mng->m_Translators)
    {
        Datum::AddNewMessage(releaser->GetUserName(), user, Msg);
    }

    return true;
}


//任务大厅可见性判断_msn
bool Platform::msn_show_in_user_hall(const P_MSN& p_mission,
                                     const P_USER& p_user)
{
    if (!p_mission.exist() || !p_user.exist())
    { return false; }

    if (Datum::V_Find(p_user->GetRlsMissions(), p_mission->GetMissionName()) ||
        Datum::V_Find(p_user->GetInchgMissions(), p_mission->GetMissionName()))
    { return false; }
    else if (p_mission->GetReleaseState() == Mission::R_CANCELED ||
             p_mission->GetReleaseState() == Mission::R_CHOOSE_M ||
             p_mission->GetReleaseState() == Mission::R_RCRT_M_FAILED)
    { return false; }

    return true;
}

//任务大厅可见性判断_mng
bool Platform::mng_show_in_user_hall(const P_MNG& p_mng, const P_USER& p_user)
{
    if (!p_mng.exist() || !p_user.exist())
    { return false; }
    else if (Datum::V_Find(p_user->GetRlsMissions(), p_mng->GetMissionName()) ||
             Datum::V_Find(p_user->GetInchgMissions(), p_mng->GetMissionName()) ||
             Datum::V_Find(p_user->GetPtcpMissions(), p_mng->GetMissionName()))
    { return false; }

    else if (p_mng->GetReleaseState() == Mission::R_CANCELED ||
             p_mng->GetReleaseState() == Mission::R_CHOOSE_M ||
             p_mng->GetReleaseState() == Mission::R_RCRT_M_FAILED)
    { return false; }
    else if (p_mng->GetReleaseState() == Mission::R_TRANSLATING &&
             (p_mng->GetManageState() == ManageMission::M_RCRT_T_FAILED ||
              p_mng->GetManageState() == ManageMission::M_TIME_OUT) )
    { return false; }

    else  { return true; }
}

//任务招募M情况判定
bool Platform::msn_rct_M_judge(const P_MSN& mission)
{
    if (!mission.exist())
    { return false; }
    else if (mission->GetReleaseState() != Mission::R_RECRUIT_M)
    { return false; }

    if (mission->m_MngCandidates.size() > 0)
    {
        mission->SetReleaseState(Mission::R_CHOOSE_M);
    }
    else
    {
        mission->SetReleaseState(Mission::R_RCRT_M_FAILED);
    }

    return true;
}

//任务招募T情况判定
bool Platform::msn_rct_T_judge(const P_MNG& mng)
{
    if (!mng.exist())
    { return false; }
    else if (mng->GetReleaseState() != Mission::R_TRANSLATING)
    { return false; }
    else if (mng->GetManageState() != ManageMission::M_RECRUIT_T)
    { return false; }

    if (mng->m_TrsltrCandidates.size() == 0)
    {
        mng->SetManageState(ManageMission::M_RCRT_T_FAILED);
    }
    else
    {
        mng->SetManageState(ManageMission::M_CHS_T_AND_ASSIGN);
    }

    return true;
}


//任务超时处理
bool Platform::msn_time_out(const P_MNG& mng)
{
    if (!mng.exist())
    { return false; }
    else if (mng->GetReleaseState() != Mission::R_TRANSLATING)
    { return false; }
    else if (mng->GetManageState() == ManageMission::M_SUBMITTED ||
             mng->GetManageState() == ManageMission::M_ACCOMPLISHED)
    { return false; }

    mng->SetManageState(ManageMission::M_TIME_OUT);
    return true;

}


//负责人取消任务
bool Platform::r_cancel_mission(const P_USER& releaser, const P_MSN& mission)
{
    if (!releaser.exist() || !mission.exist())
    { return false; }
    else if (mission->GetReleaseState() != Mission::R_RCRT_M_FAILED)
    {
        return false;
    }

    mission->SetReleaseState(Mission::R_CANCELED);
    return true;
}



bool Platform::r_rcrt_M_time_extend(const P_USER &releaser, const P_MSN mission, const tm& time)
{
    if (!releaser.exist() || !mission.exist())
    { return false; }
    else if (mission->GetReleaseState() != Mission::R_RCRT_M_FAILED)
    {
        return false;
    }

    mission->SetRecruitMTime(time);
    mission->SetReleaseState(Mission::R_RECRUIT_M);
    return true;
}


bool Platform::m_rcrt_T_time_extend(const P_USER &manager, const P_MNG& mng, const tm& time)
{
    if (!manager.exist() || !mng.exist())
    { return false; }
    else if (mng->GetManageState() != ManageMission::M_RCRT_T_FAILED &&
             mng->GetManageState() != ManageMission::M_RECRUIT_T)
    {
        return false;
    }

    mng->SetRecruitTTime(time);
    mng->SetManageState(ManageMission::M_RECRUIT_T);
    return true;
}


bool Platform::userAbleToManage(P_USER &user)
{
    return (user->GetScore() >= 10);
}

