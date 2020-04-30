/*************************************************************************
【文件名】                 choosemanager.cpp
【功能模块和目的】          ChooseManager类实现
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/


#include "choosemanager.h"
#include "ui_choosemanager.h"
#include <QDebug>


/*************************************************************************
【函数名称】       ChooseManager
【函数功能】       ChooseManager类构造函数 构造该页面
【参数】
                  QWidget* parent               输入
                  P_MSN    mission              输入
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
ChooseManager::ChooseManager(QWidget* parent, P_MSN mission) :
    QMainWindow(parent),
    ui(new Ui::ChooseManager),
    mission(mission)
{
    ui->setupUi(this);
    ui->Comfirm->setVisible(false);
    connect(ui->Cancel, &QPushButton::clicked, this,
            &ChooseManager::ChsCancel);        //“取消”
    TableInitialize();
}


/*************************************************************************
【函数名称】       ~ChooseManager
【函数功能】       ChooseManager类析构函数
【参数】           void
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
ChooseManager::~ChooseManager()
{
    delete ui;
}


/*************************************************************************
【函数名称】       TableInitialize
【函数功能】       表格初始化
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void ChooseManager::TableInitialize()
{
    ULL rowNum = (mission->GetMngCandidates().size());
    ui->managerCandidates->setRowCount(static_cast<int>(rowNum));
    ui->managerCandidates->setColumnCount(
        4);      //userName, score, viewInfo, confirm
    ui->managerCandidates->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Stretch);
    ui->managerCandidates->verticalHeader()->setSectionResizeMode(
        QHeaderView::Interactive);
    ui->managerCandidates->horizontalHeader()->setSectionResizeMode(3,
            QHeaderView::ResizeToContents);
    ui->managerCandidates->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QStringList header;
    header << "User Name" << "Score" << "View Info" << "Confirm";
    ui->managerCandidates->setHorizontalHeaderLabels(header);

    for (ULL i = 0; i < rowNum; i++)
    {
        P_USER u(mission->GetMngCandidates()[i]);
        ui->managerCandidates->setItem(static_cast<int>(i), 0,
                                       new QTableWidgetItem(QString::fromStdString(u->GetUserName() ) ) );
        ui->managerCandidates->setItem(static_cast<int>(i), 1,
                                       new QTableWidgetItem(QString::number(u->GetScore() ) ) );

        QPushButton* info = new QPushButton;
        SetShowUserInfoButton(info,  mission->GetMngCandidates()[i]);
        ui->managerCandidates->setCellWidget(static_cast<int>(i), 2, info);

        QPushButton* chs = new QPushButton;
        SetChooseMButton(chs,  mission->GetMngCandidates()[i]);
        ui->managerCandidates->setCellWidget(static_cast<int>(i), 3, chs);
    }
}


/*************************************************************************
【函数名称】       SetChooseMButton
【函数功能】       设置选择键
【参数】           QPushButton*  btn    输入
                  P_USER        user   输入
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void ChooseManager::SetChooseMButton(QPushButton* btn, P_USER user)
{
    btn->setText("Choose him/her.");
    btn->setStyleSheet("QPushButton{background-color:white;}");

    ChsMCfmDialog* confirm = new ChsMCfmDialog(this, this, user,
            "Are you sure to choose this user as the manager?\n Your operation cannot be canceled.");
    connect(btn, &QPushButton::clicked, confirm, &CfmDialog::show);
    connect(confirm, &ChsMCfmDialog::s_returnU, this,
            &ChooseManager::ChooseMSucceed);
}


/*************************************************************************
【函数名称】       ChooseMSucceed
【函数功能】       选择成功
【参数】           P_USER        user     输入
                  CfmDialog*    cfmPge   输入
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void ChooseManager::ChooseMSucceed(P_USER applier, CfmDialog* cfmPge)
{
    cfmPge->close();
    qDebug()<<"ChooseMSucceed!!";
    P_MNG mng("");
    P_USER releaser(mission->GetReleaser());
    if(!Platform::r_choose_manager(releaser, mission, applier, mng))
    {
        qDebug()<<"Unknown error when choosing M.";
    }
    emit s_chsSucceed(this);
}


/*************************************************************************
【函数名称】       SetShowUserInfoButton
【函数功能】       设置用户信息页按钮
【参数】           QPushButton*  btn    输入
                  P_USER        user   输入
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void ChooseManager::SetShowUserInfoButton(QPushButton* btn, P_USER user)
{
    btn->setText("View details.");
    btn->setStyleSheet("QPushButton{background-color:white;}");

    UserInfo* infoPage = new UserInfo(this, user);
    infoPage->setWindowTitle("个人信息");
    connect(btn, &QPushButton::clicked, infoPage, &UserInfo::show);
    connect(infoPage, &UserInfo::s_return, this, &ChooseManager::ViewUserReturn);

}


/*************************************************************************
【函数名称】       ViewUserReturn
【函数功能】       用户信息页返回
【参数】           UserInfo*  userinfo     输入
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void  ChooseManager::ViewUserReturn(UserInfo* userinfo)
{
    userinfo->close();
}


/*************************************************************************
【函数名称】       ChsCancel
【函数功能】       选择取消
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void ChooseManager::ChsCancel()
{
    emit s_chsCancel(this);
}

