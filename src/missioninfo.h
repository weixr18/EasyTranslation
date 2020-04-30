/*************************************************************************
【文件名】                 missioninfo.h
【功能模块和目的】          MissionInfo类声明
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/

#ifndef MISSIONINFO_H
#define MISSIONINFO_H

#include <QMainWindow>
#include <QPushButton>
#include "userinfo.h"
#include "Platform.h"

namespace Ui
{
    class MissionInfo;
}

/*************************************************************************
【类名】              MissionInfo
【功能】              前端-信息界面-任务信息
【接口说明】
                     1. 构造函数，用于构造界面（+3重载）
                     2. 析构函数
【开发者及日期】      魏欣然 2019/08/01
【更改记录】          无
*************************************************************************/


class MissionInfo : public QMainWindow
{
    Q_OBJECT

public:
    //构造函数，参数为P_MSN
    explicit MissionInfo(QWidget* parent = nullptr, P_MSN mission = nullptr);
    //构造函数，参数为P_MNG
    explicit MissionInfo(QWidget* parent = nullptr, P_MNG mng = P_MNG(""));
    //构造函数，参数为P_SUB
    explicit MissionInfo(QWidget* parent = nullptr,
                         P_SUB sub = P_SUB(KEY_SUB_NULL));
    //析构函数
    ~MissionInfo();

private:
    //基本信息初始化
    void BasicInitial(P_MSN pMission);
    //负责阶段信息初始化
    void MngInfoInitial(P_MNG pMng);
    //翻译者信息初始化
    void TrslInfoInitial(P_MNG pMng);
    //任务成果信息初始化
    void ResultInitial(P_MNG pMng);

    //设置用户信息页按钮
    void SetBUserInfo();
    //用户信息页返回
    void ViewUserReturn(UserInfo* userinfo);
    //返回上一页面
    void ReturnLast();

signals:
    void s_return(MissionInfo* missioninfo);

private:
    Ui::MissionInfo* ui;

};



#endif // MISSIONINFO_H
