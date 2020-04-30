/*************************************************************************
【文件名】                 mainwindow.h
【功能模块和目的】          MainWindow类声明
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlError>
#include "login.h"
#include "regist.h"
#include "DBOP.h"

namespace Ui
{
    class MainWindow;
}

/*************************************************************************
【类名】              MainWindow
【功能】              前端-功能界面-起始页
【接口说明】
                     1. 构造函数，用于构造界面
                     2. 析构函数
【开发者及日期】      魏欣然 2019/08/01
【更改记录】          无
*************************************************************************/

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //构造函数
    explicit MainWindow(QWidget* parent = nullptr);
    //析构函数
    ~MainWindow();

private:
    //登录
    void GoLogin();
    //注册
    void GoRegister();
    //返回本页面
    void ReturnMain();
    //注册成功
    void RegSucceed();

signals:
    //信号-登录
    void s_login();

private:
    Ui::MainWindow* ui;
    Login* login;
    Regist* regist;

};

#endif // MAINWINDOW_H
