/*************************************************************************
【文件名】                 mission.cpp
【功能模块和目的】          Mission类实现-PART II
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/

#include "mission.h"
#include <iostream>

/*************************任务大厅相关函数*************************/

//任务大厅展示状态
std::string Mission::GetShowingMode() const
{
    switch (m_ReleaseState)
    {
    case Mission::R_RECRUIT_M :
    {
        return std::string("Recruiting Manager");                  //正在招募负责人
    }

    case Mission::R_RCRT_M_FAILED :
    case Mission::R_CHOOSE_M :
    case Mission::R_CANCELED :
    {
        return std::string();                                                       //不显示
    }

    default :
        return std::string();
    }
}

//用户查询申请状态
Mission::ApplyMState Mission::GetAplMState(const std::string& username)
{
    /*if (std::find(m_MngCandidates.begin(), m_MngCandidates.end(), username) ==
        m_MngCandidates.end())
    {
        return Mission::A_NOT_APPLYING_M;
    }*/

    switch (GetReleaseState())
    {
    case Mission::R_RECRUIT_M :
    case Mission::R_CHOOSE_M :
        return Mission::A_APPLYING_M;

    case Mission::R_RCRT_M_FAILED :
    case Mission::R_CANCELED :
        return Mission::A_APPLY_M_FAILED;

    case Mission::R_TRANSLATING :
    case Mission::R_WAIT_FOR_PAY :
    case Mission::R_ACCOMPLISHED :
        return Mission::A_NOT_APPLYING_M;
    }

    return Mission::A_NOT_APPLYING_M;
}


/********************通用函数***********************/

//通用int转tm
tm Mission::IntToTime(int year, int month, int date, int hour, int minute,
                      int second)
{
    tm time;
    time.tm_year = year;
    time.tm_mon = month;
    time.tm_mday = date;
    time.tm_hour = hour;
    time.tm_min = minute;
    time.tm_sec = second;
    return time;
}

//通用tm转string
std::string Mission::TimeToString(const tm& time)
{
    std::string s(std::to_string(time.tm_year) + ".");

    if (time.tm_mon < 10)
    {
        s += std::to_string(0);
        s += std::to_string(time.tm_mon);
    }
    else
    {
        s += std::to_string(time.tm_mon);
    }

    s += ".";


    if (time.tm_mday < 10)
    {
        s += std::to_string(0);
        s += std::to_string(time.tm_mday);
    }
    else
    {
        s += std::to_string(time.tm_mday);
    }

    s += " ";


    if (time.tm_hour < 10)
    {
        s += std::to_string(0);
        s += std::to_string(time.tm_hour);
    }
    else
    {
        s += std::to_string(time.tm_hour);
    }

    s += ":";


    if (time.tm_min < 10)
    {
        s += std::to_string(0);
        s += std::to_string(time.tm_min);
    }
    else
    {
        s += std::to_string(time.tm_min);
    }

    s += ":";

    if (time.tm_sec < 10)
    {
        s += std::to_string(0);
        s += std::to_string(time.tm_sec);
    }
    else
    {
        s += std::to_string(time.tm_sec);
    }

    return s;
}


//通用string转tm
tm Mission::StringToTime(const std::string& sTime)
{
    const char* pStart = sTime.c_str();

    char szYear[5], szMonth[3], szDay[3], szHour[3], szMin[3], szSec[3];

    szYear[0] = *pStart;
    pStart++;
    szYear[1] = *pStart;
    pStart++;
    szYear[2] = *pStart;
    pStart++;
    szYear[3] = *pStart;
    pStart++;
    szYear[4] = 0x0;
    pStart++;

    szMonth[0] = *pStart;
    pStart++;
    szMonth[1] = *pStart;
    pStart++;
    szMonth[2] = 0x0;
    pStart++;

    szDay[0] = *pStart;
    pStart++;
    szDay[1] = *pStart;
    pStart++;
    szDay[2] = 0x0;
    pStart++;

    szHour[0] = *pStart;
    pStart++;
    szHour[1] = *pStart;
    pStart++;
    szHour[2] = 0x0;
    pStart++;

    szMin[0] = *pStart;
    pStart++;
    szMin[1] = *pStart;
    pStart++;
    szMin[2] = 0x0;
    pStart++;

    szSec[0] = *pStart;
    pStart++;
    szSec[1] = *pStart;
    pStart++;
    szSec[2] = 0x0;

    tm tmObj;

    tmObj.tm_year  = atoi(szYear);
    tmObj.tm_mon   = atoi(szMonth);
    tmObj.tm_mday  = atoi(szDay);
    tmObj.tm_hour  = atoi(szHour);
    tmObj.tm_min   = atoi(szMin);
    tmObj.tm_sec   = atoi(szSec);
    tmObj.tm_isdst = -1;

    return tmObj;
}



//通用ReleaseState转string
std::string Mission::ReleaseStateTostring(Mission::ReleaseState releaseState)
{
    switch (releaseState)
    {
    case Mission::R_RECRUIT_M :
        return std::string("recruitingM");

    case Mission::R_RCRT_M_FAILED :
        return std::string("recruitMFailed");

    case Mission::R_CANCELED :
        return std::string ("canceled");

    case Mission::R_CHOOSE_M :
        return std::string("chooceManager");

    case Mission::R_TRANSLATING :
        return std::string("translating_r");

    case Mission::R_WAIT_FOR_PAY :
        return std::string("waitForPayment");

    case Mission::R_ACCOMPLISHED :
        return std::string("accomplished");
    }

    return std::string();
}

//通用applyMState转string
std::string Mission::ApplyMStateToString(const ApplyMState& state)
{
    switch (state)
    {
    case A_APPLYING_M :
        return std::string("Applying M");

    case A_APPLY_M_FAILED :
        return std::string("Apply Manager Failed.");

    case A_APPLY_M_SUCCEED :
        return std::string("Apply Manager Succeed");

    case A_NOT_APPLYING_M :
        return std::string("Not Applying");
    }

    return std::string();
}

//通用int转ReleaseState
Mission::ReleaseState Mission::IntToReleaseState(int iState)
{
    switch (iState)
    {
    case 0 :
        return Mission::R_RECRUIT_M;

    case 1 :
        return Mission::R_RCRT_M_FAILED;

    case 2 :
        return Mission::R_CANCELED;

    case 3 :
        return Mission:: R_CHOOSE_M;

    case 4 :
        return Mission:: R_TRANSLATING;

    case 5 :
        return Mission:: R_WAIT_FOR_PAY;

    case 6 :
        return Mission:: R_ACCOMPLISHED;

    default :
        return Mission::R_ACCOMPLISHED;
    }
}

//通用int转Language
Mission::Language Mission::IntToLanguage(int iLang)
{
    switch (iLang)
    {
    case 0 :
        return Mission::CHINESE;

    case 1 :
        return Mission::ENGLISH;

    case 2 :
        return Mission::FRENCH;

    case 3 :
        return Mission::SPANISH;

    default:
        return Mission::CHINESE;
    }
}


std::string Mission::LanguageToStr(Language lan)
{
    switch (lan)
    {
    case Mission::CHINESE :
        return "Chinese";

    case Mission::ENGLISH :
        return "English";

    case Mission::FRENCH :
        return "French";

    case Mission::SPANISH :
        return "Spanish";
    }
}


