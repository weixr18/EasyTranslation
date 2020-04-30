/*************************************************************************
【文件名】                 choosertranslator.cpp
【功能模块和目的】          ChooseTranslator类实现
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/


#include "choosetranslator.h"
#include "ui_choosetranslator.h"
#include "missionassign.h"
#include <QCheckBox>
#include <QButtonGroup>
#include <QMessageBox>
#include <QDebug>

/*************************************************************************
【函数名称】       ChooseTranslator
【函数功能】       ChooseTranslator类构造函数 构造该页面
【参数】
                  QWidget*  parent               输入
                  P_MNG     mngMission           输入
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
ChooseTranslator::ChooseTranslator(QWidget* parent, P_MNG mngMission) :
    QMainWindow(parent),
    ui(new Ui::ChooseTranslator),
    mngMission(mngMission)
{
    ui->setupUi(this);
    connect(ui->Cancel, &QPushButton::clicked, this,
            &ChooseTranslator::ChsCancel);           //“取消”
    connect(ui->Comfirm, &QPushButton::clicked, this,
            &ChooseTranslator::ChsComplete);        //继续
    TableInitialize();
}


/*************************************************************************
【函数名称】       ~ChooseTranslator
【函数功能】       ChooseTranslator类析构函数
【参数】           void
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
ChooseTranslator::~ChooseTranslator()
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
void ChooseTranslator::TableInitialize()
{
    ULL rowNum = mngMission->GetTrslCandidates().size();
    ui->translatorCandidates->setRowCount(static_cast<int>(rowNum));
    ui->translatorCandidates->setColumnCount(
        4);      //userName, score, viewInfo, confirm
    ui->translatorCandidates->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Stretch);
    ui->translatorCandidates->verticalHeader()->setSectionResizeMode(
        QHeaderView::Interactive);
    ui->translatorCandidates->setEditTriggers(QAbstractItemView::NoEditTriggers);


    QStringList header;
    header << "User Name" << "Score" << "View Info" << "Confirm";
    ui->translatorCandidates->setHorizontalHeaderLabels(header);

    pBG = new QButtonGroup(this);
    pBG->setExclusive(false);

    for (ULL i = 0; i < rowNum; i++)
    {
        P_USER can(mngMission->GetTrslCandidates()[i]);

        if (can.exist())
        {
            ui->translatorCandidates->setItem(static_cast<int>(i), 0,
                new QTableWidgetItem(QString::fromStdString(can->GetUserName() ) ) );
            ui->translatorCandidates->setItem(static_cast<int>(i), 1,
                new QTableWidgetItem(QString::number(can->GetScore() ) ) );

            QPushButton* info = new QPushButton;
            SetShowUserInfoButton(info,  can);
            ui->translatorCandidates->setCellWidget(static_cast<int>(i), 2, info);

            QCheckBox* chk = new QCheckBox("选择", this);
            ui->translatorCandidates->setCellWidget(static_cast<int>(i), 3, chk);
            pBG->addButton(chk, static_cast<int>(i));
        }
    }

    connect(pBG, SIGNAL(buttonClicked(QAbstractButton*)), this,
            SLOT(OnButtonClicked(QAbstractButton*)));
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
void ChooseTranslator::SetShowUserInfoButton(QPushButton* btn, P_USER p_user)
{
    btn->setText("View details.");
    btn->setStyleSheet("QPushButton{background-color:white;}");

    UserInfo* infoPage = new UserInfo(this, p_user);
    infoPage->setWindowTitle("个人信息");
    connect(btn, &QPushButton::clicked, infoPage, &UserInfo::show);
    connect(infoPage, &UserInfo::s_return, this, &ChooseTranslator::ViewUserReturn);
}


/*************************************************************************
【函数名称】       OnButtonClicked
【函数功能】       设置用户信息页按钮
【参数】           QAbstractButton*     输入（无作用）
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void ChooseTranslator::OnButtonClicked(QAbstractButton*)
{
    tmpTranslators.clear();

    for (ULL i = 0; i != mngMission->GetTrslCandidates().size(); i++)
    {
        if (pBG->button(static_cast<int>(i))->isChecked())
        {
            tmpTranslators.push_back(mngMission->GetTrslCandidates()[i]);
        }
    }
}

/*************************************************************************
【函数名称】       ChsComplete
【函数功能】       选择完成
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void ChooseTranslator::ChsComplete()
{
    if (tmpTranslators.size() == 0)
    {
        QMessageBox* warn = new QMessageBox(QMessageBox::Warning, "Notice",
            "You have't choose any user yet.",
            QMessageBox::Yes, this);
        warn->show();
    }
    else
    {
        //处理信息
        std::vector<P_USER> v1;

        for (auto name : tmpTranslators)
        {
            P_USER u = name;
            v1.push_back(u);
        }

        Platform::m_choose_tranlator(mngMission->GetManager(), mngMission, v1);

        //进入分配任务页
        MissionAssign* nxtpge = new MissionAssign(this, mngMission);
        nxtpge->show();
        this->hide();
        connect(nxtpge, &MissionAssign::s_asgSucceed, this,
                &ChooseTranslator::ReturnLast);     //分配任务返回
    }
}


/*************************************************************************
【函数名称】       ViewUserReturn
【函数功能】       用户信息页返回
【参数】           UserInfo*  userinfo     输入
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void ChooseTranslator::ViewUserReturn(UserInfo* userinfo)
{
    userinfo->close();
}


/*************************************************************************
【函数名称】       ReturnLast
【函数功能】       返回上一页面
【参数】
                  MissionAssign*  nxtpge  输入
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void ChooseTranslator::ReturnLast(MissionAssign* nxtpge)
{
    this->show();

    if (nxtpge != nullptr)
    {
        nxtpge->close();
    }

    emit s_chsSucceed(this);
}


/*************************************************************************
【函数名称】       ChsCancel
【函数功能】       选择取消
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void ChooseTranslator::ChsCancel()
{
    emit s_chsCancel(this);
}

