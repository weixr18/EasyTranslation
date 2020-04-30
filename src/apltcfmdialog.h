/*************************************************************************
【文件名】                 apltcfmdialog.h
【功能模块和目的】          AplTCfmDialog类声明
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/

#ifndef APLTCFMDIALOG_H
#define APLTCFMDIALOG_H

#include "cfmdialog.h"
#include "managemission.h"

/*************************************************************************
【类名】              AplTCfmDialog
【功能】              前端-提示界面-申请翻译者确认
【接口说明】
                     1. 构造函数，用于构造界面
                     2. 析构函数
【开发者及日期】      魏欣然 2019/08/01
【更改记录】          无
*************************************************************************/

class AplTCfmDialog:
    public CfmDialog
{
public:
    //构造函数
    explicit AplTCfmDialog(QWidget* parent = nullptr,
                           QWidget* parentWindow = nullptr, P_MNG mng = P_MNG(""),
                           QString  confirmContent = nullptr);
    //析构函数
    ~AplTCfmDialog();

private:
    //报名成功
    void SuccessNotice();
    //返回上一页
    void ReturnDone();

private:
    P_MNG mng;
};


#endif // APLTCFMDIALOG_H
