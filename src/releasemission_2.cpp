/*************************************************************************
【文件名】                 releasemission_2.cpp
【功能模块和目的】          ReleaseMission_2类实现
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/


#include "releasemission_2.h"
#include "ui_releasemission_2.h"
#include <QMessageBox>
#include <QDebug>


/*************************************************************************
【函数名称】        ReleaseMission_2
【函数功能】        ReleaseMission_2类构造函数 构造该页面
【参数】
                  QWidget*             parent      输入
                  P_USER               user        输入
                  std::string          tempName    输入
                  std::string          tempText    输入
                  std::string          tempIntro   输入
                  Mission::Language    tempLang    输入
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
ReleaseMission_2::ReleaseMission_2(QWidget* parent, P_USER user,
                                   std::string tempName, std::string tempText,
                                   std::string tempIntro, Mission::Language tempSrcLang,
                                   Mission::Language tempTarLang) :
    QMainWindow(parent),
    ui(new Ui::ReleaseMission_2),
    user(user),
    tempName(tempName),
    tempText(tempText),
    tempIntro(tempIntro),
    tempSrcLang(tempSrcLang),
    tempTarLang(tempTarLang)
{
    ui->setupUi(this);

    ui->recruitMTime->setMinimumDateTime(QDateTime::currentDateTime());
    ui->recruitMTime->setMaximumDateTime(QDateTime::currentDateTime().addYears(1));

    ui->missionDDL->setMinimumDateTime(QDateTime::currentDateTime().addDays(7));
    ui->missionDDL->setMaximumDateTime(QDateTime::currentDateTime().addYears(1));

    ui->recruitMTime->setDateTime(QDateTime::currentDateTime().addDays(3));
    ui->missionDDL->setDateTime(QDateTime::currentDateTime().addDays(15));
    ui->awardAmount->setSingleStep(10);

    connect(ui->cancel, &QPushButton::clicked, this,
            &ReleaseMission_2::RlsCancel);             //取消
    connect(ui->completed, &QPushButton::clicked, this,
            &ReleaseMission_2::RlsContinue);           //继续
}


/*************************************************************************
【函数名称】        ~ReleaseMission_2
【函数功能】        ReleaseMission_2类析构函数
【参数】           void
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
ReleaseMission_2::~ReleaseMission_2()
{
    delete ui;
}


/*************************************************************************
【函数名称】        RlsContinue
【函数功能】        发布继续
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void ReleaseMission_2::RlsContinue()
{
    if (user == nullptr || tempName == "" ||
        tempText == "" || tempIntro == "")
    {
        //此处弹错误框
    }
    else
    {
        int y1 = ui->recruitMTime->date().year();
        int m1 = ui->recruitMTime->date().month();
        int d1 = ui->recruitMTime->date().day();
        int h1 = ui->recruitMTime->time().hour();
        int mi1 = ui->recruitMTime->time().minute();
        tempRTime = Mission::IntToTime(y1, m1, d1, h1, mi1);

        int y2 = ui->missionDDL->date().year();
        int m2 = ui->missionDDL->date().month();
        int d2 = ui->missionDDL->date().day();
        int h2 = ui->missionDDL->time().hour();
        int mi2 = ui->missionDDL->time().minute();
        tempDDL = Mission::IntToTime(y2, m2, d2, h2, mi2);

        tempAmount = ui->awardAmount->value();

        QMessageBox* success = new QMessageBox(QMessageBox::Information, "Notice",
            "Mission Release Succeed!!\nPress 'OK' and return HomePage.", QMessageBox::Ok,
            this);
        success->show();
        connect(success, &QMessageBox::accepted, this, &ReleaseMission_2::RlsSucceed);
    }
}


/*************************************************************************
【函数名称】        RlsSucceed
【函数功能】        发布成功处理
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void ReleaseMission_2::RlsSucceed()
{

    //对于发布信息的处理
    P_USER p1 = this->user;
    P_MSN m1 = nullptr;
    Platform::u_release_mission(p1, m1, tempName, tempIntro,
                                tempText, tempRTime, tempDDL,
                                tempAmount, tempSrcLang, tempTarLang);

    emit s_rlsSucceed(m1);
    this->close();
}

/*************************************************************************
【函数名称】        RlsCancel
【函数功能】        发布取消处理
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void ReleaseMission_2::RlsCancel()
{
    emit s_rlsCancel();
    this->close();
}

