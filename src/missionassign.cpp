/*************************************************************************
【文件名】                 missionassign.cpp
【功能模块和目的】          MissionAssign类实现
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/

#include "missionassign.h"
#include "ui_missionassign.h"
#include "submission.h"
#include <QPlainTextEdit>
#include <QMessageBox>
#include <QDebug>


/*************************************************************************
【函数名称】        MissionAssign
【函数功能】        MissionAssign类构造函数 构造该页面
【参数】
                  QWidget* parent          输入
                  P_MNG    mng             输入
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
MissionAssign::MissionAssign(QWidget* parent, P_MNG mngMission) :
    QMainWindow(parent),
    ui(new Ui::MissionAssign),
    mngMission(mngMission)
{
    if (!mngMission.exist())
    {
        qDebug() << "Error : MissionAssign::MissionAssign(\
            QWidget* parent, TranslateMission* trslMission) ";
    }
    else
    {
        ui->setupUi(this);
        ui->srcText->setPlainText(QString::fromStdString(mngMission->GetSrcText()));
        ui->srcText->setReadOnly(true);
        ui->reDo->setEnabled(false);
        TableInitialize();
        connect(ui->cutText, &QPushButton::clicked, this,
                &MissionAssign::OnCutClicked);      //剪切
        connect(ui->complete, &QPushButton::clicked, this,
                &MissionAssign::AssignComplete);         //完成
    }
}


/*************************************************************************
【函数名称】        ~MissionAssign
【函数功能】        MissionAssign类析构函数
【参数】           void
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
MissionAssign::~MissionAssign()
{
    delete ui;
}



/*************************************************************************
【函数名称】        TableInitialize
【函数功能】        表格初始化
【参数】           void
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void MissionAssign::TableInitialize()
{
    translators = mngMission->GetTranslators();
    ULL rowNum = translators.size();

    ui->translatorTable->setRowCount(static_cast<int>(rowNum));
    //userName, view info, assignText, paste
    ui->translatorTable->setColumnCount(4);
    ui->translatorTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->translatorTable->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Stretch);
    ui->translatorTable->horizontalHeader()->setSectionResizeMode(0,
            QHeaderView::ResizeToContents);
    ui->translatorTable->horizontalHeader()->setSectionResizeMode(1,
            QHeaderView::ResizeToContents);
    ui->translatorTable->horizontalHeader()->setSectionResizeMode(3,
            QHeaderView::ResizeToContents);
    ui->translatorTable->verticalHeader()->setSectionResizeMode(
        QHeaderView::Interactive);

    QStringList header;
    header << "User" << "Info" << "Assign Text" << "Paste";
    ui->translatorTable->setHorizontalHeaderLabels(header);
    pBG = new QButtonGroup(this);
    pBG->setExclusive(false);

    for (ULL i = 0; i < rowNum; i++)
    {
        P_USER temp(translators[i]);

        if (temp.exist())
        {
            ui->translatorTable->setItem(static_cast<int>(i), 0,
                new QTableWidgetItem(QString::fromStdString(temp->GetUserName() ) ) );

            QPushButton* info = new QPushButton;
            SetShowUserInfoButton(info,  translators[i]);
            ui->translatorTable->setCellWidget(static_cast<int>(i), 1, info);

            QPlainTextEdit* edit = new QPlainTextEdit;
            edit->setReadOnly(true);
            edits.push_back(edit);
            ui->translatorTable->setCellWidget(static_cast<int>(i), 2, edit);

            QPushButton* paste = new QPushButton("粘贴", this);
            pBG->addButton(paste, static_cast<int>(i));
            ui->translatorTable->setCellWidget(static_cast<int>(i), 3, paste);
            paste->setStyleSheet("QPushButton{background-color:white;}");
        }
    }

    connect(pBG, SIGNAL(buttonClicked(int)), this, SLOT(OnButtonClicked(int)));   //粘贴
}



/*************************************************************************
【函数名称】        SetShowUserInfoButton
【函数功能】        设置展示个人信息键
【参数】           void
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void MissionAssign::SetShowUserInfoButton(QPushButton* btn, P_USER p_user)
{
    btn->setText("View details.");
    btn->setStyleSheet("QPushButton{background-color:white;}");

    UserInfo* infoPage = new UserInfo(this, p_user);
    infoPage->setWindowTitle("个人信息");
    connect(btn, &QPushButton::clicked, infoPage, &UserInfo::show);
    connect(infoPage, &UserInfo::s_return, this, &MissionAssign::ViewUserReturn);
}



/*************************************************************************
【函数名称】        OnCutClicked
【函数功能】        剪切操作响应
【参数】           void
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void MissionAssign::OnCutClicked()
{
    if (pasted)
    {
        ClipBoard = ui->srcText->textCursor().selectedText();
        ui->srcText->textCursor().removeSelectedText();
        pasted = false;
    }
}


/*************************************************************************
【函数名称】        OnButtonClicked
【函数功能】        粘贴操作响应
【参数】           void
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void MissionAssign::OnButtonClicked(int id)
{
    qDebug() << "33333333333";
    ULL id1 = static_cast<ULL>(id);

    if (!pasted)
    {
        if (id1 >= translators.size())
        {
            qDebug() << "Error1 :  MissionAssign::onButtonClicked(int id)";
        }
        else if (edits[id1] == nullptr)
        {
            qDebug() << "Error2 :  MissionAssign::onButtonClicked(int id)";
        }
        else
        {
            edits[id1]->setPlainText(ClipBoard);
            pasted = true;
        }
    }
}


/*************************************************************************
【函数名称】        AssignComplete
【函数功能】        任务分配完成
【参数】           void
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void MissionAssign::AssignComplete()
{
    if (!TextFilled())                                   //判断是否分配完成
    {
        QMessageBox* warn = new QMessageBox(QMessageBox::Warning, "Notice",
            "Assingment not completed yet.",
            QMessageBox::Yes, this);
        warn->show();
    }
    else
    {
        ASSIGN_MIS v1;

        //信息处理
        for (ULL i = 0; i != translators.size(); i++)
        {
            std::pair<std::string, std::string> p(translators[i],
                                                  edits[i]->toPlainText().toStdString());
            v1.push_back(p);
        }

        P_USER manager(mngMission->GetManager());
        P_MNG mng = mngMission;
        Platform::m_assign_mission(manager, mng, v1);

        //页面返回
        QMessageBox* success = new QMessageBox(QMessageBox::Information,
                                               "Notice", "Mission Assign Succeed!!\nPress 'OK' and return HomePage.",
                                               QMessageBox::Ok, this);
        success->show();
        connect(success, &QMessageBox::accepted, this, &MissionAssign::ReturnLast);
    }
}


/*************************************************************************
【函数名称】        TextFilled
【函数功能】        判断分配框是否被填满
【参数】           void
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
bool MissionAssign::TextFilled()
{
    if (!ui->srcText->document()->isEmpty())
    {
        return false;
    }

    for (ULL i = 0; i != edits.size(); i++)
    {
        if (edits[i]->document()->isEmpty())
        {
            return false;
        }
    }

    return true;
}


/*************************************************************************
【函数名称】        ViewUserReturn
【函数功能】        个人信息页返回
【参数】           void
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void MissionAssign::ViewUserReturn(UserInfo* userinfo)
{
    userinfo->close();
}


/*************************************************************************
【函数名称】        ReturnLast
【函数功能】        返回上一页面
【参数】           void
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void MissionAssign::ReturnLast()
{
    emit s_asgSucceed(this);
}

