/*************************************************************************
【文件名】                 homepage.h
【功能模块和目的】          HomePage类声明
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/

#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QMainWindow>
#include <QPushButton>
#include <vector>

#include "releasemission.h"
#include "missionhall.h"
#include "useraccount.h"
#include "messagebox.h"

#include "choosemanager.h"
#include "choosetranslator.h"
#include "submittranslation.h"
#include "checktranslation.h"
#include "payformission.h"

#include "missioninfo.h"
#include "stateupdatew.h"
#include "rcrtmfailproc.h"

namespace Ui
{
    class HomePage;
}

/*************************************************************************
【类名】              HomePage
【功能】              前端-功能界面-个人主页
【接口说明】
                     1. 构造函数，用于构造界面
                     2. 析构函数
【开发者及日期】      魏欣然 2019/08/01
【更改记录】          无
*************************************************************************/

class MainWindow;

class HomePage : public QMainWindow
{
    Q_OBJECT

public:
    //构造函数
    explicit HomePage(QWidget* parent = nullptr, P_USER user = nullptr);
    //析构函数
    ~HomePage();

private:

    //*********页面跳转*********
    //进入任务大厅页
    void GoMissionHall();
    //任务大厅页关闭
    void CloseMissionHall();

    //进入发布任务页
    void GoReleaseMission();
    //发布任务页关闭
    void CloseRelease();

    void GoMessageBox();

    void CloseMessageBox();

    //进入个人账户页
    void GoMyAccount();
    //个人账户页关闭
    void CloseAccount();

    //设置选择负责人按钮
    void SetBChooseM();
    //负责人选择取消
    void ChooseMCancel(ChooseManager* choosePge);
    //负责人选择成功
    void ChooseMSucceed(ChooseManager* choosePge);

    //设置选择翻译者按钮
    void SetBChooseT();
    //翻译者选择取消
    void ChooseTCancel(ChooseTranslator* choosePge);
    //翻译者选择成功
    void ChooseTSucceed(ChooseTranslator* choosePge);

    //设置提交译文页按钮
    void SetBSubTrans();
    //提交译文页返回
    void SubmitTransReturn(SubmitTranslation* subPge);

    //设置审核译文页按钮
    void SetBCheckTrans();
    //审核译文页返回
    void CheckTransReturn(CheckTranslation* chkPge);

    //设置支付页按钮
    void SetBPayForMission();
    //支付取消
    void PayCancel(PayForMission* payPge);
    //支付成功
    void PaySucceed(PayForMission* payPge);

    //设置任务信息页按钮
    void SetBMissionInfo();
    //人物信息页返回
    void MsnInfoReturn(MissionInfo* infoPge);

    //设置招募负责人失败处理页按钮
    void SetBRcrtMFail();
    //招募负责人失败处理页返回
    void RcrtMFailReturn(RcrtMFailProc* pcspge);


    //*********页面初始化*********

    //获取用户相关的任务
    void GetUserMissions();
    //表格初始化
    void TableInitialize();
    //发布任务表格初始化
    void RlsTableInitialize();
    //负责任务表格初始化
    void MngTableInitialize();
    //参与翻译任务表格初始化
    void PtcpTableInitialize();

    //设置发布任务操作按钮
    void SetRlsMissionOprtButton(QPushButton* btn,  P_MSN mission);
    //设置负责任务操作按钮-参数为P_MSN
    void SetMngMissionOprtButton(QPushButton* btn, P_MSN mission);
    //设置负责任务操作按钮-参数为P_MNG
    void SetMngMissionOprtButton(QPushButton* btn, P_MNG mng);
    //设置参与任务操作按钮-参数为P_MNG
    void SetPtcpMissionOprtButton(QPushButton* btn, P_MNG mng);
    //设置参与任务操作按钮-参数为P_MSUB
    void SetPtcpMissionOprtButton(QPushButton* btn, P_SUB sub);
    //页面更新
    void PageRefresh();

private slots:
    //退出登录
    void Exit_clicked();

signals:
    //信号-返回起始页
    void s_returnMain();

private:
    Ui::HomePage* ui;
    ReleaseMission* releasePg;
    MissionHall* missionHall;
    UserAccount* userAccount;
    MessageBox* messageBox;

    std::vector<std::string> releasedMissions;
    std::vector<std::string> inChargeMissions;
    std::vector<std::string> participatingMissions;

    StateUpdateW* pS;
    P_USER user;

};


#endif // HOMEPAGE_H
