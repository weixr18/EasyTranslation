/*************************************************************************
【文件名】                 lastsubmittal.cpp
【功能模块和目的】          LastSubmittal类实现
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/


#include "lastsubmittal.h"
#include "ui_lastsubmittal.h"
#include <QDebug>


/*************************************************************************
【函数名称】       LastSubmittal
【函数功能】       LastSubmittal类构造函数 构造该页面
【参数】
                  QWidget* parent          输入
                  P_MNG    mng             输入
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
LastSubmittal::LastSubmittal(QWidget* parent, P_MNG mng) :
    QMainWindow(parent),
    ui(new Ui::LastSubmittal),
    mng(mng)
{
    if (!mng.exist())
    {
        qDebug() << "Error 1 : nullptr \n\t \
            LastSubmittal::LastSubmittal(QWidget *parent, P_MNG mng)  ";
    }
    else
    {
        ui->setupUi(this);
        TableInitialize();
        ui->reDo->setEnabled(false);

        connect(ui->Paste, &QPushButton::clicked, this,
                &LastSubmittal::OnPasteClicked);           //粘贴
        connect(ui->complete, &QPushButton::clicked, this,
                &LastSubmittal::CfmLastSubmit);         //完成
    }

}

/*************************************************************************
【函数名称】       ~LastSubmittal
【函数功能】       LastSubmittal类析构函数
【参数】           void
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
LastSubmittal::~LastSubmittal()
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
void LastSubmittal::TableInitialize()
{
    submissions = mng->GetSubMissions();
    ULL rowNum = submissions.size();

    ui->translatorTable->setRowCount(static_cast<int>(rowNum));
    ui->translatorTable->setColumnCount(
        4);      //userName, srcText, translation, cut
    ui->translatorTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->translatorTable->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Stretch);
    ui->translatorTable->horizontalHeader()->setSectionResizeMode(0,
            QHeaderView::ResizeToContents);
    ui->translatorTable->horizontalHeader()->setSectionResizeMode(1,
            QHeaderView::ResizeToContents);
    ui->translatorTable->horizontalHeader()->setSectionResizeMode(2,
            QHeaderView::ResizeToContents);
    ui->translatorTable->horizontalHeader()->setSectionResizeMode(3,
            QHeaderView::ResizeToContents);
    ui->translatorTable->verticalHeader()->setSectionResizeMode(
        QHeaderView::Interactive);

    QStringList header;
    header << "User" << "SrcText" << "Translation" << "Cut";
    ui->translatorTable->setHorizontalHeaderLabels(header);
    pBG = new QButtonGroup(this);
    pBG->setExclusive(false);

    for (ULL i = 0; i < rowNum; i++)
    {
        P_SUB p_sub = submissions[i];
        ui->translatorTable->setItem(static_cast<int>(i), 0,
                                     new QTableWidgetItem(QString::fromStdString(p_sub->GetTranslator() ) ) );
        ui->translatorTable->setItem(static_cast<int>(i), 1,
                                     new QTableWidgetItem(QString::fromStdString(p_sub->GetSrcSubText() ) ) );

        QPlainTextEdit* edit = new QPlainTextEdit;
        edit->setReadOnly(true);
        edits.push_back(edit);
        edit->setPlainText(QString::fromStdString(p_sub->GetTranslation() ) );
        ui->translatorTable->setCellWidget(static_cast<int>(i), 2, edit);

        QPushButton* cut = new QPushButton("剪切", this);
        pBG->addButton(cut, static_cast<int>(i));
        ui->translatorTable->setCellWidget(static_cast<int>(i), 3, cut);
        cut->setStyleSheet("QPushButton{background-color:white;}");
    }

    connect(pBG, SIGNAL(buttonClicked(int)), this,
            SLOT(OnCutClicked(int)));                          //剪切
}

/*************************************************************************
【函数名称】       OnCutClicked
【函数功能】       剪切操作响应
【参数】
                  int id     输入
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void LastSubmittal::OnCutClicked(int id)
{
    if (pasted)
    {
        if (id >= static_cast<int>(submissions.size()))
        {
            qDebug() << "Error1 :  MissionAssign::onButtonClicked(int id)";
        }
        else if (edits[static_cast<ULL>(id)] == nullptr)
        {
            qDebug() << "Error2 :  MissionAssign::onButtonClicked(int id)";
        }
        else
        {
            ClipBoard = edits[static_cast<ULL>(id)]->document()->toPlainText();
            edits[static_cast<ULL>(id)]->clear();
            pasted = false;
        }
    }
}


/*************************************************************************
【函数名称】       OnPasteClicked
【函数功能】       粘贴操作响应
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void LastSubmittal::OnPasteClicked()
{
    if (!pasted)
    {
        ui->finalTranslation->insertPlainText(ClipBoard);
        pasted = true;
    }
}


/*************************************************************************
【函数名称】       CfmLastSubmit
【函数功能】       最终提交确认
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void LastSubmittal::CfmLastSubmit()
{
    if (TextFilled())
    {
        CfmDialog* confirm = new CfmDialog(this, this,
                                           "Are you sure to submit the Translation?  \n\
            Your operation cannot be canceled.");
        confirm->show();
        connect(confirm, &CfmDialog::s_confirmed, this, &LastSubmittal::SubmitSucceed);
    }
}


/*************************************************************************
【函数名称】       TextFilled
【函数功能】       判断是否合并了所有译者提交的译文
【参数】           void
【返回值】         bool 指示是否合并了所有译者提交的译文
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
bool LastSubmittal::TextFilled()
{
    if (ui->finalTranslation->document()->isEmpty())
    {
        qDebug() << "ui->finalTranslation->document()->isEmpty()";
        return false;
    }

    for (ULL i = 0; i != edits.size(); i++)
    {
        if (!edits[i]->document()->isEmpty())
        { return false; }
    }

    return true;
}


/*************************************************************************
【函数名称】       SubmitSucceed
【函数功能】       提交成功响应
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void LastSubmittal::SubmitSucceed(CfmDialog* cfmpge)
{
    cfmpge->close();

    std::string lst = ui->finalTranslation->document()->toPlainText().toStdString();
    Platform::m_last_submittal(this->mng->GetManager(), mng, lst);
    emit s_returnLast(this);
}


