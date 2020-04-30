/*************************************************************************
【文件名】                 useraccount.h
【功能模块和目的】          UserAccount类声明
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/

#ifndef USERACCOUNT_H
#define USERACCOUNT_H

#include <QMainWindow>
#include "chargepage.h"

namespace Ui
{
    class UserAccount;
}

/*************************************************************************
【类名】              UserAccount
【功能】              前端-信息界面-用户账号
【接口说明】
                     1. 构造函数，用于构造界面
                     2. 析构函数
【开发者及日期】      魏欣然 2019/08/01
【更改记录】          无
*************************************************************************/

class UserAccount : public QMainWindow
{
    Q_OBJECT

public:
    //构造函数
    explicit UserAccount(QWidget* parent = nullptr, P_USER user = nullptr);
    //析构函数
    ~UserAccount();

private:
    //表格初始化
    void TableInitialize();

    //充值界面
    void GoCharge();
    //充值界面返回
    void ChargePgeReturn(ChargePage* nxtpge);
    //返回上一页
    void ReturnLast();

signals:
    //信号-返回上一页面
    void s_returnLast(UserAccount* pge);

private:
    Ui::UserAccount* ui;
    P_USER user;

};

#endif // USERACCOUNT_H
