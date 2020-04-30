/*************************************************************************
【文件名】                 chargecfmdialog.cpp
【功能模块和目的】          ChargeCfmDialog类实现
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/


#include "chargecfmdialog.h"
#include <QMessageBox>
#include <QDebug>


/*************************************************************************
【函数名称】        ChargeCfmDialog
【函数功能】        ChargeCfmDialog类构造函数 构造该页面
【参数】
                  QWidget* parent               输入
                  QWidget* parentWindow         输入
                  P_USER   user                 输入
                  QString  confirmContent       输入
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
ChargeCfmDialog::ChargeCfmDialog(QWidget* parent, QWidget* parentWindow,
                                 P_USER user, QString confirmContent) :
    CfmDialog::CfmDialog(parent, parentWindow, confirmContent),
    user(user)
{
    connect(this, &ChargeCfmDialog::s_confirmed, this,
        &ChargeCfmDialog::SuccessNotice);
}


/*************************************************************************
【函数名称】       ~ChargeCfmDialog
【函数功能】       ChargeCfmDialog类析构函数
【参数】           void
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
ChargeCfmDialog::~ChargeCfmDialog()
{
    qDebug() << "~ChargeCfmDialog()";
}

/*************************************************************************
【函数名称】       SuccessNotice
【函数功能】       申请成功
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void ChargeCfmDialog::SuccessNotice()
{
    QMessageBox* succeed = new QMessageBox(QMessageBox::Information, "Notice",
        "Charge succeed!\n ", QMessageBox::Ok, this);
    succeed->show();
    connect(succeed, &QMessageBox::accepted, this, &ChargeCfmDialog::ReturnDone);
}

/*************************************************************************
【函数名称】       ReturnDone
【函数功能】       返回上一页面
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void ChargeCfmDialog::ReturnDone()
{
    emit s_returnU(user, this);
}

