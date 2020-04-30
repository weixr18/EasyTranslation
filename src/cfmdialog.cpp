/*************************************************************************
【文件名】                 cfmdialog.cpp
【功能模块和目的】          CfmDialog类实现
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/

#include "cfmdialog.h"
#include "ui_cfmdialog.h"
#include <QDebug>


/*************************************************************************
【函数名称】        CfmDialog
【函数功能】        CfmDialog类构造函数 构造该页面
【参数】
                  QWidget* parent               输入
                  QWidget* parentWindow         输入
                  QString confirmContent        输入
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
CfmDialog::CfmDialog(QWidget* parent, QWidget* parentWindow,
                     QString confirmContent) :
    QDialog(parent),
    ui(new Ui::CfmDialog),
    confirmContent(confirmContent),
    parentWindow(parentWindow)
{
    ui->setupUi(this);
    ui->textEdit->setPlainText(confirmContent);
    QPalette pa = ui->textEdit->palette();
    pa.setColor(QPalette::Base, QColor(245, 245, 245));
    ui->textEdit->setPalette(pa);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &CfmDialog::Confirm);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this,
        &CfmDialog::CloseThis);
}


/*************************************************************************
【函数名称】        ~CfmDialog
【函数功能】        CfmDialog类析构函数
【参数】           void
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
CfmDialog::~CfmDialog()
{
    delete ui;
}


/*************************************************************************
【函数名称】        Confirm
【函数功能】        确认响应
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void CfmDialog::Confirm()
{
    emit s_confirmed(this);
}

/*************************************************************************
【函数名称】        CloseThis
【函数功能】        关闭本页面
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void CfmDialog::CloseThis()
{
    parentWindow->show();
    this->close();
}



