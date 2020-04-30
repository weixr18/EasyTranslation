/*************************************************************************
【文件名】                 paycfmdialog.cpp
【功能模块和目的】          PayCfmDialog类实现
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/



#include "paycfmdialog.h"

#include <QMessageBox>
#include <QDebug>

/*************************************************************************
【函数名称】        PayCfmDialog
【函数功能】        PayCfmDialog类构造函数 构造该页面
【参数】
                  QWidget* parent          输入
                  QWidget* parentWindow    输入
                  P_MSN mission            输入
                  QString confirmContent   输入
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
PayCfmDialog::PayCfmDialog(QWidget* parent , QWidget* parentWindow ,
                           P_MSN mission, QString confirmContent) :
    CfmDialog::CfmDialog(parent, parentWindow, confirmContent),
    mission(mission)
{
    connect(this, &PayCfmDialog::s_confirmed, this, &PayCfmDialog::SuccessNotice);
}


/*************************************************************************
【函数名称】        ~PayCfmDialog
【函数功能】        PayCfmDialog类析构函数
【参数】           void
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
PayCfmDialog::~PayCfmDialog()
{}


/*************************************************************************
【函数名称】        SuccessNotice
【函数功能】        支付成功提示
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void PayCfmDialog::SuccessNotice()
{
    QMessageBox* succeed = new QMessageBox(QMessageBox::Information, "Notice",
                                           "Payment succeed!\n ", QMessageBox::Ok, this);
    succeed->show();
    connect(succeed, &QMessageBox::accepted, this, &PayCfmDialog::ReturnDone);
}


/*************************************************************************
【函数名称】        ReturnDone
【函数功能】        返回上一页面
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void PayCfmDialog::ReturnDone()
{
    P_MNG mng(mission->GetMissionName());

    if (!mng.exist())
    {
        qDebug() << "Error! ManageMission not exist. \n\t from PayCfmDialog::returnDone()";
    }
    emit s_returnM2(mng, this);
}

