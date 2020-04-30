/*************************************************************************
【文件名】                 user.h
【功能模块和目的】          User类声明及内联函数实现
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/

#ifndef USER_H
#define USER_H

#include <vector>
#include <string>
using namespace std;

typedef unsigned long long ULL;


/*************************************************************************
【类名】              User
【功能】              后端-功能模块-用户
【接口说明】
                    见下方注释
【开发者及日期】      魏欣然 2019/08/01
【更改记录】          无
*************************************************************************/

class User
{
    friend class DBOP;

public:
    //用户信息，打包成一个结构体
    struct Userinfo
    {
    public:
        std::string m_ID;
        std::string m_RealName;
        std::string m_Email;
    };

    /*****************构造与析构*****************/
public:
    //无参构造函数
    User();
    //拷贝构造函数
    User(const User& u);
    //全要素构造函数
    User(std::string m_Name, std::string m_Password, int m_iScore,
         std::string m_RealName = "", std::string m_IDNum = "000",
         std::string m_Email = "");
    //析构函数
    virtual ~User();
    //赋值运算符
    User& operator= (const User& u);

    /*****************set接口*****************/
public:
    //积分+1
    void ScorePlus();
    //充值
    void Charge(double rAmount);
    //获得报酬
    void GetPay(double rAmount);
    //付款
    bool Pay(double rAmount);

    /*****************get接口*****************/
public:
    //获取用户信息
    Userinfo GetUserInfo() const;
    //获取用户名
    std::string GetUserName() const;
    //获取用户身份证号
    std::string GetIdNum() const;
    //获取用户真实姓名
    std::string GetRealName() const;
    //获取用户邮箱
    std::string GetEMail() const;
    //获取用户积分
    int GetScore() const;
    //获取用户账户余额
    double GetBalance() const;

    //获取用户发布的任务
    std::vector<std::string>& GetRlsMissions();
    //获取用户申请负责的任务
    std::vector<std::string>& GetInchgMissions();
    //获取用户申请参与翻译的任务
    std::vector<std::string>& GetPtcpMissions();

    /*****************判定方法*****************/
    //密码匹配
    bool PasswordMatch(const std::string& pIn);
    //计算初始积分
    static int FirstScore(const int level, const double achievement);

    /*****************隐私方法*****************/
private:
    //获取密码【仅DBOP类使用】
    std::string GetPassword() const;

    /*****************数据成员*****************/
private:
    std::vector<std::string> m_ReleasedMissions;                  //发布的任务
    std::vector<std::string> m_InChargeMissions;                  //负责的任务
    std::vector<std::string> m_ParticipatingMissions;             //参与的任务

    std::string m_Name;
    std::string m_Password;
    double m_rBalance{0.0};                                       //余额
    int m_iScore{0};                                              //积分
    Userinfo m_Info;

};


/*****************内联get接口实现*****************/

/*************************************************************************
【函数名称】       GetScore
【函数功能】       获取积分
【参数】           void
【返回值】         int 用户积分
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
inline int User::GetScore() const
{
    return m_iScore;
}


/*************************************************************************
【函数名称】       GetBalance
【函数功能】       获取余额
【参数】           void
【返回值】         double 用户积分
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
inline double User::GetBalance() const
{
    return m_rBalance;
}


/*************************************************************************
【函数名称】       GetUserName
【函数功能】       获取用户名
【参数】           void
【返回值】         std::string 用户名
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
inline std::string User::GetUserName() const
{
    return m_Name;
}


/*************************************************************************
【函数名称】       GetUserInfo
【函数功能】       获取用户信息
【参数】           void
【返回值】         User::UserInfo 用户信息
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
inline User::Userinfo User::GetUserInfo() const
{
    return m_Info;
}


/*************************************************************************
【函数名称】       GetIdNum
【函数功能】       获取身份证号
【参数】           void
【返回值】         std::string 身份证号
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
inline std::string User::GetIdNum() const
{
    return m_Info.m_ID;
}


/*************************************************************************
【函数名称】       GetRealName
【函数功能】       获取真实姓名
【参数】           void
【返回值】         std::string 真实姓名
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
inline std::string User::GetRealName() const
{
    return m_Info.m_RealName;
}


/*************************************************************************
【函数名称】       GetEmail
【函数功能】       获取邮箱
【参数】           void
【返回值】         std::string 邮箱
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
inline std::string User::GetEMail() const
{
    return m_Info.m_Email;
}


/*************************************************************************
【函数名称】       GetPassword
【函数功能】       获取密码
【参数】           void
【返回值】         std::string 密码
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
【备注】          向数据库写入数据的时候必须要知道密码明文 没办法
*************************************************************************/
inline std::string User::GetPassword() const
{
    return m_Password;
}


#endif // USER_H
