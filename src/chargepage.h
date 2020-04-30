/*************************************************************************
【文件名】                 chargepage.h
【功能模块和目的】          ChargePage类声明
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/


#ifndef CHARGEPAGE_H
#define CHARGEPAGE_H

#include <QMainWindow>
#include "chargecfmdialog.h"

namespace Ui
{
    class ChargePage;
}

/*************************************************************************
【类名】              ChargePage
【功能】              前端-功能界面-充值
【接口说明】
                     1. 构造函数，用于构造界面
                     2. 析构函数
【开发者及日期】      魏欣然 2019/08/01
【更改记录】          无
*************************************************************************/

class ChargePage : public QMainWindow
{
    Q_OBJECT

public:
    //构造函数
    explicit ChargePage(QWidget* parent = nullptr, P_USER user = nullptr);
    //析构函数
    ~ChargePage();

private:
    //返回上一页面
    void ReturnLast();
    //确认充值
    void ConfirmCharge();
    //充值成功
    void ChargeSucceed(P_USER user, CfmDialog* cfmPge);

signals:
    //信号-返回上一页面
    void s_returnLast(ChargePage* pge);

private:
    Ui::ChargePage* ui;
    P_USER user;
};

#endif // CHARGEPAGE_H
