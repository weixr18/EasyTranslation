/*************************************************************************
【文件名】                 rcrtmfailproc.h
【功能模块和目的】          RcrtMFailProc类声明
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/

#ifndef RCRTMFAILPROC_H
#define RCRTMFAILPROC_H

#include <QMainWindow>
#include "Platform.h"

namespace Ui
{
    class RcrtMFailProc;
}

/*************************************************************************
【类名】              RcrtMFailProc
【功能】              前端-功能界面-招募负责人失败
【接口说明】
                     1. 构造函数，用于构造界面
                     2. 析构函数
【开发者及日期】      魏欣然 2019/08/01
【更改记录】          无
*************************************************************************/

class RcrtMFailProc : public QMainWindow
{
    Q_OBJECT

public:
    //构造函数
    explicit RcrtMFailProc(QWidget* parent = nullptr, P_MSN mission = P_MSN(""));
    //析构函数
    ~RcrtMFailProc();

private:
    //取消任务
    void CancelMission();
    //延长招募时间
    void ExtendRcrtMTime();

private slots:
    //返回键响应
    void on_cancel_clicked();
    //radio更换响应
    void on_radio_delay_toggled(bool checked);
    //确认键响应
    void on_confirm_clicked();

signals:
    //信号-返回上一页面
    void s_returnLast(RcrtMFailProc* pge);

private:
    Ui::RcrtMFailProc* ui;
    P_MSN mission;
};

#endif // RCRTMFAILPROC_H
