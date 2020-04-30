/*************************************************************************
【文件名】                 payformission.cpp
【功能模块和目的】          PayForMission类实现
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/


#include "payformission.h"
#include "ui_payformission.h"
#include <QDebug>
#include <QMessageBox>


/*************************************************************************
【函数名称】        PayForMission
【函数功能】        PayForMission类构造函数 构造该页面
【参数】
                  QWidget* parent          输入
                  P_MSN mission            输入
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
PayForMission::PayForMission(QWidget* parent, P_MSN mission) :
    QMainWindow(parent),
    ui(new Ui::PayForMission),
    mission(mission)
{
    ui->setupUi(this);
    connect(ui->cancel, &QPushButton::clicked, this, &PayForMission::Canceled);

    ui->missionName->setText(QString::fromStdString(mission->GetMissionName() ) );
    ui->manager->setText(QString::fromStdString(mission->GetReleaser() ) );
    ui->awardAmount->setText(QString::number(mission->GetAwardAmount() ) );

    P_MNG mng = mission->GetMissionName();

    if (mng.exist())
    {
        ui->trslNum->setText(QString::number(mng->GetTranslators().size() ) );
        ui->missionName->setReadOnly(true);
        ui->manager->setReadOnly(true);
        ui->awardAmount->setReadOnly(true);
        ui->trslNum->setReadOnly(true);

        int rownum4 = 1;
        ui->missionResult->setRowCount(rownum4);
        ui->missionResult->setColumnCount(2);
        ui->missionResult->horizontalHeader()->setSectionResizeMode(
            QHeaderView::Stretch);
        ui->missionResult->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->missionResult->setEditTriggers(QAbstractItemView::NoEditTriggers);

        QStringList header;
        header << "Source Text" << "Translation Text";
        ui->missionResult->setHorizontalHeaderLabels(header);
        QHeaderView* headerView = ui->missionResult->verticalHeader();
        headerView->setHidden(true);

        ui->missionResult->setItem(0, 0,
                                   new QTableWidgetItem(QString::fromStdString(mng->GetSrcText() ) ) );
        ui->missionResult->setItem(0, 1,
                                   new QTableWidgetItem(QString::fromStdString(mng->GetLastTranslation() ) ) );

        connect(ui->confirm, &QPushButton::clicked, this, &PayForMission::Confirm);
    }
}


/*************************************************************************
【函数名称】        ~PayForMission
【函数功能】        PayForMission类析构函数
【参数】           void
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
PayForMission::~PayForMission()
{
    delete ui;
}


/*************************************************************************
【函数名称】        Confirm
【函数功能】        确认支付
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void PayForMission::Confirm()
{
    int pay = mission->GetAwardAmount();
    QMessageBox* warn = new QMessageBox(QMessageBox::Warning, "Warning",
                                        "Your account balance is not enough. Please go to charge first.",
                                        QMessageBox::Yes, this);
    PayCfmDialog* cfm = new PayCfmDialog(this, this, mission,
                                         "You are going to pay " + QString::number(pay)
                                         + " yuan for this mission. Continue?");
    P_USER user = mission->GetReleaser();

    if (user->GetBalance() < pay)
    {
        warn->show();
    }
    else
    {
        cfm->show();
        connect(cfm, &PayCfmDialog::s_returnM2, this, &PayForMission::Succeed);
    }
}

/*************************************************************************
【函数名称】        Succeed
【函数功能】        支付成功响应
【参数】
                  P_MNG mng                    输入
                  CfmDialog* cfmPge            输入
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void PayForMission::Succeed(P_MNG mng, CfmDialog* cfmPge)
{
    if (cfmPge != nullptr)
    { cfmPge->close(); }

    P_USER user = mng->GetReleaser();

    if (Platform::r_pay_award(user, mng) )
    { qDebug() << "pay Succeed! Mission accomplished!!"; }

    emit s_succeed(this);
}

/*************************************************************************
【函数名称】        Canceled
【函数功能】        支付取消响应
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void PayForMission::Canceled()
{
    emit s_canceled(this);
}
