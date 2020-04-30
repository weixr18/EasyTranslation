/*************************************************************************
【文件名】                 choosetranslator.h
【功能模块和目的】          ChooseTranslator类声明
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/

#ifndef CHOOSETRANSLATOR_H
#define CHOOSETRANSLATOR_H

#include <QMainWindow>
#include <QPushButton>
#include "missionassign.h"

namespace Ui
{
    class ChooseTranslator;
}

/*************************************************************************
【类名】              ChooseTranslator
【功能】              前端-功能界面-选择翻译者
【接口说明】
                     1. 构造函数，用于构造界面
                     2. 析构函数
【开发者及日期】      魏欣然 2019/08/01
【更改记录】          无
*************************************************************************/

class ChooseTranslator : public QMainWindow
{
    Q_OBJECT

public:
    //构造函数
    explicit ChooseTranslator(QWidget* parent = nullptr,
                              P_MNG mngMission = P_MNG(""));
    //析构函数
    ~ChooseTranslator();

private:
    //选择取消
    void ChsCancel();
    //选择完成
    void ChsComplete();

    //表格初始化
    void TableInitialize();
    //设置查看申请者信息按钮
    void SetShowUserInfoButton(QPushButton* btn, P_USER p_user);

    //查看信息页返回
    void ViewUserReturn(UserInfo* userinfo);
    //返回上一页面
    void ReturnLast(MissionAssign* nxtpge);

private slots:
    //确认按钮响应
    void OnButtonClicked(QAbstractButton*);

signals:
    //信号-选择取消
    void s_chsCancel(ChooseTranslator* chsPge);
    //信号-选择成功
    void s_chsSucceed(ChooseTranslator* chsPge);

private:
    Ui::ChooseTranslator* ui;
    P_MNG mngMission;
    std::vector<std::string> tmpTranslators;
    QButtonGroup* pBG;

};


#endif // CHOOSETRANSLATOR_H
