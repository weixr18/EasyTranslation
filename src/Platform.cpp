/*************************************************************************
【文件名】                 Platform.cpp
【功能模块和目的】          Platform类实现-PART I
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/


#include "Platform.h"
#include <iostream>


Platform::Platform() {}
Platform::Platform(const Platform& p) {};
Platform::~Platform() {}
Platform& Platform::operator=(Platform& p) { return *this; }


//用户注册
bool Platform::u_regist(P_USER& p_user, const std::string& username,
                        const std::string& password,
                        const int& score, const std::string& realName, const std::string& IDNum,
                        const std::string& email)
{
    User* user1 = new User(username, password, score, realName, IDNum, email);

    if (Datum::AddNewUser(*user1))
    {
        p_user = user1;
        cout << "Datum::loadedUsers.size(): " << Datum::s_LoadedUsers.size() << endl;
        delete user1; user1 = nullptr;
        return true;
    }

    delete user1; user1 = nullptr;
    return false;
}


//判断登录是否成功
bool Platform::u_login_succeed(const std::string& username,
                               const std::string& password)
{
    for (auto user : Datum::s_LoadedUsers)
    {
        if (user.second.GetUserName() == username &&
            user.second.PasswordMatch(password))
        { return true; }
    }

    return Datum::s_dbop.NameMatchPassword(username, password);
}


//用户发布任务
bool Platform::u_release_mission(P_USER& p_releaser, P_MSN& p_mission,
                                 const std::string missionName, const std::string introduction,
                                 const std::string srcText, const tm recruitMTime,
                                 const tm missionDDL, const int awardAmount,
                                 const Mission::Language srcLanguage,
                                 const Mission::Language tarLanguage)
{
    Mission* mission1 = new Mission(missionName, p_releaser->GetUserName(),
                                    introduction,
                                    srcText, recruitMTime, missionDDL, awardAmount, Mission::R_RECRUIT_M,
                                    srcLanguage, tarLanguage);

    if (!Datum::MissionNameExist(mission1->GetMissionName()) &&
        p_releaser.exist())
    {
        if (Datum::AddNewMission(*mission1))
        {
            p_mission = mission1;
            cout << "Add mission: " << p_mission->GetMissionName() << endl;
            p_releaser->GetRlsMissions().push_back(p_mission->GetMissionName());
            cout << "Datum::loadedMissions.size(): " << Datum::s_LoadedMissions.size() <<
                 endl;

            delete mission1; mission1 = nullptr;
            return true;
        }
    }

    delete mission1; mission1 = nullptr;
    return false;
}


//用户申请成为负责人
bool Platform::u_apl_manager(const P_USER& applyer, const P_MSN& mission)
{
    if (applyer->GetUserName() == mission->GetReleaser())
    { return false; }
    else if (mission->GetReleaseState() != Mission::R_RECRUIT_M)
    { return false; }
    else if (Datum::V_Find(applyer->GetInchgMissions(), mission->GetMissionName()))
    { return false; }
    else if (Datum::V_Find(mission->m_MngCandidates, applyer->GetUserName()))
    { return false; }

    applyer->GetInchgMissions().push_back(mission->GetMissionName());
    mission->m_MngCandidates.push_back(applyer->GetUserName());

    std::string aplMsg =
        applyer->GetUserName() + " is applying for the manager of your mission "
        + mission->GetMissionName() +
        ".";
    Datum::AddNewMessage(applyer->GetUserName(), mission->GetReleaser(), aplMsg);

    return true;
}


//发布者选择负责人
bool Platform::r_choose_manager(const P_USER& releaser, const P_MSN& mission,
                                const P_USER& manager, P_MNG& mng)
{
    if (!releaser.exist() || !mission.exist() || !manager.exist())
    { return false; }
    else if (mission->GetReleaser() != releaser->GetUserName())
    { return false; }
    else if (mission->GetReleaseState() != Mission::R_CHOOSE_M)
    { return false; }
    else if (!Datum::V_Find(mission->m_MngCandidates, manager->GetUserName()))
    { return false; }
    else if (!Datum::V_Find(manager->GetInchgMissions(), mission->GetMissionName()))
    { return false; }

    for (auto user : mission->m_MngCandidates)
    {
        if (!P_USER(user).exist())
        {
            return false;
        }
    }

    //设置原任务的manager releasestate
    mission->SetManager(manager->GetUserName());
    mission->SetReleaseState(Mission::R_TRANSLATING);

    //用原任务生成新的ManageMission对象
    const ManageMission* temp = new ManageMission(*mission);

    //将原表中的原任务换为新表中的新任务
    if (!Datum::MissionTrsfMngMission(*mission, *temp))
    {
        mng = P_MNG("");
        delete temp; temp = nullptr;
        return false;
    }

    mng = temp;
    delete temp; temp = nullptr;


    //获取当前时间并将招募时间设为3天后
    time_t timer = time(nullptr);                           //系统日历时间
    timer += 259200;                                        //推移到3天后
    tm add3Time = *localtime(&timer);
    add3Time.tm_year += 1900;
    add3Time.tm_mon += 1;
    mng->SetRecruitTTime(add3Time);

    mng->SetManageState(ManageMission::M_RECRUIT_T);				   //设置任务的managestate

    //发送成功和失败消息
    std::string scsMsg =
        "Congratulations! You are seleted as the manager of mission "
        + mng->GetMissionName() +
        ". You can go to set the recruit translator time now.";
    Datum::AddNewMessage(mng->GetReleaser(), manager->GetUserName(), scsMsg);

    std::string failMsg =
        "Sorry. You are not seleted as the manager of mission "
        + mng->GetMissionName() + ". ";
    for (auto user : mission->m_MngCandidates)
    {
        if (user != manager->GetUserName())
        {
            Datum::AddNewMessage(mng->GetReleaser(), user, failMsg);
        }
    }

    return true;
}


//用户申请成为翻译者
bool Platform::u_apl_transltr(const P_USER& p_user, const P_MNG& p_mng)
{
    if (p_user->GetUserName() == p_mng->GetReleaser())
    { return false; }
    else if (p_user->GetUserName() == p_mng->GetManager())
    { return false; }
    else if (p_mng->GetReleaseState() != Mission::R_TRANSLATING)
    { return false; }
    else if (p_mng->GetManageState() != ManageMission::M_RECRUIT_T)
    { return false; }
    else if (Datum::V_Find(p_user->GetPtcpMissions(),
                           p_mng->GetMissionName()))
    { return false; }
    else if (Datum::V_Find(p_mng->m_TrsltrCandidates, p_user->GetUserName()))
    { return false; }

    p_mng->m_TrsltrCandidates.push_back(p_user->GetUserName());
    p_user->GetPtcpMissions().push_back(p_mng->GetMissionName());

    std::string aplMsg =
        p_user->GetUserName() + " is applying for the translator of your managing mission "
        + p_mng->GetMissionName() +
        ".";
    Datum::AddNewMessage(p_user->GetUserName(), p_mng->GetReleaser(), aplMsg);

    return true;
}


//负责人设置招募翻译者截止时间
bool Platform::m_set_recruit_T_time(const P_USER& manager, const P_MNG& mng,
                                    const tm& recruitTTime)
{
    if (!manager.exist() || !mng.exist())
    { return false; }
    else if (mng->GetManageState() != ManageMission::M_CHS_T_AND_ASSIGN)
    { return false; }

    mng->SetRecruitTTime(recruitTTime);
    return true;
}


//负责人选择翻译者
bool Platform::m_choose_tranlator(const P_USER& manager, const P_MNG& mng,
                                  const std::vector<P_USER>& translators)
{
    //安全检查
    if (!manager.exist() || !mng.exist())
    { return false; }
    else if (mng->GetManageState() != ManageMission::M_CHS_T_AND_ASSIGN)
    { return false; }

    ULL trslNum = translators.size();

    for (ULL i = 0; i != trslNum; i++)
    {
        if (!translators[i].exist())
        { return false; }
        else if (!Datum::V_Find<std::string>(mng->m_TrsltrCandidates,
                                             translators[i]->GetUserName()))
        { return false; }
        else if (!Datum::V_Find<std::string>(translators[i]->GetPtcpMissions(),
                                             mng->GetMissionName()))
        { return false; }
    }

    //信息处理
    for (ULL i = 0; i != trslNum; i++)
    {
        mng->m_Translators.push_back(translators[i]->GetUserName());
        cout << "succeed choose" << translators[i]->GetUserName() << endl;
    }

    //发送成功和失败消息
    std::string scsMsg =
        "Congratulations! You are seleted as the translator of mission "
        + mng->GetMissionName() +
        ". You can go to view source text and submit translation now.";

    std::string failMsg =
        "Sorry. You are not seleted as the translator of mission "
        + mng->GetMissionName() + ". ";

    for (auto user : mng->m_TrsltrCandidates)
    {
        if (!Datum::V_Find(mng->m_Translators, user))
        {
            Datum::AddNewMessage(mng->GetManager(), user, failMsg);
        }
        else
        {
            Datum::AddNewMessage(mng->GetManager(), user, scsMsg);
        }
    }

    return true;
}


//负责人分配任务
bool Platform::m_assign_mission(const P_USER& manager, const P_MNG& mng,
                                const ASSIGN_MIS& assign)
{
    if (!manager.exist() || !mng.exist())
    { return false; }
    else if (mng->GetManageState() != ManageMission::M_CHS_T_AND_ASSIGN)
    { return false; }
    else if (mng->GetManager() != manager->GetUserName())
    { return false; }

    ManageMission m(*mng);

    cout << "mng->translators.size(): " << mng->m_Translators.size() << endl;
    cout << "m.translators.size(): " << m.m_Translators.size() << endl;

    Datum::MngCreateSubMsn(m, assign);

    for (auto kvpair : assign)
    {
        KEY_SUB key(mng->GetMissionName(), kvpair.first);
        mng->m_SubMissions.push_back(key);
    }

    mng->SetManageState(ManageMission::M_CHECKING);
    return true;
}



//译者提交译文
bool Platform::t_submit_translation(const P_USER& translator,
                                    const P_SUB& p_sub,
                                    const std::string& translation)
{
    if (!translator.exist() || !p_sub.exist())
    { return false; }
    else if (p_sub->GetSubMissionState() != SubMission::T_WAIT_FOR_TRANS &&
             p_sub->GetSubMissionState() != SubMission::T_WAIT_FOR_MODIFY)
    { return false; }
    else if (translator->GetUserName() != p_sub->GetTranslator())
    { return false; }

    TRANSLATION_P p(translation, std::string(""));
    p_sub->m_History.push_back(p);
    p_sub->SetSubMissionState(SubMission::T_SUBMITTED);

    //发送消息
    std::string Msg =
        "I have submitted a translation. Please check if it could be accepted.";
    Datum::AddNewMessage(translator->GetUserName(), p_sub->GetManager(), Msg);

    return true;
}


//负责人提交反馈
bool Platform::m_submit_feedback(const P_USER& manager, const P_SUB& p_sub,
                                 const std::string& feedback)
{
    if (!manager.exist() || !p_sub.exist())
    { return false; }
    else if (p_sub->GetSubMissionState() != SubMission::T_SUBMITTED)
    { return false; }
    else if (manager->GetUserName() != p_sub->GetManager())
    { return false; }
    else if (p_sub->m_History.size() < 1)
    { return false; }

    TRANSLATION_P p = p_sub->m_History.back();

    if (p.first == std::string(""))
    { return false; }

    p.second = feedback;
    p_sub->m_History.pop_back();
    p_sub->m_History.push_back(p);
    p_sub->SetSubMissionState(SubMission::T_WAIT_FOR_MODIFY);

    //发送消息
    std::string Msg =
        "Your Translation has a feedback. Please read.";
    Datum::AddNewMessage(manager->GetUserName(), p_sub->GetTranslator(), Msg);

    return true;
}


//负责人接受译文
bool Platform::m_accept_translation(const P_USER& manager, const P_SUB& p_sub)
{
    if (!manager.exist() || !p_sub.exist())
    { return false; }
    else if (p_sub->GetSubMissionState() != SubMission::T_WAIT_FOR_MODIFY)
    { return false; }
    else if (manager->GetUserName() != p_sub->GetManager())
    { return false; }
    else if (p_sub->m_History.size() < 1)
    { return false; }

    TRANSLATION_P p = p_sub->m_History.back();

    if (p.first == std::string(""))
    { return false; }

    p_sub->SetTranslation(p.first);
    p_sub->SetSubMissionState(SubMission::T_ACCEPTED);

    //发送消息
    std::string Msg =
        "Your Translation is accepted. Thank you for your work.";
    Datum::AddNewMessage(manager->GetUserName(), p_sub->GetTranslator(), Msg);

    return true;
}


