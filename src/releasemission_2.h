/*************************************************************************
【文件名】                 releasemission_2.h
【功能模块和目的】          ReleaseMission_2类声明
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/

#ifndef RELEASEMISSION_2_H
#define RELEASEMISSION_2_H

#include <QMainWindow>
#include "Platform.h"

namespace Ui
{
    class ReleaseMission_2;
}

/*************************************************************************
【类名】              ReleaseMission_2
【功能】              前端-功能界面-发布任务页2
【接口说明】
                     1. 构造函数，用于构造界面
                     2. 析构函数
【开发者及日期】      魏欣然 2019/08/01
【更改记录】          无
*************************************************************************/


class ReleaseMission_2 : public QMainWindow
{
    Q_OBJECT

public:
    //构造函数
    explicit ReleaseMission_2(QWidget* parent = nullptr, P_USER user = nullptr,
                              std::string tempName = "", std::string tempText = "",
                              std::string tempIntro = "",
                              Mission::Language tempSrcLang = Mission::ENGLISH,
                              Mission::Language tempTarLang = Mission::CHINESE);
    //析构函数
    ~ReleaseMission_2();

private:
    //发布取消
    void RlsCancel();
    //发布继续
    void RlsContinue();
    //发布成功
    void RlsSucceed();

signals:
    //信号-发布取消
    void s_rlsCancel();
    //信号-发布继续
    void s_rlsContinue();
    //信号-发布成功
    void s_rlsSucceed(P_MSN mission);

private:
    Ui::ReleaseMission_2* ui;
    P_USER user;
    std::string tempName;
    std::string tempText;
    std::string tempIntro;
    Mission::Language tempSrcLang;
    Mission::Language tempTarLang;
    tm tempRTime;
    tm tempDDL;
    int tempAmount;

};


#endif // RELEASEMISSION_2_H
