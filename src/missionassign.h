/*************************************************************************
【文件名】                 missionassign.h
【功能模块和目的】          MissionAssign类声明
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/

#ifndef MISSIONASSIGN_H
#define MISSIONASSIGN_H

#include <QMainWindow>
#include <QTextCursor>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QButtonGroup>
#include "userinfo.h"

namespace Ui
{
    class MissionAssign;
}

/*************************************************************************
【类名】              MissionAssign
【功能】              前端-功能界面-任务分配
【接口说明】
                     1. 构造函数，用于构造界面
                     2. 析构函数
【开发者及日期】      魏欣然 2019/08/01
【更改记录】          无
*************************************************************************/

class MissionAssign : public QMainWindow
{
    Q_OBJECT

public:
    //构造函数
    explicit MissionAssign(QWidget* parent = nullptr, P_MNG mngMission = P_MNG(""));
    //析构函数
    ~MissionAssign();

private:
    //表格初始化
    void TableInitialize();
    //设置翻译者个人信息按钮
    void SetShowUserInfoButton(QPushButton* btn, P_USER p_user);

    //查看个人信息页返回
    void ViewUserReturn(UserInfo* userinfo);
    //分配完成
    void AssignComplete();
    //返回上一页面
    void ReturnLast();
    //分配框已填满
    bool TextFilled();

private slots:
    //剪切
    void OnCutClicked();
    //粘贴
    void OnButtonClicked(int id);

signals:
    //信号-分配完成
    void s_asgSucceed(MissionAssign* pge);

private:
    Ui::MissionAssign* ui;
    const P_MNG mngMission;
    std::vector<std::string> translators;

    QButtonGroup* pBG;
    std::vector<QPlainTextEdit*> edits;
    QString ClipBoard;
    bool pasted{true};
};


#endif // MISSIONASSIGN_H
