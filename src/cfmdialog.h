/*************************************************************************
【文件名】                 cfmdialog.h
【功能模块和目的】          CfmDialog类声明
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/

#ifndef CFMDIALOG_H
#define CFMDIALOG_H

#include <QDialog>
#include "Platform.h"

namespace Ui
{
    class CfmDialog;
}

/*************************************************************************
【类名】              CfmDialog
【功能】              前端-提示界面-通用确认
【接口说明】
                     1. 构造函数，用于构造界面
                     2. 析构函数
【开发者及日期】      魏欣然 2019/08/01
【更改记录】          无
*************************************************************************/

class CfmDialog : public QDialog
{
    Q_OBJECT

public:
    //构造函数
    explicit CfmDialog(QWidget* parent = nullptr, QWidget* parentWindow = nullptr,
                       QString  confirmContent = nullptr);
    //析构函数
    ~CfmDialog();

protected:
    //关闭本页面
    void CloseThis();
    //确认
    void Confirm();

signals:
    //返回信号，携带P_MSN型参数，携带页面指针参数
    void s_returnM1(P_MSN mission, CfmDialog* cfmPge);
    //返回信号，携带P_MNG型参数，携带页面指针参数
    void s_returnM2(P_MNG mission, CfmDialog* cfmPge);
    //返回信号，携带P_MNG型参数，携带是否通过参数
    void s_returnM3(P_MSN mission, CfmDialog* cfmPge, bool result);
    //返回信号，携带P_USER型参数，携带页面指针参数
    void s_returnU(P_USER user, CfmDialog* cfmPge);
    //返回信号，携带页面指针参数
    void s_confirmed(CfmDialog* cfmpge);
    //返回信号，不携带参数
    void s_return();

protected:
    Ui::CfmDialog* ui;
    QString confirmContent;
    QWidget* parentWindow;
};



#endif // CFMDIALOG_H
