/*************************************************************************
【文件名】                 regist.cpp
【功能模块和目的】          Regist类实现
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/


#include "regist.h"
#include "ui_regist.h"
#include <QValidator>
#include <QDebug>

/*************************************************************************
【函数名称】        Regist
【函数功能】        Regist类构造函数 构造该页面
【参数】
                  QWidget* parent          输入
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
Regist::Regist(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::Regist)
{
    ui->setupUi(this);
    connect(ui->continue_2, &QPushButton::clicked, this,
            &Regist::ConTinueReg);        //“继续”
    connect(ui->cancel, &QPushButton::clicked, this,
            &Regist::on_cancel_clicked);        //“取消”
}


/*************************************************************************
【函数名称】        ~Regist
【函数功能】        Regist类析构函数
【参数】           void
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
Regist::~Regist()
{
    delete ui;
}


/*************************************************************************
【函数名称】        ConTinueReg
【函数功能】        注册继续
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void Regist::ConTinueReg()
{
    if (ui->e_username->text().isEmpty() ||
        ui->e_idNum->text().isEmpty() ||
        ui->e_realName->text().isEmpty() ||
        ui->e_email->text().isEmpty())
    {
        QMessageBox* warn = new QMessageBox(QMessageBox::Warning, "Warning",
            "Personal infomation must be completely filled.", QMessageBox::Ok, this);
        warn->show();
    }
    else if (Datum::UserNameExist(ui->e_username->text().toStdString()))
    {
        QMessageBox* warn = new QMessageBox(QMessageBox::Warning, "Warning",
            "This username already exists. Please try another one.", QMessageBox::Ok, this);
        warn->show();
    }
    else if (!FormatCheckPass())
    {
        //Do nothing here.
    }
    else
    {
        tempName = ui->e_username->text().toStdString();
        tempID = ui->e_idNum->text().toStdString();
        tempRealName = ui->e_realName->text().toStdString();
        tempEmail = ui->e_email->text().toStdString();

        nxtpge = new Regist_2(this, tempName, tempID, tempEmail, tempRealName);
        nxtpge->setWindowTitle("众包翻译平台-注册");
        connect(nxtpge, &Regist_2::s_regCancel, this,
                &Regist::on_cancel_clicked);         //监听下一页面取消
        connect(nxtpge, &Regist_2::s_regSucceed, this,
                &Regist::RegSucceed);                //监听下一页面成功
        this->hide();
        nxtpge->show();
    }
}


/*************************************************************************
【函数名称】        RegSucceed
【函数功能】        注册成功处理
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void Regist::RegSucceed(P_USER user)
{
    emit  s_regSucceed(user);
}


bool Regist::FormatCheckPass()
{
    if (ui->e_username->text().contains(QRegExp("[()\"#|;]")))
    {
        QMessageBox* warn = new QMessageBox(QMessageBox::Warning, "Warning",
            "Username cannot contain special symbols : \n\
            ()\"#|;", QMessageBox::Ok, this);
        warn->show();
        return false;
    }
    else if(ui->e_realName->text().contains(QRegExp("[()\"#|;]")))
    {
        QMessageBox* warn = new QMessageBox(QMessageBox::Warning, "Warning",
            "Real name cannot contain special symbols : \n\
            ()\"#|;", QMessageBox::Ok, this);
        warn->show();
        return false;
    }
    else if(ui->e_email->text().contains(QRegExp("[()\"#|;]")))
    {
        QMessageBox* warn = new QMessageBox(QMessageBox::Warning, "Warning",
            "Email address cannot contain special symbols : \n\
            ()\"#|;", QMessageBox::Ok, this);
        warn->show();
        return false;
    }
    else
    {
        QString qrx = "^[1-9][0-9]{5}(18|19|([23][0-9]))[0-9]{2}((0[1-9])|(10|11|12))"
                      "(([0-2][1-9])|10|20|30|31)[0-9]{3}[0-9Xx]$";
        QRegExp rx(qrx);
        bool match1 = rx.exactMatch(ui->e_idNum->text());
        if (!match1)
        {
            QMessageBox* warn = new QMessageBox(QMessageBox::Warning, "Warning",
            "ID format wrong! Please input the real ID num.", QMessageBox::Ok, this);
            warn->show();
            return false;
        }

        QString qrx2 = "^[a-zA-Z0-9_-]+@[a-zA-Z0-9_-]+(\\.[a-zA-Z0-9_-]+)+$";
        QRegExp rx2(qrx2);
        bool match2 = rx2.exactMatch(ui->e_email->text());
        if (!match2)
        {
            QMessageBox* warn = new QMessageBox(QMessageBox::Warning, "Warning",
            "Email format wrong! Please input the right email address.", QMessageBox::Ok, this);
            warn->show();
            return false;
        }
    }
    return true;
}

/*************************************************************************
【函数名称】        on_cancel_clicked
【函数功能】        注册取消响应
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void Regist::on_cancel_clicked()
{
    emit s_regCancel();
}
