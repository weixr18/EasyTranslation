/*************************************************************************
【文件名】                 releasemission.h
【功能模块和目的】          ReleaseMission类声明
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/


#ifndef RELEASEMISSION_H
#define RELEASEMISSION_H

#include <QMainWindow>
#include <QMessageBox>
#include <QButtonGroup>
#include "releasemission_2.h"

namespace Ui
{
    class ReleaseMission;
}

/*************************************************************************
【类名】              ReleaseMission
【功能】              前端-功能界面-发布任务页
【接口说明】
                     1. 构造函数，用于构造界面
                     2. 析构函数
【开发者及日期】      魏欣然 2019/08/01
【更改记录】          无
*************************************************************************/

class ReleaseMission : public QMainWindow
{
    Q_OBJECT

public:
    //构造函数
    explicit ReleaseMission(QWidget* parent = nullptr, P_USER user = nullptr );
    //析构函数
    ~ReleaseMission();

private:
    //取消发布
    void RlsCancel();
    //继续发布
    void RlsContinue();
    //发布成功
    void RlsSucceed(P_MSN mission);

    bool FormatCheckPass();

    bool LanguageChecked();

signals:
    //信号-发布取消
    void s_rlsCancel();
    //信号-发布成功
    void s_rlsSucceed(P_MSN mission);

private:
    Ui::ReleaseMission* ui;
    P_USER user;
    ReleaseMission_2* nxtpge;           //继续发布

    QButtonGroup* m_srcBtnGrp;
    QButtonGroup* m_tarBtnGrp;

    std::string tempName;
    std::string tempText;
    std::string tempIntro;
    Mission::Language tempSrcLang;
    Mission::Language tempTarLang;
};


#endif // RELEASEMISSION_H
