/*************************************************************************
【文件名】                 chsmcfmdialog.h
【功能模块和目的】          ChsMCfmDialog类声明
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/

#ifndef CHSMCFMDIALOG_H
#define CHSMCFMDIALOG_H
#include "cfmdialog.h"

/*************************************************************************
【类名】              ChsMCfmDialog
【功能】              前端-提示界面-选择负责人确认
【接口说明】
                     1. 构造函数，用于构造界面
                     2. 析构函数
【开发者及日期】      魏欣然 2019/08/01
【更改记录】          无
*************************************************************************/

class ChsMCfmDialog:
    public CfmDialog
{
public:
    //构造函数
    explicit ChsMCfmDialog(QWidget* parent = nullptr,
                           QWidget* parentWindow = nullptr, P_USER user = nullptr,
                           QString confirmContent = nullptr);
    //析构函数
    ~ChsMCfmDialog();

private:
    //操作成功
    void SuccessNotice();
    //返回上一页面
    void ReturnDone();

private:
    P_USER user;
};

#endif // CHSMCFMDIALOG_H
