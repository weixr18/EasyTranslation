/*************************************************************************
【文件名】                 checktranslation.h
【功能模块和目的】          CheckTranslation类声明
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/

#ifndef CHECKTRANSLATION_H
#define CHECKTRANSLATION_H

#include <QMainWindow>
#include <QPlainTextEdit>
#include "lastsubmittal.h"

namespace Ui
{
    class CheckTranslation;
}

/*************************************************************************
【类名】              CheckTranslation
【功能】              前端-功能界面-审核译文
【接口说明】
                     1. 构造函数，用于构造界面
                     2. 析构函数
【开发者及日期】      魏欣然 2019/08/01
【更改记录】          无
*************************************************************************/

class CheckTranslation : public QMainWindow
{
    Q_OBJECT

public:
    //构造函数
    explicit CheckTranslation(QWidget* parent = nullptr, P_MNG mng = P_MNG(""));
    //析构函数
    ~CheckTranslation();

private:
    //返回上一页面，并关闭下一页面
    void ReturnLast(LastSubmittal* nxtpge);
    //仅返回上一页面
    void ReturnLast2();
    //翻译者列表初始化
    void TranslatorInitialize();
    //其他部分初始化
    void TableInitialize();

    //设置反馈
    void SetFeedback();
    //接受译文
    void AcceptTranslation();
    //接受译文成功
    void AcceptSucceed(CfmDialog* cfmpge);

    //完成按钮可见性判断
    bool CompleteVisible();
    //最终提交
    void LastSubmit();

signals:
    //信号-返回上一页面
    void s_return(CheckTranslation* subpge);

private:
    Ui::CheckTranslation* ui;
    P_MNG mng;
    P_SUB crtSub;
    QPlainTextEdit* edit1;
};


#endif // CHECKTRANSLATION_H
