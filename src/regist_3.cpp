/*************************************************************************
【文件名】                 regist_3.cpp
【功能模块和目的】          Regist_3类实现
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/


#include "regist_3.h"
#include "ui_regist_3.h"
#include <QString>
#include <QMessageBox>
#include <QDebug>


/*************************************************************************
【函数名称】        Regist_3
【函数功能】        Regist_3类构造函数 构造该页面
【参数】
                  QWidget* parent          输入
                  std::string name         输入
                  std::string id           输入
                  std::string email        输入
                  std::string realName     输入
                  std::string password     输入
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
Regist_3::Regist_3(QWidget* parent , std::string name ,
                   std::string id , std::string email ,
                   std::string realName , std::string password) :
    QMainWindow(parent),
    ui(new Ui::Regist_3),
    tempName(name),
    tempID(id),
    tempRealName(realName),
    tempEmail(email),
    tempPW(password)
{
    ui->setupUi(this);
    connect(ui->finished, &QPushButton::clicked, this, &Regist_3::RegistSucceed);
}


/*************************************************************************
【函数名称】        ~Regist_3
【函数功能】        Regist_3类析构函数
【参数】           void
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
Regist_3::~Regist_3()
{
    delete ui;
}


/*************************************************************************
【函数名称】        RegistSucceed
【函数功能】        注册成功
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void Regist_3::RegistSucceed()
{
    QMessageBox* suc = new QMessageBox(QMessageBox::Information, "Notice",
                                       "Regestration succeed!", QMessageBox::Ok, this);
    connect(suc, &QMessageBox::rejected, this, &Regist_3::Scd_ReturnMain);
    connect(suc, &QMessageBox::buttonClicked, this, &Regist_3::Scd_ReturnMain);
    suc->show();
}


/*************************************************************************
【函数名称】        Scd_ReturnMain
【函数功能】        成功注册后处理信息并返回主页
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void Regist_3::Scd_ReturnMain()
{
    tempScore = User::FirstScore(ui->comboBox->currentIndex(),
                                 ui->lineEdit->text().toDouble());
    P_USER p1("");
    Platform::u_regist(p1, tempName, tempPW, tempScore, tempRealName, tempID,
                       tempEmail);

    emit s_regSucceed(p1);
    this->close();
}


