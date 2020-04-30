/*************************************************************************
【文件名】                 userinfo.h
【功能模块和目的】          UserInfo类声明
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/

#ifndef USERINFO_H
#define USERINFO_H

#include <QDialog>
#include "Platform.h"

class MissionInfo;

namespace Ui
{
    class UserInfo;
}

/*************************************************************************
【类名】              UserInfo
【功能】              前端-信息界面-用户信息
【接口说明】
                     1. 构造函数，用于构造界面
                     2. 析构函数
【开发者及日期】      魏欣然 2019/08/01
【更改记录】          无
*************************************************************************/

class UserInfo : public QDialog
{
    Q_OBJECT

public:
    //构造函数
    explicit UserInfo(QWidget* parent = nullptr, P_USER user = nullptr);
    //析构函数
    ~UserInfo();

private:
    //表格初始化
    void TableInitialize();
    //基本信息初始化
    void BasicInitial();
    //发布任务初始化
    void RlsInitial();
    //负责任务初始化
    void MngInitial();
    //参与任务初始化
    void PtcpInitial();

    //设置任务信息按钮
    void SetMissionBtn();
    //任务信息页返回
    void MsnInfoReturn(MissionInfo* infoPge);
    //返回上一页
    void ReturnLast();

signals:
    //信号-返回上一页
    void s_return(UserInfo* userinfo);

private:
    Ui::UserInfo* ui;
    P_USER user;
};

#endif // USERINFO_H
