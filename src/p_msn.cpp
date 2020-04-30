/*************************************************************************
【文件名】                 p_msn.cpp
【功能模块和目的】          P_MSN类实现
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/


#include "p_msn.h"
#include "Datum.h"

P_MSN::P_MSN(const std::string& missionName) :
    m_Key(missionName)
{
}

P_MSN::P_MSN(Mission* m)
{
    if (m == nullptr)
    { m_Key = ""; }
    else
    { m_Key = m->GetMissionName(); }
}

P_MSN::~P_MSN()
{
}


bool P_MSN::exist() const
{
    return Datum::MissionNameExist(m_Key);
}


Mission* P_MSN::operator ->() const
{
    Mission* temp = nullptr;

    if (Datum::GetMissionByName(m_Key, temp))
    {
        return temp;
    }
    else
    {
        return nullptr;
    }
}


Mission P_MSN::operator*() const
{
    Mission* temp = nullptr;

    if (Datum::GetMissionByName(m_Key, temp))
    {
        return *temp;
    }
    else
    {
        return Mission();
    }
}

bool P_MSN::operator != (const P_MSN& p) const
{
    return (m_Key != p.m_Key);
}

bool P_MSN::operator == (const P_MSN& p) const
{
    return (m_Key == p.m_Key);
}

P_MSN& P_MSN::operator = (const P_MSN& p)
{
    m_Key = p.m_Key;
    return *this;
}


P_MSN& P_MSN::operator = (const Mission * (&mission))
{
    if (mission == nullptr)
    { m_Key = ""; }
    else
    { m_Key = mission->GetMissionName(); }

    return *this;
}


