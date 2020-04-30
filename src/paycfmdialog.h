/*************************************************************************
【文件名】                 paycfmdialog.h
【功能模块和目的】          PayCfmDialog类声明
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/

#ifndef PAYCFMDIALOG_H
#define PAYCFMDIALOG_H

#include "cfmdialog.h"

/*************************************************************************
【类名】              PayCfmDialog
【功能】              前端-提示界面-支付确认
【接口说明】
                     1. 构造函数，用于构造界面
                     2. 析构函数
【开发者及日期】      魏欣然 2019/08/01
【更改记录】          无
*************************************************************************/

class PayCfmDialog : public CfmDialog
{
public:
    //构造函数
    explicit PayCfmDialog(QWidget* parent = nullptr,
                          QWidget* parentWindow = nullptr, P_MSN mission = nullptr,
                          QString  confirmContent = nullptr);
    //析构函数
    ~PayCfmDialog();

private:
    //成功
    void SuccessNotice();
    //失败
    void FailNotice();
    //返回上一页面
    void ReturnDone();

private:
    P_MSN mission;
};

#endif // PAYCFMDIALOG_H
