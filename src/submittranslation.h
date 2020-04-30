/*************************************************************************
【文件名】                 submittranslation.h
【功能模块和目的】          SubmitTranslation类声明
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/

#ifndef SUBMITTRANSLATION_H
#define SUBMITTRANSLATION_H

#include <QMainWindow>
#include <QPlainTextEdit>
#include "Platform.h"

namespace Ui
{
    class SubmitTranslation;
}

/*************************************************************************
【类名】              SubmitTranslation
【功能】              前端-功能界面-提交译文
【接口说明】
                     1. 构造函数，用于构造界面
                     2. 析构函数
【开发者及日期】      魏欣然 2019/08/01
【更改记录】          无
*************************************************************************/


class SubmitTranslation : public QMainWindow
{
    Q_OBJECT

public:
    //构造函数
    explicit SubmitTranslation(QWidget* parent = nullptr,
                               P_SUB sub = P_SUB(KEY_SUB_NULL));
    //析构函数
    ~SubmitTranslation();

private:
    //表格初始化
    void TableInitialize();

    //提交按钮响应
    void SubmitClicked();
    //返回上一页面
    void ReturnLast();

signals:
    //信号-返回上一页面
    void s_return(SubmitTranslation* subpge);

private:
    Ui::SubmitTranslation* ui;
    P_SUB subMission;
    QPlainTextEdit* edit1;
};

#endif // SUBMITTRANSLATION_H
