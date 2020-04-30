/*************************************************************************
【文件名】                 p_sub.cpp
【功能模块和目的】          P_SUB类实现
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/


#include "p_sub.h"
#include "Datum.h"


P_SUB::P_SUB(const KEY_SUB& missionName) :
    m_Key(missionName)
{
}

P_SUB::P_SUB(const SubMission*& m)
{
    if (m == nullptr)
    { m_Key = KEY_SUB_NULL; }
    else
    { m_Key = KEY_SUB(m->GetMissionName(), m->GetTranslator()); }
}

P_SUB::~P_SUB()
{
}


bool P_SUB::exist() const
{
    return Datum::SubMsnKeyExist(m_Key);
}

SubMission* P_SUB::operator ->() const
{
    SubMission* temp = nullptr;

    if (Datum::GetSubMsnByKey(m_Key, temp))
    {
        return temp;
    }
    else
    {
        return nullptr;
    }
}

SubMission P_SUB::operator*() const
{
    SubMission* temp = nullptr;

    if (Datum::GetSubMsnByKey(m_Key, temp))
    {
        return *temp;
    }
    else
    {
        return SubMission();
    }
}

bool P_SUB::operator != (const P_SUB& p) const
{
    return (m_Key != p.m_Key);
}

bool P_SUB::operator == (const P_SUB& p) const
{
    return (m_Key == p.m_Key);
}

P_SUB& P_SUB::operator = (const P_SUB& p)
{
    m_Key = p.m_Key;
    return *this;
}

P_SUB& P_SUB::operator = (const SubMission * (&sub))
{

    if (sub == nullptr)
    { m_Key = KEY_SUB_NULL; }
    else
    { m_Key = KEY_SUB(sub->GetMissionName(), sub->GetTranslator()); }

    return *this;
}


