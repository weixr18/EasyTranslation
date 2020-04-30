/*************************************************************************
【文件名】                 mission.h
【功能模块和目的】          Mission类声明
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/


#ifndef MISSION_H
#define MISSION_H
#include <string>
#include <time.h>
#include <vector>


/*************************************************************************
【类名】              Mission
【功能】              后端-功能模块-任务
【接口说明】
                    见下方注释
【开发者及日期】      魏欣然 2019/08/01
【更改记录】          无
*************************************************************************/
class Mission
{
    friend class Platform;
    friend class DBOP;
    friend class StateUpdateC;

public:
    //语言
    enum Language {CHINESE, ENGLISH, FRENCH, SPANISH};
    //发布状态
    enum ReleaseState
    {
        R_RECRUIT_M,
        R_RCRT_M_FAILED,
        R_CANCELED,
        R_CHOOSE_M,
        R_TRANSLATING,
        R_WAIT_FOR_PAY,
        R_ACCOMPLISHED
    };
    //申请负责人状态
    enum ApplyMState
    {
        A_APPLYING_M,
        A_APPLY_M_FAILED,
        A_APPLY_M_SUCCEED,
        A_NOT_APPLYING_M
    };

    /************************构造与析构************************/
public:
    //无参数构造函数
    Mission();
    //全要素构造函数
    Mission(
        const std::string missionName,
        std::string releaser,
        const std::string introduction,
        const std::string srcText,
        const tm recruitMTime,
        const tm DDL,
        const int awardAmount,
        const ReleaseState releaseState,
        const Language srcLanguage,
        const Language tarLanguage,
        const std::string& manager = "");
    //拷贝构造函数
    Mission(const Mission& m);
    //析构函数
    virtual ~Mission();
    //赋值运算符
    Mission& operator=(const Mission& m);


    /************************get方法************************/
public:
    //获取任务名
    const std::string GetMissionName() const;
    //获取发布者
    const std::string GetReleaser() const;
    //获取负责人
    const std::string GetManager() const;
    //获取发布状态
    Mission::ReleaseState GetReleaseState() const;
    //获取源文本
    const std::string GetSrcText() const;
    //获取任务简介
    const std::string GetIntroduction() const;
    //获取源语言
    Mission::Language GetSrcLanguage() const;
    //获取目标语言
    Mission::Language GetTarLanguage() const;
    //获取招募负责人截止时间
    const tm GetRecruitMTime() const;
    //获取任务截止时间
    const tm GetMissionDDL() const;
    //获取总酬金数目
    int GetAwardAmount() const;

    //获取负责人报名者
    std::vector<std::string>& GetMngCandidates();

    /************************任务大厅相关************************/
public:
    //获取发布状态str
    std::string GetReleaseStateStr() const;
    //获取负责状态str
    virtual std::string GetManageStateStr() const;
    //获取任务大厅展示状态
    virtual std::string GetShowingMode() const;
    //用户查询申请负责人状态
    virtual ApplyMState GetAplMState(const std::string& user);

    /************************通用方法************************/
    //string转tm
    static tm StringToTime(const std::string& sTime);
    //int转tm
    static tm IntToTime(int year, int month, int date, int hour, int minute,
                        int second = 0);
    //tm转string
    static std::string TimeToString(const tm& time);

    //发布状态转string
    static std::string ReleaseStateTostring(ReleaseState releaseState);
    //int转发布状态
    static ReleaseState IntToReleaseState(int iState);
    //申请状态转string
    static std::string ApplyMStateToString(const ApplyMState& state);

    //语言转string
    static std::string LanguageToStr(Language lan);
    //int转语言
    static Language IntToLanguage(int iLang);

    /************************set方法【隐私方法】************************/
protected:
    //设置负责人
    void SetManager(const std::string& user);
    //设置发布状态
    void SetReleaseState(const Mission::ReleaseState& releaseState);
    //设置招募负责人截止时间
    void SetRecruitMTime(const tm& recruitMTime);

    /************************数据成员************************/
private:
    std::string m_Name;                                //任务名【唯一标识】
    std::string m_Releaser;                            //发布者
    Language m_Srclanguage{ENGLISH};                   //源语言
    Language m_TarLanguage{CHINESE};                   //目标语言
    std::string m_SrcText;                             //文本
    std::string m_Introduction;                        //介绍
    tm m_DDL;                                          //项目完成截止时间
    tm m_RecruitMTime;                                 //负责人招募截止时间
    int m_iAwardAmount;                                //报酬总额

    std::vector<std::string> m_MngCandidates;          //负责人报名者

protected:
    ReleaseState m_ReleaseState;                       //发布状态
    std::string m_Manager;                             //负责人

};


#endif // MISSION_H
