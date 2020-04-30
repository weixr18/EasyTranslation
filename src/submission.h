/*************************************************************************
【文件名】                 submission.h
【功能模块和目的】          SubMission类声明
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/


#ifndef SUBMISSION_H
#define SUBMISSION_H
#include <utility>
#include <string>
#include "managemission.h"


/*************************************************************************
【类名】              SubMission
【功能】              后端-功能模块-子任务
【接口说明】
                    见下方注释
【开发者及日期】      魏欣然 2019/08/01
【更改记录】          无
*************************************************************************/
class SubMission : public ManageMission
{
    friend class Datum;
    friend class DBOP;
    friend class Platform;

public:
    //子任务状态
    enum SubMissionState
    {
        T_WAIT_FOR_TRANS,
        T_SUBMITTED,
        T_WAIT_FOR_MODIFY,
        T_ACCEPTED,
        T_ACCOMPLISHED
    };

public:
    //无参构造函数
    SubMission();
    //使用基类对象初始化的构造函数
    SubMission(const ManageMission& m, const std::string& translator);
    //拷贝构造函数
    SubMission(const SubMission& s);
    //全要素构造函数
    SubMission(const std::string& name, const std::string& translator,
               const std::string& releaser, const Language srclanguage,
               const Language tarLanguage,
               const std::string& introduction, const tm& missionDDL,
               const std::string manager, const ManageState manageState,
               const SubMissionState submissionState, const std::string srcSubtext,
               const std::vector<KEY_SUB>& history, const std::string& translation);
    //析构函数
    virtual ~SubMission();
    //赋值运算符
    SubMission& operator=(const SubMission& s);

    /***************************get方法***************************/
public:
    //获取子任务状态
    SubMissionState GetSubMissionState() const;
    //获取翻译者
    std::string GetTranslator() const;
    //获取自己的源文本
    std::string GetSrcSubText() const;
    //获取最终译文
    std::string GetTranslation() const;
    //获取唯一标识符
    KEY_SUB GetKey() const;
    //获取子任务状态str
    std::string GetSubMissionStateStr() const;
    //获取历史记录
    std::vector<std::pair<std::string, std::string>>& GetHistory() ;

    /***************************通用方法***************************/
public:
    //子任务状态转string
    static std::string SubMsnStateTostr(const SubMissionState& state);
    static SubMissionState IntToSubMissionState(const int iState);

    /***************************set方法【隐私方法】***************************/
protected:
    //设置子任务状态
    void SetSubMissionState(const SubMissionState& subMissionState);
    //设置源文本
    void SetSrcSubText(const std::string& srcSubText);
    //设置最终译文
    void SetTranslation(const std::string& translation);

    /**************************数据成员****************************/
private:
    KEY_SUB m_Key;                                              //唯一标识符
    std::string m_Translator;                                   //翻译者
    std::string m_SrcSubText;                                   //分配的文本
    std::string m_Translation;                                  //译文
    std::vector<std::pair<std::string, std::string>> m_History; //历史记录

protected:
    SubMissionState m_SubMissionState{ T_WAIT_FOR_TRANS };      //子任务状态

};

#endif // SUBMISSION_H
