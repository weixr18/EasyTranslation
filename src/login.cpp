/*************************************************************************
【文件名】                 login.cpp
【功能模块和目的】          Login类实现
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/


#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"
#include <QDebug>


/*************************************************************************
【函数名称】       Login
【函数功能】       Login类构造函数 构造该页面
【参数】
                  QWidget* parent          输入
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
Login::Login(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::Login),
    homepage(nullptr)
{
    ui->setupUi(this);
    connect(ui->ok, &QPushButton::clicked, this,
            &Login::IdentityConfirm);                           //进入身份验证
    connect(ui->cancel, &QPushButton::clicked, this,
            &Login::ReturnMain);                                //登录取消
    connect(this, &Login::s_loginSucceed, this,
            &Login::GoHomepage);                                //登录成功
    connect(this, &Login::s_loginFailed, this,
            &Login::LoginFailed);                               //登录失败
}


/*************************************************************************
【函数名称】       ~Login
【函数功能】       Login类析构函数
【参数】           void
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
Login::~Login()
{
    delete ui;
}



/*************************************************************************
【函数名称】       IdentityConfirm
【函数功能】       检查用户名密码是否匹配
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void Login::IdentityConfirm()
{
    std::string username = ui->username->text().toStdString();
    std::string password = ui->password->text().toStdString();

    if (Platform::u_login_succeed(username, password))
    {
        P_USER user(username);

        if (!user.exist())
        {
            //弹提示框
        }
        else
        {
            emit s_loginSucceed(user);
        }
    }
    else
    {
        emit s_loginFailed();
    }
}


/*************************************************************************
【函数名称】       GoHomepage
【函数功能】       进入个人主页
【参数】
                  P_USER   user   输入
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void Login::GoHomepage(P_USER user)
{
    homepage = new HomePage(nullptr, user);
    homepage->setWindowTitle("众包翻译平台-个人主页");
    connect(homepage, &HomePage::s_returnMain, this,
            &Login::ReturnMain);       //监听个人主页退出
    homepage->show();
    this->close();
}


/*************************************************************************
【函数名称】       LoginFailed
【函数功能】       登录失败
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void Login::LoginFailed()
{
    qDebug() << "loginFailed()";
    QMessageBox* warn = new QMessageBox(QMessageBox::Warning, "Warning",
                                        "Your username or password is wrong. Please try again.",
                                        QMessageBox::Yes, this);
    warn->show();
}


/*************************************************************************
【函数名称】       ReturnMain
【函数功能】       返回上一页面
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void Login::ReturnMain()
{
    emit s_returnMain();
}



