/*************************************************************************
【文件名】                 rcrtmfailproc.cpp
【功能模块和目的】          RcrtMFailProc类实现
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/


#include "rcrtmfailproc.h"
#include "ui_rcrtmfailproc.h"
#include "cfmdialog.h"
#include <QMessageBox>


/*************************************************************************
【函数名称】        RcrtMFailProc
【函数功能】        RcrtMFailProc类构造函数 构造该页面
【参数】
                  QWidget* parent          输入
                  P_MSN mission            输入
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
RcrtMFailProc::RcrtMFailProc(QWidget* parent, P_MSN mission) :
    QMainWindow(parent),
    ui(new Ui::RcrtMFailProc),
    mission(mission)
{
    ui->setupUi(this);
    tm DDL = mission->GetMissionDDL();
    QDateTime QDDL = QDateTime(QDate(DDL.tm_year, DDL.tm_mon, DDL.tm_mday),
                               QTime(DDL.tm_hour, DDL.tm_min, DDL.tm_sec));
    ui->missionDDL->setMinimumDateTime(QDDL);
    ui->missionDDL->setMaximumDateTime(QDateTime::currentDateTime().addYears(1));
    ui->missionDDL->setDateTime(QDDL);

    ui->recruitMTime->setMinimumDateTime(QDateTime::currentDateTime());
    ui->recruitMTime->setMaximumDateTime(QDDL);
    ui->recruitMTime->setDateTime(QDateTime::currentDateTime().addDays(1));

    ui->recruitMTime->setEnabled(false);
    ui->missionDDL->setEnabled(false);

    ui->label_notice->setText("Your mission " + QString::fromStdString(
                                  mission->GetMissionName())
                              + " failed to recruit a manager. Please choose a solution.");
    ui->label_notice->setWordWrap(true);
}


/*************************************************************************
【函数名称】        ~RcrtMFailProc
【函数功能】        RcrtMFailProc类析构函数
【参数】           void
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
RcrtMFailProc::~RcrtMFailProc()
{
    delete ui;
}


/*************************************************************************
【函数名称】        on_cancel_clicked
【函数功能】        操作取消响应
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void RcrtMFailProc::on_cancel_clicked()
{
    emit s_returnLast(this);
}


/*************************************************************************
【函数名称】        on_radio_delay_toggled
【函数功能】        radio钮切换响应
【参数】
                  bool checked          输入
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void RcrtMFailProc::on_radio_delay_toggled(bool checked)
{
    ui->recruitMTime->setEnabled(checked);
    ui->missionDDL->setEnabled(checked);
}


/*************************************************************************
【函数名称】        on_confirm_clicked
【函数功能】        确认按钮响应
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void RcrtMFailProc::on_confirm_clicked()
{
    if (ui->radio_delay->isChecked())
    {
        QMessageBox* inf = new QMessageBox(QMessageBox::Warning, "Notice",
             "Set recruit manager succeed.",
             QMessageBox::Yes, this);
        inf->show();
        connect(inf, &QMessageBox::accepted, this, &RcrtMFailProc::ExtendRcrtMTime);

    }
    else if (ui->radio_cancel->isChecked())
    {
        CfmDialog* cfm = new CfmDialog(this, this,
            "Are you sure to cancel this mission? Your operation cannot be redone.");

        cfm->show();
        connect(cfm, &CfmDialog::s_confirmed, this, &RcrtMFailProc::CancelMission);
    }
}

/*************************************************************************
【函数名称】        CancelMission
【函数功能】        任务取消处理
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void RcrtMFailProc::CancelMission()
{
    QObject* obj = sender();
    CfmDialog* cfm = qobject_cast<CfmDialog*>(obj);

    if (cfm != nullptr)
    {
        cfm->close();
    }

    QMessageBox* notice = new QMessageBox(QMessageBox::Critical, "Notice",
                                          QString("Mission " + QString::fromStdString(mission->GetMissionName()) +
                                                  " is canceled."),
                                          QMessageBox::Ok, this);
    notice->show();
    Platform::r_cancel_mission(mission->GetReleaser(), mission);
    emit s_returnLast(this);
}

/*************************************************************************
【函数名称】        ExtendRcrtMTime
【函数功能】        任务招募时间延长处理
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void RcrtMFailProc::ExtendRcrtMTime()
{
    int y1 = ui->recruitMTime->date().year();
    int m1 = ui->recruitMTime->date().month();
    int d1 = ui->recruitMTime->date().day();
    int h1 = ui->recruitMTime->time().hour();
    int mi1 = ui->recruitMTime->time().minute();
    tm rcrt = Mission::IntToTime(y1, m1, d1, h1, mi1);

    Platform::r_rcrt_M_time_extend(mission->GetReleaser(), mission, rcrt);
    emit s_returnLast(this);
}


