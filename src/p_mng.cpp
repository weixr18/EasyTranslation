/*************************************************************************
【文件名】                 p_mng.cpp
【功能模块和目的】          P_MNG类实现
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/


#include "p_mng.h"
#include "Datum.h"

P_MNG::P_MNG(const std::string& missionName) :
    m_Key(missionName)
{
}

P_MNG::P_MNG(const ManageMission*& m)
{
    if (m == nullptr)
    { m_Key = ""; }
    else
    { m_Key = m->GetMissionName(); }
}

P_MNG::~P_MNG()
{
}


bool P_MNG::exist() const
{
    return Datum::MngMsnNameExist(m_Key);
}

ManageMission* P_MNG::operator ->() const
{
    ManageMission* temp = nullptr;

    if (Datum::GetMngMsnByName(m_Key, temp))
    {
        return temp;
    }
    else
    {
        return nullptr;
    }
}

ManageMission P_MNG::operator*() const
{
    ManageMission* temp = nullptr;

    if (Datum::GetMngMsnByName(m_Key, temp))
    {
        return *temp;
    }
    else
    {
        return ManageMission();
    }
}

bool P_MNG::operator != (const P_MNG& p) const
{
    return (m_Key != p.m_Key);
}

bool P_MNG::operator == (const P_MNG& p) const
{
    return (m_Key == p.m_Key);
}

P_MNG& P_MNG::operator = (const P_MNG& p)
{
    m_Key = p.m_Key;
    return *this;
}

P_MNG& P_MNG::operator = (const ManageMission * (&mng))
{
    if (mng == nullptr)
    { m_Key = ""; }
    else
    { m_Key = mng->GetMissionName(); }

    return *this;
}

