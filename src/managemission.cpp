/*************************************************************************
【文件名】                 managemission.cpp
【功能模块和目的】          ManageMission类实现
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/


#include "managemission.h"
#include <iostream>

ManageMission::ManageMission()
{}

ManageMission::~ManageMission()
{}

ManageMission::ManageMission(const Mission& m,
                             const ManageState managestate):
    Mission(m),
    m_ManageState(managestate)
{}

ManageMission::ManageMission(const ManageMission& mng):
    Mission (mng),
    m_ManageState(mng.m_ManageState),
    m_LastTranslation(mng.m_LastTranslation),
    m_RecruitTTime(mng.m_RecruitTTime),
    m_TrsltrCandidates(mng.m_TrsltrCandidates),
    m_Translators(mng.m_Translators),
    m_SubMissions(mng.m_SubMissions)
{}


ManageMission& ManageMission::operator=(const ManageMission& mng)
{
    if (this == &mng) { return *this; }

    static_cast <Mission&> (*this) = mng;
    m_TrsltrCandidates = mng.m_TrsltrCandidates;
    m_Translators = mng.m_Translators;
    m_SubMissions = mng.m_SubMissions;
    m_ManageState = mng.m_ManageState;
    m_LastTranslation = mng.m_LastTranslation;
    m_RecruitTTime = mng.m_RecruitTTime;
    return *this;
}

/*********************set方法*********************/


void ManageMission::SetManageState(const ManageState& manageState)
{
    this->m_ManageState = manageState;
}

void ManageMission::SetLastTranslation(const std::string& lastTranslation)
{
    this->m_LastTranslation = lastTranslation;
}


void ManageMission::SetRecruitTTime(const tm& recruitTTime)
{
    this->m_RecruitTTime = recruitTTime;
}

/*********************get方法*********************/


ManageMission::ManageState ManageMission::GetManageState() const
{
    return m_ManageState;
}

std::string ManageMission::GetLastTranslation() const
{
    return m_LastTranslation;
}

tm ManageMission::GetRecruitTTime() const
{
    return m_RecruitTTime;
}

//获取负责状态str
std::string ManageMission::GetManageStateStr() const
{
    return ManageStateTostring(m_ManageState);
}

//通用applyTState转string
std::string ManageMission::ApplyTStateToString(const ApplyTState& state)
{
    switch (state)
    {
    case A_APPLYING_T:
        return std::string("Applying T");

    case A_APPLY_T_FAILED:
        return std::string("Apply Translator Failed.");

    case A_APPLY_T_SUCCEED:
        return std::string("Apply Translator Succeed");

    case A_NOT_APPLYING_T:
        return std::string("Not Applying");
    }

    return std::string();
}


//通用ManageState转string
std::string ManageMission::ManageStateTostring(const ManageMission::ManageState&
        manageState)
{
    switch (manageState)
    {
    case ManageMission::M_RECRUIT_T:
        return std::string("recruitingT");

    case ManageMission::M_RCRT_T_FAILED:
        return std::string("recruitTFailed");

    case ManageMission::M_CHS_T_AND_ASSIGN:
        return std::string("chooceAndAssign");

    case ManageMission::M_CHECKING:
        return std::string("checking");

    case ManageMission::M_TIME_OUT:
        return std::string("timeOut");

    case ManageMission::M_SUBMITTED:
        return std::string("submitted_m");

    case ManageMission::M_ACCOMPLISHED:
        return std::string("accomplished_m");
    }

    return std::string();
}


//通用int转ManageState
ManageMission::ManageState ManageMission::IntToManageState(const int iState)
{
    switch (iState)
    {
    case 0:
        return ManageMission::M_RECRUIT_T;

    case 1:
        return ManageMission::M_RCRT_T_FAILED;

    case 2:
        return ManageMission::M_CHS_T_AND_ASSIGN;

    case 3:
        return ManageMission::M_CHECKING;

    case 4:
        return ManageMission::M_TIME_OUT;

    case 5:
        return ManageMission::M_SUBMITTED;

    case 6:
        return ManageMission::M_ACCOMPLISHED;

    default:
        return ManageMission::M_TIME_OUT;
    }
}

std::vector<std::string>& ManageMission::GetTrslCandidates()
{
    return m_TrsltrCandidates;
}
std::vector<std::string>& ManageMission::GetTranslators()
{
    return m_Translators;
}
std::vector<KEY_SUB>& ManageMission::GetSubMissions()
{
    return m_SubMissions;
}


/**********************任务大厅相关函数**********************/

//任务大厅展示状态
std::string ManageMission::GetShowingMode() const
{
    switch (m_ReleaseState)
    {
    case Mission::R_WAIT_FOR_PAY :
    case Mission::R_ACCOMPLISHED :
    {
        return std::string("Accomplished");                         //已完成
    }

    case Mission::R_TRANSLATING :
    {
        switch (this->m_ManageState)
        {
        case ManageMission::M_RECRUIT_T :
        {
            return std::string("Recruiting Translator");        //正在招募译者
        }

        case ManageMission::M_CHECKING :
        case ManageMission::M_CHS_T_AND_ASSIGN :
        {
            return std::string("Translating");                  //正在翻译
        }

        case ManageMission::M_SUBMITTED :
        case ManageMission::M_ACCOMPLISHED :
        {
            return std::string("Accomplished");                 //已完成
        }

        case ManageMission::M_RCRT_T_FAILED :
        case ManageMission::M_TIME_OUT :
        {
            return std::string();
        }
        }

        break;
    }

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
    }

    return std::string();
}


//用户查询申请负责人状态
Mission::ApplyMState ManageMission::GetAplMState(const std::string& username)
{
    /*
    std::vector<std::string> mngCandidates = GetMngCandidates();
    if (std::find(mngCandidates.begin(), mngCandidates.end(), username) ==
        mngCandidates.end())
    {
        return Mission::A_NOT_APPLYING_M;
    }
    */

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
        if (GetManager() != username)
        {
            return Mission::A_APPLY_M_FAILED;
        }
        else
        {
            return Mission::A_APPLY_M_SUCCEED;
        }
    }

    return Mission::A_NOT_APPLYING_M;
}

//用户查询申请翻译者状态
ManageMission::ApplyTState ManageMission::GetAplTState(const std::string&
        username)
{
    /*if (std::find(m_TrsltrCandidates.begin(), m_TrsltrCandidates.end(), username)
        == m_TrsltrCandidates.end())
    {
        return ManageMission::A_NOT_APPLYING_T;
    }*/


    switch (GetManageState())
    {
    case ManageMission::M_RECRUIT_T :
    case ManageMission::M_CHS_T_AND_ASSIGN :
        return ManageMission::A_APPLYING_T;

    case ManageMission::M_RCRT_T_FAILED :
    case ManageMission::M_TIME_OUT :
        return ManageMission::A_APPLY_T_FAILED;

    case ManageMission::M_CHECKING :
    case ManageMission::M_SUBMITTED :
    case ManageMission::M_ACCOMPLISHED :
        /*
        if (std::find(m_Translators.begin(), m_Translators.end(),
                      username) == m_Translators.end())
        {
            return ManageMission::A_APPLY_T_FAILED;
        }
        else
        {
            return ManageMission::A_APPLY_T_SUCCEED;
        }*/
        break;
    }

    return ManageMission::A_NOT_APPLYING_T;
}

