/*************************************************************************
【文件名】                 mission.cpp
【功能模块和目的】          Mission类实现-PART I
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/

#include "mission.h"
#include <iostream>

Mission::Mission()
{}

//全要素构造函数
Mission::Mission(const std::string missionName, std::string releaser,
                 const std::string introduction, const std::string srcText,
                 const tm recruitMTime, const tm missionDDL,
                 const int awardAmount, const ReleaseState releaseState,
                 const Language srcLanguage, const Language tarLanguage,
                 const std::string& manager):
    m_Name(missionName),
    m_Releaser(releaser),
    m_Srclanguage(srcLanguage),
    m_TarLanguage(tarLanguage),
    m_SrcText(srcText),
    m_Introduction(introduction),
    m_DDL(missionDDL),
    m_RecruitMTime(recruitMTime),
    m_iAwardAmount(awardAmount),
    m_ReleaseState(releaseState),
    m_Manager(manager)
{}

//复制构造函数
Mission::Mission(const Mission& m):
    m_Name(m.m_Name),
    m_Releaser(m.m_Releaser),
    m_Srclanguage(m.m_Srclanguage),
    m_TarLanguage(m.m_TarLanguage),
    m_SrcText(m.m_SrcText),
    m_Introduction(m.m_Introduction),
    m_DDL(m.m_DDL),
    m_RecruitMTime(m.m_RecruitMTime),
    m_iAwardAmount(m.m_iAwardAmount),
    m_ReleaseState(m.m_ReleaseState),
    m_Manager(m.m_Manager),
    m_MngCandidates(m.m_MngCandidates)
{}

Mission::~Mission()
{}

Mission& Mission::operator=(const Mission& m)
{
    if (m_Name == "")
    {
        m_Name = m.m_Name;
        m_Releaser = m.m_Releaser;
        m_Srclanguage = m.m_Srclanguage;
        m_TarLanguage = m.m_TarLanguage;
        m_SrcText = m.m_SrcText;
        m_Introduction = m.m_Introduction;
        m_DDL = m.m_DDL;
        m_RecruitMTime = m.m_RecruitMTime;
        m_iAwardAmount = m.m_iAwardAmount;
        m_ReleaseState = m.m_ReleaseState;
        m_Manager = m.m_Manager;
        m_MngCandidates = m.m_MngCandidates;
    }
    return *this;
}

/*******set方法*******/


void Mission::SetManager(const std::string& manager)
{
    this->m_Manager = manager;
}


void Mission::SetReleaseState(const Mission::ReleaseState& releaseState)
{
    this->m_ReleaseState = releaseState;
}

void Mission::SetRecruitMTime(const tm &recruitMTime)
{
    this->m_RecruitMTime = recruitMTime;
}


/****get方法****/

const std::string Mission::GetMissionName() const
{
    return m_Name;
}

const std::string Mission::GetManager() const
{
    return m_Manager;
}

const std::string Mission::GetReleaser() const
{
    return m_Releaser;
}

const std::string Mission::GetSrcText() const
{
    return m_SrcText;
}

const std::string Mission::GetIntroduction() const
{
    return m_Introduction;
}

Mission::ReleaseState Mission::GetReleaseState() const
{
    return m_ReleaseState;
}

Mission::Language Mission::GetSrcLanguage() const
{
    return m_Srclanguage;
}

Mission::Language Mission::GetTarLanguage() const
{
    return m_TarLanguage;
}

const tm Mission::GetRecruitMTime() const
{
    return m_RecruitMTime;
}

const tm Mission::GetMissionDDL() const
{
    return m_DDL;
}

int Mission::GetAwardAmount() const
{
    return m_iAwardAmount;
}


//获取发布状态String
std::string Mission::GetReleaseStateStr() const
{
    return ReleaseStateTostring(m_ReleaseState);
}


std::string Mission::GetManageStateStr() const
{
    return std::string("");
}

std::vector<std::string>& Mission::GetMngCandidates()
{
    return m_MngCandidates;
}
