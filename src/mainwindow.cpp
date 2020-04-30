/*************************************************************************
【文件名】                 mainwindow.cpp
【功能模块和目的】          MainWindow类实现
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/

#include "mainwindow.h"
#include "ui_start_page.h"
#include <QDebug>


/*************************************************************************
【函数名称】       MainWindow
【函数功能】       MainWindow类构造函数 构造该页面
【参数】
                  QWidget* parent          输入
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    login(nullptr),
    regist(nullptr)
{
    ui->setupUi(this);

    connect(ui->login, &QPushButton::clicked, this,
            &MainWindow::GoLogin);                          //登录
    connect(ui->register_2, &QPushButton::clicked, this,
            &MainWindow::GoRegister);                  //注册
}


/*************************************************************************
【函数名称】       ~MainWindow
【函数功能】       MainWindow类析构函数
【参数】           void
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
MainWindow::~MainWindow()
{
    Datum::UpdateDB();
    delete ui;
}



/*************************************************************************
【函数名称】       GoLogin
【函数功能】       进入登录页面
【参数】           void
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void MainWindow::GoLogin()
{
    login = new Login(this);
    login->setWindowTitle("众包翻译平台-登录");
    connect(this->login, &Login::s_returnMain, this,
            &MainWindow::ReturnMain);                     //登录页返回
    login->show();
    this->hide();
}


/*************************************************************************
【函数名称】       GoLogin
【函数功能】       进入注册页面
【参数】           void
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void MainWindow::GoRegister()
{
    regist = new Regist(this);
    regist->setWindowTitle("众包翻译平台-注册");
    connect(this->regist, &Regist::s_regCancel, this,
            &MainWindow::ReturnMain);                    //注册页返回
    connect(this->regist, &Regist::s_regSucceed, this,
            &MainWindow::RegSucceed);                //注册成功

    regist->show();
    this->hide();
}


/*************************************************************************
【函数名称】       ReturnMain
【函数功能】       返回本页面
【参数】           void
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void MainWindow::ReturnMain()
{
    this->show();

    if (login != nullptr)
    {
        login->close();
    }

    if (regist != nullptr)
    {
        regist->close();
    }
}


/*************************************************************************
【函数名称】       RegSucceed
【函数功能】       注册成功
【参数】           void
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void MainWindow::RegSucceed()
{
    this->show();

    if (login != nullptr)
    {
        login->close();
    }

    if (regist != nullptr)
    {
        regist->close();
    }
}

