/*************************************************************************
【文件名】                 missionhall.h
【功能模块和目的】          MissionHall类声明
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/

#ifndef MISSIONHALL_H
#define MISSIONHALL_H

#include <QMainWindow>
#include <QPushButton>
#include "missioninfo.h"
#include "cfmdialog.h"
#include "Datum.h"

namespace Ui
{
    class MissionHall;
}

/*************************************************************************
【类名】              MissionHall
【功能】              前端-功能界面-任务大厅
【接口说明】
                     1. 构造函数，用于构造界面
                     2. 析构函数
【开发者及日期】      魏欣然 2019/08/01
【更改记录】          无
*************************************************************************/


class MissionHall : public QMainWindow
{
    Q_OBJECT

public:
    //构造函数
    explicit MissionHall(QWidget* parent = nullptr, P_USER user = nullptr);
    //析构函数
    ~MissionHall();

private:
    //表格初始化
    void TableInitialize();
    //载入任务大厅显示的任务
    void SetUserHallMissions();
    //发布阶段任务初始化
    void RlsTableInitialize();
    //负责阶段任务初始化
    void MngTableInitialize();

    //设置任务信息页按钮
    void SetBMissionInfo();
    //任务信息页返回
    void MsnInfoReturn(MissionInfo* infoPge);

    //设置任务操作按钮，参数为P_MSN
    void SetMissionOprtButton(QPushButton* btn, P_MSN mission);
    //设置任务操作按钮，参数为P_MNG
    void SetMissionOprtButton(QPushButton* btn, P_MNG mission);

    //返回上一页
    void ReturnHomePage();

private slots:
    //申请负责人成功
    void ApplyMReturn(P_MSN mission, CfmDialog* cfmPge, bool result);
    //申请翻译者成功
    void ApplyTSucceed(P_MNG mission, CfmDialog* cfmPge);

signals:
    //信号-返回上一页面
    void s_returnHomePage();

private:
    Ui::MissionHall* ui;
    P_USER user;
    std::vector<P_MSN> userHallMissions;
    std::vector<P_MNG> userHallMngMissions;
};


#endif // MISSIONHALL_H
