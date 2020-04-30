/*************************************************************************
【文件名】                 payformission.h
【功能模块和目的】          PayForMission类声明
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/

#ifndef PAYFORMISSION_H
#define PAYFORMISSION_H

#include <QMainWindow>
#include "paycfmdialog.h"

namespace Ui
{
    class PayForMission;
}

/*************************************************************************
【类名】              PayForMission
【功能】              前端-功能界面-任务支付页
【接口说明】
                     1. 构造函数，用于构造界面
                     2. 析构函数
【开发者及日期】      魏欣然 2019/08/01
【更改记录】          无
*************************************************************************/

class PayForMission : public QMainWindow
{
    Q_OBJECT

public:
    //构造函数
    explicit PayForMission(QWidget* parent = nullptr, P_MSN mission = nullptr);
    //析构函数
    ~PayForMission();

private:
    //确认
    void Confirm();
    //取消
    void Canceled();
    //支付成功
    void Succeed(P_MNG mng, CfmDialog* cfmPge);

signals:
    //信号-支付取消
    void s_canceled(PayForMission* pge);
    //信号-支付成功
    void s_succeed(PayForMission* pge);

private:
    Ui::PayForMission* ui;
    P_MSN mission;
};

#endif // PAYFORMISSION_H
