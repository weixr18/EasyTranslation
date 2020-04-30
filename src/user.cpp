/*************************************************************************
【文件名】                 user.cpp
【功能模块和目的】          User类实现
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/


#include "user.h"
#include <iostream>

User::User():
    m_rBalance(0)
{
}

User::User(std::string m_Name, std::string m_Password, int m_iScore,
           std::string m_RealName, std::string m_IDNum, std::string m_Email):
    m_Name(m_Name),
    m_Password(m_Password),
    m_rBalance(0),
    m_iScore(m_iScore),
    m_Info( {m_IDNum, m_RealName, m_Email})
{
}

User::~User()
{
}

User::User(const User& u):
    m_ReleasedMissions(u.m_ReleasedMissions),
    m_InChargeMissions(u.m_InChargeMissions),
    m_ParticipatingMissions(u.m_ParticipatingMissions),
    m_Name(u.m_Name),
    m_Password(u.m_Password),
    m_rBalance(u.m_rBalance),
    m_iScore(u.m_iScore),
    m_Info(u.m_Info)
{
}


User& User::operator=(const User& u)
{
    if (m_Name == "")
    {
        m_ReleasedMissions = u.m_ReleasedMissions;
        m_InChargeMissions = u.m_InChargeMissions;
        m_ParticipatingMissions = u.m_ParticipatingMissions;
        m_Name = u.m_Name;
        m_Password = u.m_Password;
        m_rBalance = u.m_rBalance;
        m_iScore = u.m_iScore;
        m_Info = u.m_Info;
    }
    return *this;
}


/*****set接口******/


void User::ScorePlus()
{
    this->m_iScore += 1;
}



void User::GetPay(double rAmount)
{
    m_rBalance += rAmount;
}

void User::Charge(double rAmount)
{
    m_rBalance += rAmount;
}

bool User::Pay(double rAmount)
{
    if (m_rBalance >= rAmount)
    {
        m_rBalance -= rAmount;
        return true;
    }
    else { return false; }
}



std::vector<std::string>& User::GetRlsMissions()
{
    return m_ReleasedMissions;
}

std::vector<std::string>& User::GetInchgMissions()
{
    return m_InChargeMissions;
}

std::vector<std::string>& User::GetPtcpMissions()
{
    return m_ParticipatingMissions;
}


bool User::PasswordMatch(const std::string& pIn)
{
    return (m_Password == pIn);
}


int User::FirstScore(const int level, const double archievement)
{
    switch (level)
    {
    case 0 :             //四级
        return 5;
    case 1 :             //六级
        return 7;
    case 2 :             //专业八级
        return 9;
    case 3 :             //TOFEL
    {
        int arc = static_cast<int>(archievement);

        if (0 <= arc && arc <= 69)
        {
            return 3;
        }
        else if (70 <= arc && arc <= 89)
        {
            return 7;
        }
        else if (90 <= arc && arc <= 99)
        {
            return 8;
        }
        else if (100 <= arc && arc <= 109)
        {
            return 9;
        }
        else if (110 <= arc && arc <= 120)
        {
            return 10;
        }
        else
        {
            return 3;
        }
    }

    case 4 :                 //YELTS
    {
        if (0 <= archievement && archievement <= 4)
        {
            return 3;
        }
        else if (4.5 <= archievement && archievement <= 5.5)
        {
            return 5;
        }
        else if (6 <= archievement && archievement <= 7.5)
        {
            return 7;
        }
        else if (8 <= archievement && archievement <= 9)
        {
            return 9;
        }
        else
        {
            return 3;
        }
    }

    case 5 :                 //GRE
    {
        int arc = static_cast<int>(archievement);

        if (130 <= arc && arc <= 149)
        {
            return 5;
        }
        else if (150 <= arc && arc <= 154)
        {
            return 7;
        }
        else if (155 <= arc && arc <= 159)
        {
            return 9;
        }
        else if (160 <= arc && arc <= 170)
        {
            return 11;
        }
        else
        {
            return 3;
        }
    }

    default :
        return 0;
    }
}



