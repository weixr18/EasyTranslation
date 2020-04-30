/*************************************************************************
【文件名】                 regist_2.cpp
【功能模块和目的】          Regist_2类实现
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/


#include "regist_2.h"
#include "ui_regist_2.h"
#include <QMessageBox>
#include <QDebug>

/*************************************************************************
【函数名称】        Regist_2
【函数功能】        Regist_2类构造函数 构造该页面
【参数】
                  QWidget* parent          输入
                  std::string name         输入
                  std::string id           输入
                  std::string email        输入
                  std::string realName     输入
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
Regist_2::Regist_2(QWidget* parent, std::string name ,
                   std::string id , std::string email , std::string realName) :
    QMainWindow(parent),
    ui(new Ui::Regist_2),
    tempName(name),
    tempID(id),
    tempRealName(realName),
    tempEmail(email)
{
    ui->setupUi(this);
    connect(ui->cancel, &QPushButton::clicked, this,
            &Regist_2::RegCancel);    //取消注册
}


/*************************************************************************
【函数名称】        Regist_2
【函数功能】        Regist_2类析构函数
【参数】           void
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
Regist_2::~Regist_2()
{
    delete ui;
}

/*************************************************************************
【函数名称】        RegCancel
【函数功能】        注册取消
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void Regist_2::RegCancel()
{
    emit s_regCancel();
    this->close();
}

/*************************************************************************
【函数名称】        RegSucceed
【函数功能】        注册成功
【参数】
                  P_USER tempUser   输入
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void Regist_2::RegSucceed(P_USER tempUser)
{
    emit s_regSucceed(tempUser);
    this->close();
}


/*************************************************************************
【函数名称】        on_continue_2_clicked
【函数功能】        继续注册
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void Regist_2::on_continue_2_clicked()
{
    if (ui->password->text().isEmpty() ||
        ui->passwordRepeat->text().isEmpty())
    {
        QMessageBox* warn = new QMessageBox(QMessageBox::Warning, "Warning",
            "A blank is empty.", QMessageBox::Ok, this);
        warn->show();
    }
    else if ((ui->password->text() != ui->passwordRepeat->text()))
    {
        QMessageBox* warn = new QMessageBox(QMessageBox::Warning, "Warning",
            tr("两次输入密码必须一致！"), QMessageBox::Ok, this);
        warn->show();
    }
    else if (ui->password->text().contains(QRegExp("[()\"#|;]")))
    {
        QMessageBox* warn = new QMessageBox(QMessageBox::Warning, "Warning",
            "Password cannot contain special symbols : \n\
            ()\"#|;", QMessageBox::Ok, this);
        warn->show();
    }
    else
    {
        tempPW = ui->password->text().toStdString();

        nxtpge = new Regist_3(this, tempName, tempID, tempEmail, tempRealName, tempPW);
        nxtpge->setWindowTitle("众包翻译平台-注册");
        connect(nxtpge, &Regist_3::s_regSucceed, this,
                &Regist_2::RegSucceed);    //监听成功信号
        nxtpge->show();
        this->hide();
    }
}
