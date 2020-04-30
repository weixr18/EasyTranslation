/*************************************************************************
【文件名】                 choosemanager.h
【功能模块和目的】          ChooseManager类声明
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/

#ifndef CHOOSEMANAGER_H
#define CHOOSEMANAGER_H

#include <QMainWindow>
#include <QPushButton>
#include "chsmcfmdialog.h"
#include "userinfo.h"

namespace Ui
{
    class ChooseManager;
}

/*************************************************************************
【类名】              ChooseManager
【功能】              前端-功能界面-选择负责人
【接口说明】
                     1. 构造函数，用于构造界面
                     2. 析构函数
【开发者及日期】      魏欣然 2019/08/01
【更改记录】          无
*************************************************************************/

class ChooseManager : public QMainWindow
{
    Q_OBJECT

public:
    //构造函数
    explicit ChooseManager(QWidget* parent = nullptr, P_MSN p_mission = nullptr);
    //析构函数
    ~ChooseManager();

private:
    //表格初始化
    void TableInitialize();
    //设置选择负责人按钮
    void SetChooseMButton(QPushButton* btn, P_USER user);
    //设置查看申请人信息按钮
    void SetShowUserInfoButton(QPushButton* btn, P_USER user);

    //选择取消
    void ChsCancel();
    //选择成功
    void ChooseMSucceed(P_USER user, CfmDialog* cfmPge);
    //查看负责人信息页返回
    void ViewUserReturn(UserInfo* userinfo);

signals:
    //信号-选择取消
    void s_chsCancel(ChooseManager* ChoosePge);
    //信号-选择成功
    void s_chsSucceed(ChooseManager* ChoosePge);

private:
    Ui::ChooseManager* ui;
    P_MSN mission;
};


#endif // CHOOSEMANAGER_H
