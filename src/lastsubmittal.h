/*************************************************************************
【文件名】                 lastsubmittal.h
【功能模块和目的】          LastSubmittal类声明
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/

#ifndef LASTSUBMITTAL_H
#define LASTSUBMITTAL_H

#include <QMainWindow>
#include <QButtonGroup>
#include <QPlainTextEdit>
#include "cfmdialog.h"
#include "submission.h"

namespace Ui
{
    class LastSubmittal;
}

/*************************************************************************
【类名】              LastSubmittal
【功能】              前端-功能界面-提交最终译文
【接口说明】
                     1. 构造函数，用于构造界面
                     2. 析构函数
【开发者及日期】      魏欣然 2019/08/01
【更改记录】          无
*************************************************************************/

class LastSubmittal : public QMainWindow
{
    Q_OBJECT

public:
    //构造函数
    explicit LastSubmittal(QWidget* parent = nullptr, P_MNG mng = P_MNG(""));
    //析构函数
    ~LastSubmittal();

private:
    //表格初始化
    void TableInitialize();
    //确认最终提交
    void CfmLastSubmit();
    //译文已全部剪切，提交框已填满
    bool TextFilled();
    //提交成功
    void SubmitSucceed(CfmDialog* cfmpge);

private slots:
    //剪切
    void OnCutClicked(int id);
    //粘贴
    void OnPasteClicked();

signals:
    //信号-返回上一页面
    void s_returnLast(LastSubmittal* pge);

private:
    Ui::LastSubmittal* ui;
    P_MNG mng;
    std::vector<KEY_SUB> submissions;
    QButtonGroup* pBG;

    bool pasted{true};
    QString ClipBoard;
    std::vector<QPlainTextEdit*> edits;

};


#endif // LASTSUBMITTAL_H
