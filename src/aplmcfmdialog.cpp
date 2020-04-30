/*************************************************************************
【文件名】                 aplmcfmdialog.cpp
【功能模块和目的】          AplMCfmDialog类实现
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/


#include "aplmcfmdialog.h"
#include <QMessageBox>
#include <QDebug>


/*************************************************************************
【函数名称】        AplMCfmDialog
【函数功能】        AplMCfmDialog类构造函数 构造该页面
【参数】
                  QWidget* parent               输入
                  QWidget* parentWindow         输入
                  P_MSN mission                 输入
                  QString confirmContent        输入
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
AplMCfmDialog::AplMCfmDialog(QWidget* parent, QWidget* parentWindow,
                             P_MSN mission, QString confirmContent,
                             P_USER user) :
    CfmDialog::CfmDialog(parent, parentWindow, confirmContent),
    mission(mission),
    user(user)
{
    connect(this, &AplMCfmDialog::s_confirmed, this, &AplMCfmDialog::QualityCheck);
}


/*************************************************************************
【函数名称】        ~AplMCfmDialog
【函数功能】        AplMCfmDialog类析构 析构该页面
【参数】           void
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
AplMCfmDialog::~AplMCfmDialog()
{
    qDebug() << "~AplMCfmDialog()";
}



/*************************************************************************
【函数名称】        QualityCheck
【函数功能】        申请者资质检查
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void AplMCfmDialog::QualityCheck()
{
    if (!Platform::userAbleToManage(user))
    {
        QMessageBox* warn = new QMessageBox(QMessageBox::Warning, "Notice",
                                        "Your score is not enough to apply for a manager.",
                                        QMessageBox::Yes, this);
        warn->show();
        result = false;
        connect(warn, &QMessageBox::accepted, this, &AplMCfmDialog::ReturnDone);
    }
    else
    {
        QMessageBox* succeed = new QMessageBox(QMessageBox::Information, "Notice",
            "Apply Succeed.\n You can view the application status on your home page.",
            QMessageBox::Ok, this);
        succeed->show();
        result = true;
        connect(succeed, &QMessageBox::accepted, this, &AplMCfmDialog::ReturnDone);
    }

}


/*************************************************************************
【函数名称】        ReturnDone
【函数功能】        发送返回上一页面信号
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void AplMCfmDialog::ReturnDone()
{
    emit s_returnM3(mission, this, result);
}

