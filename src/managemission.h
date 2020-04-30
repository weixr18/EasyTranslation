/*************************************************************************
【文件名】                 managemission.h
【功能模块和目的】          ManageMission类声明
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/

#ifndef MANAGEMISSION_H
#define MANAGEMISSION_H
#include "mission.h"
#include <utility>

//SubMission唯一标识符
typedef std::pair<std::string, std::string> KEY_SUB;
//上述唯一标识符的NULL值
#define KEY_SUB_NULL std::pair<std::string, std::string>("","")


/*************************************************************************
【类名】              ManageMission
【功能】              后端-功能模块-负责阶段任务
【接口说明】
                    见下方注释
【开发者及日期】      魏欣然 2019/08/01
【更改记录】          无
*************************************************************************/

class ManageMission:
    public Mission
{
    friend class DBOP;
    friend class StateUpdateC;
    friend class Platform;

public:
    //申请翻译者状态
    enum ApplyTState
    {
        A_APPLYING_T,
        A_APPLY_T_FAILED,
        A_APPLY_T_SUCCEED,
        A_NOT_APPLYING_T
    };
    //任务负责状态
    enum ManageState
    {
        M_RECRUIT_T,
        M_RCRT_T_FAILED,
        M_CHS_T_AND_ASSIGN,
        M_CHECKING,
        M_TIME_OUT,
        M_SUBMITTED,
        M_ACCOMPLISHED
    };

    /*******************构造与析构*******************/
public:
    using Mission::Mission;
    //无参数构造函数
    ManageMission();
    //全要素构造函数
    ManageMission(const ManageMission& mng);
    ManageMission(const Mission& m,
                  const ManageState managestate = M_RECRUIT_T);
    //析构函数
    virtual ~ManageMission();
    //赋值运算符
    ManageMission& operator=(const ManageMission& mng);

    /*******************get方法*******************/
public:
    //获取发布状态str
    std::string GetManageStateStr() const;
    //获取发布状态
    ManageState GetManageState() const;
    //获取最终译文
    std::string GetLastTranslation() const;

    //获取任务大厅展示模式
    std::string GetShowingMode() const;
    //获取申请负责人状态
    ApplyMState GetAplMState(const std::string& username);
    //获取申请翻译者状态
    ApplyTState GetAplTState(const std::string& username);
    //获取招募翻译者时间
    tm GetRecruitTTime() const;

    std::vector<std::string>& GetTrslCandidates();
    std::vector<std::string>& GetTranslators();
    std::vector<KEY_SUB>& GetSubMissions();

    /*******************通用方法*******************/
public:
    //负责状态转string
    static std::string ManageStateTostring(const ManageState& manageState);
    //int转负责状态
    static ManageState IntToManageState(const int iState);
    //翻译者申请状态转string
    static std::string ApplyTStateToString(const ApplyTState& state);

    /*******************set方法【隐私方法】*******************/
protected:
    //设置负责状态
    void SetManageState(const ManageState& manageState);
    //设置最终译文
    void SetLastTranslation(const std::string& lastTranslation);
    //设置招募译者时间
    void SetRecruitTTime(const tm& recruitTTime);


    /*******************数据成员*******************/
protected:
    ManageState m_ManageState{ M_RECRUIT_T };                          //负责状态

private:
    std::string m_LastTranslation;
    tm m_RecruitTTime;

    std::vector<std::string> m_TrsltrCandidates;                       //翻译者申请人
    std::vector<std::string> m_Translators;                            //翻译者名单
    std::vector<KEY_SUB> m_SubMissions;                                //子任务列表

};

#endif // MANAGEMISSION_H
