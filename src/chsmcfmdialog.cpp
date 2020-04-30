/*************************************************************************
【文件名】                 chsmcfmdialog.cpp
【功能模块和目的】          ChsMCfmDialog类实现
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/


#include "chsmcfmdialog.h"
#include <QMessageBox>
#include <QDebug>


/*************************************************************************
【函数名称】       ChsMCfmDialog
【函数功能】       ChsMCfmDialog类构造函数 构造该页面
【参数】
                  QWidget*   parent               输入
                  QWidget*   parentWindow         输入
                  P_USER     user                 输入
                  QString    confirmContent       输入
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
ChsMCfmDialog::ChsMCfmDialog(QWidget* parent, QWidget* parentWindow ,
                             P_USER user, QString confirmContent) :
    CfmDialog::CfmDialog(parent, parentWindow, confirmContent),
    user(user)
{
    connect(this, &ChsMCfmDialog::s_confirmed, this, &ChsMCfmDialog::SuccessNotice);
}


/*************************************************************************
【函数名称】       ~ChsMCfmDialog
【函数功能】       ChsMCfmDialog类析构函数
【参数】           void
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
ChsMCfmDialog::~ChsMCfmDialog()
{}


/*************************************************************************
【函数名称】       SuccessNotice
【函数功能】       选择成功提醒
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void ChsMCfmDialog::SuccessNotice()
{
    QMessageBox* succeed = new QMessageBox(QMessageBox::Information, "Notice",
        "Set manager succeed.\n You can view the mission status on your home page.",
        QMessageBox::Ok, this);
    succeed->show();
    connect(succeed, &QMessageBox::accepted, this, &ChsMCfmDialog::ReturnDone);
}


/*************************************************************************
【函数名称】       ReturnDone
【函数功能】       返回上一页面
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void ChsMCfmDialog::ReturnDone()
{
    emit s_returnU(user, this);
}

