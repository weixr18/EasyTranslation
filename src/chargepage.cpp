/*************************************************************************
【文件名】                 chargepage.cpp
【功能模块和目的】          ChargePage类实现
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/


#include "chargepage.h"
#include "ui_chargepage.h"
#include "chargecfmdialog.h"
#include <QDebug>


/*************************************************************************
【函数名称】       ChargePage
【函数功能】       ChargePage类构造函数 构造该页面
【参数】
                  QWidget* parent               输入
                  P_USER   user                 输入
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
ChargePage::ChargePage(QWidget* parent, P_USER user) :
    QMainWindow(parent),
    ui(new Ui::ChargePage),
    user(user)
{
    ui->setupUi(this);
    connect(ui->cancel, &QPushButton::clicked, this, &ChargePage::ReturnLast);
    connect(ui->confirm, &QPushButton::clicked, this, &ChargePage::ConfirmCharge);

}


/*************************************************************************
【函数名称】       ~ChargePage
【函数功能】       ChargePage类析构函数
【参数】           void
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
ChargePage::~ChargePage()
{
    delete ui;
}


/*************************************************************************
【函数名称】       ConfirmCharge
【函数功能】       充值确认
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void ChargePage::ConfirmCharge()
{
    if (ui->spinBox->value() == 0)
    {
        //弹提示框
    }
    else if (!user->PasswordMatch(ui->lineEdit->text().toStdString() ) )
    {
        //弹提示框
    }
    else
    {
        qDebug() << "Charge confirm";
        ChargeCfmDialog* cfm = new ChargeCfmDialog(this, this, user,
                QString("You are going to charge " + QString::number(ui->spinBox->value()) +
                        " yuan, are you sure?"));
        cfm->show();
        connect(cfm, &ChargeCfmDialog::s_returnU, this, &ChargePage::ChargeSucceed);
    }
}

/*************************************************************************
【函数名称】       ChargeSucceed
【函数功能】       充值成功
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void ChargePage::ChargeSucceed(P_USER user, CfmDialog* cfmPge)
{
    cfmPge->close();

    user->Charge(ui->spinBox->value());
    emit s_returnLast(this);
}

/*************************************************************************
【函数名称】       ReturnLast
【函数功能】       返回上一页面
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void ChargePage::ReturnLast()
{
    emit s_returnLast(this);
}
