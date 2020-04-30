/*************************************************************************
【文件名】                 chargecfmdialog.h
【功能模块和目的】          ChargeCfmDialog类声明
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/

#ifndef CHARGECFMDIALOG_H
#define CHARGECFMDIALOG_H
#include "cfmdialog.h"

/*************************************************************************
【类名】              ChargeCfmDialog
【功能】              前端-提示界面-充值确认
【接口说明】
                     1. 构造函数，用于构造界面
                     2. 析构函数
【开发者及日期】      魏欣然 2019/08/01
【更改记录】          无
*************************************************************************/

class ChargeCfmDialog : public CfmDialog
{
public:
    //构造函数
    explicit ChargeCfmDialog(QWidget* parent = nullptr,
                             QWidget* parentWindow = nullptr, P_USER user = nullptr,
                             QString  confirmContent = nullptr);
    //析构函数
    ~ChargeCfmDialog();

protected:
    //充值成功
    void SuccessNotice();
    //返回上一页面
    void ReturnDone();

private:
    P_USER user;
};

#endif // CHARGECFMDIALOG_H
