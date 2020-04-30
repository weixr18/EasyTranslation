/*************************************************************************
【文件名】                 apltcfmdialog.cpp
【功能模块和目的】          AplTCfmDialog类实现
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/


#include "apltcfmdialog.h"
#include <QMessageBox>
#include <QDebug>


/*************************************************************************
【函数名称】        AplTCfmDialog
【函数功能】        AplTCfmDialog类构造函数 构造该页面
【参数】
                  QWidget* parent               输入
                  QWidget* parentWindow         输入
                  P_MNG mng                     输入
                  QString confirmContent        输入
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
AplTCfmDialog::AplTCfmDialog(QWidget* parent, QWidget* parentWindow, P_MNG mng,
                             QString confirmContent ) :
    CfmDialog::CfmDialog(parent, parentWindow, confirmContent),
    mng(mng)
{
    connect(this, &AplTCfmDialog::s_confirmed, this, &AplTCfmDialog::SuccessNotice);
}


/*************************************************************************
【函数名称】        ~AplTCfmDialog
【函数功能】        AplTCfmDialog类析构 析构该页面
【参数】           void
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
AplTCfmDialog::~AplTCfmDialog()
{
    qDebug() << "~AplTCfmDialog()";
}


/*************************************************************************
【函数名称】        SuccessNotice
【函数功能】        提示申请负责人成功
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void AplTCfmDialog::SuccessNotice()
{
    //此处的提示框可以更个性化一些
    QMessageBox* succeed = new QMessageBox(QMessageBox::Information, "Notice",
        "Apply Succeed.\n You can view the application status on your home page.",
        QMessageBox::Ok, this);
    succeed->show();
    connect(succeed, &QMessageBox::accepted, this, &AplTCfmDialog::ReturnDone);
}

/*************************************************************************
【函数名称】        ReturnDone
【函数功能】        发送返回上一页面信号
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void AplTCfmDialog::ReturnDone()
{
    emit s_returnM2(mng, this);
}


