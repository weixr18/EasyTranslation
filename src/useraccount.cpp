/*************************************************************************
【文件名】                 useraccount.cpp
【功能模块和目的】          UserAccount类实现
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/


#include "useraccount.h"
#include "ui_useraccount.h"

/*************************************************************************
【函数名称】        UserAccount
【函数功能】        UserAccount类构造函数 构造该页面
【参数】
                  QWidget* parent               输入
                  P_USER user                   输入
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
UserAccount::UserAccount(QWidget* parent, P_USER user) :
    QMainWindow(parent),
    ui(new Ui::UserAccount),
    user(user)
{
    ui->setupUi(this);
    connect(ui->return_2, &QPushButton::clicked, this, &UserAccount::ReturnLast);
    TableInitialize();
    connect(ui->charge, &QPushButton::clicked, this, &UserAccount::GoCharge);
}


/*************************************************************************
【函数名称】        ~UserAccount
【函数功能】        UserAccount类析构函数
【参数】           void
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
UserAccount::~UserAccount()
{
    delete ui;
}


/*************************************************************************
【函数名称】        TableInitialize
【函数功能】        表格初始化
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void UserAccount::TableInitialize()
{
    int rowNum1 = 6;
    ui->basicInfo->setRowCount(rowNum1);
    ui->basicInfo->setColumnCount(4);
    ui->basicInfo->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->basicInfo->verticalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    ui->basicInfo->horizontalHeader()->setSectionResizeMode(1,
            QHeaderView::ResizeToContents);
    ui->basicInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QHeaderView* headerView = ui->basicInfo->verticalHeader();
    headerView->setHidden(true);

    QStringList header;
    header << "Item" << "Content" << "Modify" << "Save";
    ui->basicInfo->setHorizontalHeaderLabels(header);//id balance

    ui->basicInfo->setItem(0, 0, new QTableWidgetItem( "User Name") );
    ui->basicInfo->setItem(0, 1,
                           new QTableWidgetItem( QString::fromStdString(user->GetUserName() ) ) );
    ui->basicInfo->setItem(1, 0, new QTableWidgetItem( "Real Name") );
    ui->basicInfo->setItem(1, 1,
                           new QTableWidgetItem( QString::fromStdString(user->GetRealName() ) ) );
    ui->basicInfo->setItem(2, 0, new QTableWidgetItem( "Score") );
    ui->basicInfo->setItem(2, 1,
                           new QTableWidgetItem( QString::number(user->GetScore() ) ) );
    ui->basicInfo->setItem(3, 0, new QTableWidgetItem( "E-mail") );
    ui->basicInfo->setItem(3, 1,
                           new QTableWidgetItem( QString::fromStdString(user->GetEMail() ) ) );
    ui->basicInfo->setItem(4, 0, new QTableWidgetItem( "ID") );
    ui->basicInfo->setItem(4, 1,
                           new QTableWidgetItem( QString::fromStdString(user->GetUserInfo().m_ID) ) );
    ui->basicInfo->setItem(5, 0, new QTableWidgetItem( "Balance") );
    ui->basicInfo->setItem(5, 1,
                           new QTableWidgetItem( QString::number(user->GetBalance() ) ) );
}


/*************************************************************************
【函数名称】        GoCharge
【函数功能】        进入充值界面
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void UserAccount::GoCharge()
{
    ChargePage* chargePge = new ChargePage(this, user);
    connect(chargePge, &ChargePage::s_returnLast, this,
            &UserAccount::ChargePgeReturn);

    chargePge->show();
    this->hide();
}


/*************************************************************************
【函数名称】        ChargePgeReturn
【函数功能】        充值界面返回
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void UserAccount::ChargePgeReturn(ChargePage* nxtpge)
{
    TableInitialize();
    this->show();

    if (nxtpge != nullptr)
    {
        nxtpge->close();
    }
}


/*************************************************************************
【函数名称】        ReturnLast
【函数功能】        返回上一页面
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void UserAccount::ReturnLast()
{
    emit s_returnLast(this);
}
