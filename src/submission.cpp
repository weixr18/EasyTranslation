/*************************************************************************
【文件名】                 submission.cpp
【功能模块和目的】          SubMission类实现
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/

#include "submission.h"


SubMission::SubMission():
    m_SubMissionState(SubMission::T_WAIT_FOR_TRANS)
{}

SubMission::SubMission(const ManageMission& m, const std::string& translator):
    ManageMission (m),
    m_Translator(translator),
    m_SubMissionState(SubMission::T_WAIT_FOR_TRANS)
{}


SubMission::SubMission(const SubMission& s):
    ManageMission (s),
    m_Key(s.m_Key),
    m_Translator(s.m_Translator),
    m_SrcSubText(s.m_SrcSubText),
    m_Translation(s.m_Translation),
    m_SubMissionState(s.m_SubMissionState),
    m_History(s.m_History)
{}


SubMission::SubMission(const std::string& name,
    const std::string& translator,
    const std::string& releaser,
    const Language srclanguage,
    const Language tarlanguage,
    const std::string& introduction,
    const tm& missionDDL,
    const std::string manager,
    const ManageState manageState,
    const SubMissionState submissionState,
    const std::string srcSubtext,
    const std::vector<KEY_SUB>& history,
    const std::string& translation):
    ManageMission(Mission(name, releaser, introduction,
                          "", tm(), missionDDL, 0,
                          Mission::R_TRANSLATING,
                          srclanguage, tarlanguage, manager),
                  manageState),
    m_Key(KEY_SUB(name, translator)),
    m_Translator(translator),
    m_SrcSubText(srcSubtext),
    m_Translation(translation),
    m_SubMissionState(submissionState),
    m_History(history)
{}


SubMission::~SubMission()
{
}

SubMission& SubMission::operator=(const SubMission& s)
{
    if (this == &s) { return *this; }

    if (m_Key == KEY_SUB_NULL)
    {
        static_cast <ManageMission&> (*this) = s;
        m_Key = s.m_Key;
        m_Translator = s.m_Translator;
        m_SrcSubText = s.m_SrcSubText;
        m_Translation = s.m_Translation;
        m_SubMissionState = s.m_SubMissionState;
        m_History = s.m_History;
    }
    return *this;
}



/**get方法**/
std::string SubMission::GetTranslator() const
{
    return m_Translator;
}


SubMission::SubMissionState SubMission::GetSubMissionState() const
{
    return m_SubMissionState;
}

std::string SubMission::GetSrcSubText() const
{
    return m_SrcSubText;
}


std::string SubMission::GetTranslation() const
{
    return m_Translation;
}

KEY_SUB SubMission::GetKey() const
{
    return m_Key;
}


//获取子任务状态str
std::string SubMission::GetSubMissionStateStr() const
{
    return SubMsnStateTostr(m_SubMissionState);
}


//获取历史记录
std::vector<KEY_SUB>& SubMission::GetHistory()
{
    return m_History;
}

/**set方法**/

void SubMission::SetSubMissionState(const SubMissionState& subMissionState)
{
    this->m_SubMissionState = subMissionState;
}


void SubMission::SetSrcSubText(const std::string& srcSubText)
{
    this->m_SrcSubText = srcSubText;
}

void SubMission::SetTranslation(const std::string& translation)
{
    this->m_Translation = translation;
}



/*************************通用方法***************************/

//通用SubmissionState转String
std::string SubMission::SubMsnStateTostr(const SubMissionState& state)
{
    switch (state)
    {
    case SubMission::T_WAIT_FOR_TRANS :
        return std::string("toBeTranslated");

    case SubMission::T_SUBMITTED :
        return std::string("submitted_t");

    case SubMission::T_WAIT_FOR_MODIFY :
        return std::string("toBeModified");

    case SubMission::T_ACCEPTED :
        return std::string("accepted");

    case SubMission::T_ACCOMPLISHED :
        return std::string("accomplished_t");
    }

    return std::string();
}



//通用int转SubmissionState
SubMission::SubMissionState SubMission::IntToSubMissionState(const int iState)
{
    switch (iState)
    {
    case 0 :
        return SubMission::T_WAIT_FOR_TRANS;

    case 1 :
        return SubMission::T_SUBMITTED;

    case 2 :
        return SubMission::T_WAIT_FOR_MODIFY;

    case 3 :
        return SubMission::T_ACCEPTED;

    case 4 :
        return SubMission::T_ACCOMPLISHED;

    default :
        return SubMission::T_ACCOMPLISHED;
    }
}


