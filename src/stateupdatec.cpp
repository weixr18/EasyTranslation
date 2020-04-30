/*************************************************************************
【文件名】                 stateupdatec.cpp
【功能模块和目的】          StateUpdateC类实现
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/



#include "stateupdatec.h"

StateUpdateC::StateUpdateC()
{
}

StateUpdateC::~StateUpdateC()
{
}



//更新任务状态
void StateUpdateC::CheckAndUpdate(Mission& mission)
{
    time_t timer = time(nullptr);
    tm currentTime = *localtime(&timer);
    currentTime.tm_year += 1900;
    currentTime.tm_mon += 1;

    if (mission.GetReleaseState() == Mission::R_RECRUIT_M)
    {
        tm rcrtM = mission.GetRecruitMTime();

        if (TimeOut(currentTime, rcrtM))
        {
            RcrtMJudge(mission);
        }
    }
}

//更新mng任务状态
void StateUpdateC::CheckAndUpdate(ManageMission& mng)
{
    time_t timer = time(nullptr);
    tm currentTime = *localtime(&timer);
    currentTime.tm_year += 1900;
    currentTime.tm_mon += 1;

    if (mng.GetReleaseState() == Mission::R_TRANSLATING)
    {
        tm rcrtT = mng.GetRecruitTTime();

        if (TimeOut(currentTime, rcrtT))
        {
            RcrtTJudge(mng);
        }

        tm msnDDL = mng.GetMissionDDL();

        if (TimeOut(currentTime, msnDDL))
        {
            MissionTimeOutJudge(mng);
        }
    }
}


//招募M判定
bool StateUpdateC::RcrtMJudge(Mission& mission)
{
    if (mission.GetReleaseState() != Mission::R_RECRUIT_M)
    { return false; }

    if (mission.m_MngCandidates.size() > 0)
    {
        mission.SetReleaseState(Mission::R_CHOOSE_M);
    }
    else
    {
        mission.SetReleaseState(Mission::R_RCRT_M_FAILED);
    }

    return true;
}


//招募T判定
bool StateUpdateC::RcrtTJudge(ManageMission& mng)
{
    if (mng.GetReleaseState() != Mission::R_TRANSLATING)
    { return false; }
    else if (mng.GetManageState() != ManageMission::M_RECRUIT_T)
    { return false; }

    if (mng.m_TrsltrCandidates.size() == 0)
    {
        mng.SetManageState(ManageMission::M_RCRT_T_FAILED);
    }
    else
    {
        mng.SetManageState(ManageMission::M_CHS_T_AND_ASSIGN);
    }

    return true;
}


//超时判定
bool StateUpdateC::MissionTimeOutJudge(ManageMission& mng)
{

    if (mng.GetReleaseState() != Mission::R_TRANSLATING)
    { return false; }
    else if (mng.GetManageState() == ManageMission::M_SUBMITTED ||
             mng.GetManageState() == ManageMission::M_ACCOMPLISHED)
    { return false; }

    mng.SetManageState(ManageMission::M_TIME_OUT);
    return true;
}




//时间先后比较
bool StateUpdateC::TimeOut(tm t1, tm t2)
{
    if (t1.tm_year < t2.tm_year)
    { return false; }
    else if (t1.tm_year > t2.tm_year)
    { return true; }
    else
    {
        if (t1.tm_mon < t2.tm_mon)
        { return false; }
        else if (t1.tm_mon > t2.tm_mon)
        { return true; }
        else
        {
            if (t1.tm_mday < t2.tm_mday)
            { return false; }
            else if (t1.tm_mday > t2.tm_mday)
            { return true; }
            else
            {
                if (t1.tm_hour < t2.tm_hour)
                { return false; }
                else if (t1.tm_hour > t2.tm_hour)
                { return true; }
                else
                {
                    if (t1.tm_min < t2.tm_min)
                    { return false; }
                    else if (t1.tm_min > t2.tm_min)
                    { return true; }
                    else
                    {
                        if (t1.tm_sec < t2.tm_sec)
                        { return false; }
                        else
                        { return true; }
                    }
                }
            }
        }
    }
}



