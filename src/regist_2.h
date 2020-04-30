/*************************************************************************
【文件名】                 regist_2.h
【功能模块和目的】          Regist_2类声明
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/

#ifndef REGIST_2_H
#define REGIST_2_H

#include <QMainWindow>
#include <QSqlQuery>
#include "regist_3.h"

namespace Ui
{
    class Regist_2;
}

/*************************************************************************
【类名】              Regist_2
【功能】              前端-功能界面-注册页2
【接口说明】
                     1. 构造函数，用于构造界面
                     2. 析构函数
【开发者及日期】      魏欣然 2019/08/01
【更改记录】          无
*************************************************************************/

class Regist_2 : public QMainWindow
{
    Q_OBJECT

public:
    //构造函数
    explicit Regist_2(QWidget* parent = nullptr, std::string name = "",
                      std::string id = "", std::string email = "", std::string reanName = "");
    //析构函数
    ~Regist_2();

private:
    //注册取消
    void RegCancel();
    //注册成功
    void RegSucceed(P_USER tempUser);

private slots:
    //继续注册
    void on_continue_2_clicked();

signals:
    //注册取消
    void s_regCancel();
    //注册成功
    void s_regSucceed(P_USER tempUser);

private:
    Ui::Regist_2* ui;
    Regist_3* nxtpge;
    std::string tempName;
    std::string tempID;
    std::string tempRealName;
    std::string tempEmail;
    std::string tempPW;
};

#endif // regist_2_H
