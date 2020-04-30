/*************************************************************************
【文件名】                 login.h
【功能模块和目的】          Login类声明
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/

#ifndef LOGIN_H
#define LOGIN_H

#include "homepage.h"

class MainWindow;

namespace Ui
{
    class Login;
}

/*************************************************************************
【类名】              Login
【功能】              前端-功能界面-登录
【接口说明】
                     1. 构造函数，用于构造界面
                     2. 析构函数
【开发者及日期】      魏欣然 2019/08/01
【更改记录】          无
*************************************************************************/

class Login : public QDialog
{
    Q_OBJECT

public:
    //构造函数
    explicit Login(QWidget* parent = nullptr);
    //析构函数
    ~Login();

private:
    //进入个人主页
    void GoHomepage(P_USER user);
    //身份确认
    void IdentityConfirm();
    //返回上一页面
    void ReturnMain();
    //登录失败
    void LoginFailed();

signals:
    //信号-返回上一页面
    void s_returnMain();
    //信号-登录成功
    void s_loginSucceed(P_USER user);
    //信号-登录失败
    void s_loginFailed();

private:
    Ui::Login* ui;
    HomePage* homepage;
};


#endif // LOGIN_H
