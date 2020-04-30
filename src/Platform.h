/*************************************************************************
【文件名】                 Platform.h
【功能模块和目的】          Platform类声明
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/


#ifndef PLATFORM_H
#define PLATFORM_H

#include <Datum.h>
#include <p_user.h>
#include <p_mng.h>
#include <p_msn.h>
#include <p_sub.h>

#define ASSIGN_MIS std::vector<std::pair<std::string, std::string>>
#define TRANSLATION_P std::pair<std::string, std::string>



class Platform
{

public:
    static bool u_regist(P_USER& p_user, const std::string& username,
                         const std::string& password, const int& score,
                         const std::string& realName, const std::string& IDNum,
                         const std::string& email);

    static bool u_login_succeed(const std::string& username,
                                const std::string& password);

    static bool u_release_mission(P_USER& p_releaser, P_MSN& p_mission,
                                  const std::string missionName, const std::string introduction,
                                  const std::string srcText, const tm recruitMTime,
                                  const tm missionDDL, const int awardAmount,
                                  const Mission::Language srcLanguage,
                                  const Mission::Language tarLanguage);

    static bool u_apl_manager(const P_USER& applyer, const P_MSN& mission);

    static bool r_choose_manager(const P_USER& releaser, const P_MSN& mission,
                                 const P_USER& manager, P_MNG& mng);

    static bool m_set_recruit_T_time(const P_USER& manager, const P_MNG& mng,
                                     const tm& recruitTTime);

    static bool u_apl_transltr(const P_USER& p_user, const P_MNG& p_mng);


    static bool m_choose_tranlator(const P_USER& manager, const P_MNG& mng,
                                   const std::vector<P_USER>& translators);


    static bool m_assign_mission(const P_USER& manager, const P_MNG& mng,
                                 const ASSIGN_MIS& assign);

    static bool t_submit_translation(const P_USER& translator, const P_SUB& p_sub,
                                     const std::string& translation);

    static bool m_submit_feedback(const P_USER& manager, const P_SUB& p_sub,
                                  const std::string& feedback);

    static bool m_accept_translation(const P_USER& manager, const P_SUB& p_sub);

    static bool m_last_submittal(const P_USER& manager, const P_MNG& mng,
                                 const std::string& allTrans);

    static bool r_pay_award(const P_USER& releaser, const P_MNG& mng);


    static bool msn_rct_M_judge(const P_MSN& mission);


    static bool msn_rct_T_judge(const P_MNG& mng);

    static bool msn_time_out(const P_MNG& mng);

    static bool msn_show_in_user_hall(const P_MSN& p_mission, const P_USER& p_user);

    static bool mng_show_in_user_hall(const P_MNG& p_mng, const P_USER& p_user);

    static bool userAbleToManage(P_USER& user);

    static bool r_cancel_mission(const P_USER& releaser, const P_MSN& mission);

    static bool r_rcrt_M_time_extend(const P_USER &releaser, const P_MSN mission, const tm& time);

    static bool m_rcrt_T_time_extend(const P_USER &manager, const P_MNG &p_mng, const tm& time);


private:
    //无参构造函数
    Platform();
    //拷贝构造函数
    Platform(const Platform& p);
    //析构函数
    virtual ~Platform();
    //赋值运算符
    Platform& operator=(Platform& p);
};


#endif // PLATFORM_H
