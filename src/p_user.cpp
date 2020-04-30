/*************************************************************************
【文件名】                 p_user.cpp
【功能模块和目的】          P_USER类实现
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/


#include "p_user.h"
#include "Datum.h"

P_USER::P_USER(std::string username):
    m_Key(username)
{
}

P_USER::P_USER(User* u)
{
    if (u == nullptr)
    { m_Key = ""; }
    else
    { m_Key = u->GetUserName(); }
}

P_USER::~P_USER()
{
}


bool P_USER::exist() const
{
    return Datum::UserNameExist(m_Key);
}

User* P_USER::operator ->() const
{
    User* temp = nullptr;

    if (Datum::GetUserByName(m_Key, temp))
    {
        return temp;
    }
    else
    {
        return nullptr;
    }
}

User P_USER::operator*() const
{
    User* temp = nullptr;

    if (Datum::GetUserByName(m_Key, temp))
    {
        return *temp;
    }
    else
    {
        return User();
    }
}

bool P_USER::operator != (const P_USER& p) const
{
    return (m_Key != p.m_Key);
}

bool P_USER::operator == (const P_USER& p) const
{
    return (m_Key == p.m_Key);
}

P_USER& P_USER::operator = (const P_USER& p)
{
    m_Key = p.m_Key;
    return *this;
}


P_USER& P_USER::operator = (const User * (&user))
{
    if (user == nullptr)
    { m_Key = ""; }
    else
    { m_Key = user->GetUserName(); }

    return *this;
}


