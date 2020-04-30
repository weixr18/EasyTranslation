/*************************************************************************
【文件名】                 aplmcfmdialog.h
【功能模块和目的】          AplMCfmDialog类声明
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/

#ifndef APLMCFMDIALOG_H
#define APLMCFMDIALOG_H

#include "cfmdialog.h"

/*************************************************************************
【类名】              AplMCfmDialog
【功能】              前端-提示界面-申请负责人确认
【接口说明】
                     1. 构造函数，用于构造界面
                     2. 析构函数
【开发者及日期】      魏欣然 2019/08/01
【更改记录】          无
*************************************************************************/

class AplMCfmDialog:
    public CfmDialog
{
public:

    //构造函数
    explicit AplMCfmDialog(QWidget* parent = nullptr,
                           QWidget* parentWindow = nullptr, P_MSN mission = nullptr,
                           QString confirmContent = nullptr, P_USER user = nullptr);
    //析构函数
    ~AplMCfmDialog();

private:
    //资格审查
    void QualityCheck();
    //返回上一页面
    void ReturnDone();

private:
    P_MSN mission;
    P_USER user;
    bool result{false};
};


#endif // APLMCFMDIALOG_H
