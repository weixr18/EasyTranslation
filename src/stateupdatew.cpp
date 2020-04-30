/*************************************************************************
【文件名】                 stateupdatew.cpp
【功能模块和目的】          StateUpdateW类实现
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/

#include "stateupdatew.h"
#include "ui_stateupdatew.h"
#include <QDateTime>
#include <QDebug>
#include <QTimer>


/*************************************************************************
【函数名称】        StateUpdateW
【函数功能】        StateUpdateW类构造函数 构造该页面
【参数】
                  QWidget* parent               输入
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
StateUpdateW::StateUpdateW(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::StateUpdateW)
{
    ui->setupUi(this);
}


/*************************************************************************
【函数名称】        ~StateUpdateW
【函数功能】        StateUpdateW类析构函数
【参数】           void
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
StateUpdateW::~StateUpdateW()
{
    delete ui;
}


/*************************************************************************
【函数名称】        CheckAndUpdate1
【函数功能】        检查所有发布阶段任务更新情况
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void StateUpdateW::CheckAndUpdate1()
{
    time_t timer = time(nullptr);
    tm currentTime = *localtime(&timer);
    currentTime.tm_year += 1900;
    currentTime.tm_mon += 1;

    for (auto pair : Datum::s_LoadedMissions)
    {
        P_MSN mission = pair.second.GetMissionName();

        if (mission.exist() && mission->GetReleaseState() == Mission::R_RECRUIT_M)
        {
            tm rcrtM = mission->GetRecruitMTime();

            if (TimeOut(currentTime, rcrtM))
            {
                Platform::msn_rct_M_judge(mission);
            }
            else if (TimeNearOut(currentTime, rcrtM))
            {
                //设置timer
                int ms = TimeIntervalMs(currentTime, rcrtM);

                if (ms > 0)
                {
                    qDebug() << "Set timer: " << ms << "ms";
                    QTimer* timer = new QTimer(this);
                    timer->setProperty("mission",
                                       QString::fromStdString(mission->GetMissionName()));
                    QObject::connect(timer, &QTimer::timeout, this, &StateUpdateW::CheckMsnTime);
                    timer->start(ms);
                }
            }
        }
    }
}


/*************************************************************************
【函数名称】        CheckAndUpdate2
【函数功能】        检查所有负责阶段任务更新情况
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void StateUpdateW::CheckAndUpdate2()
{
    time_t timer = time(nullptr);
    tm currentTime = *localtime(&timer);
    currentTime.tm_year += 1900;
    currentTime.tm_mon += 1;

    for (auto pair : Datum::s_LoadedMngMissions)
    {
        P_MNG mng = pair.second.GetMissionName();

        if (mng.exist() && pair.second.GetReleaseState() == Mission::R_TRANSLATING)
        {
            tm rcrtT = mng->GetRecruitTTime();

            if (TimeOut(currentTime, rcrtT))
            {
                Platform::msn_rct_T_judge(mng);
            }
            else if (TimeNearOut(currentTime, rcrtT))
            {
                //设置timer
                int ms = TimeIntervalMs(currentTime, rcrtT);

                if (ms > 0)
                {
                    qDebug() << "Set timer: " << ms << "ms";
                    QTimer* timer = new QTimer(this);
                    timer->setProperty("mngMission", QString::fromStdString(mng->GetMissionName()));
                    QObject::connect(timer, &QTimer::timeout, this, &StateUpdateW::CheckMsnTime);
                    timer->start(ms);
                }
            }

            tm msnDDL = mng->GetMissionDDL();

            if (TimeOut(currentTime, msnDDL))
            {
                Platform::msn_time_out(mng);
            }
            else if (TimeNearOut(currentTime, msnDDL))
            {
                //设置timer
                int ms = TimeIntervalMs(currentTime, rcrtT);

                if (ms > 0)
                {
                    qDebug() << "Set timer: " << ms << "ms";
                    QTimer* timer = new QTimer(this);
                    timer->setProperty("mngMission", QString::fromStdString(mng->GetMissionName()));
                    QObject::connect(timer, &QTimer::timeout, this, &StateUpdateW::CheckMsnTime);
                    timer->start(ms);
                }
            }
        }
    }
}


/*************************************************************************
【函数名称】        CheckMsnTime
【函数功能】        计时器到点响应，更新对应任务【由sender()获取】状态
【参数】           void
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
void StateUpdateW::CheckMsnTime()
{
    time_t timer = time(nullptr);
    tm currentTime = *localtime(&timer);
    currentTime.tm_year += 1900;
    currentTime.tm_mon += 1;

    QObject* obj = sender();
    QTimer* ttimerr = qobject_cast<QTimer*>(obj);

    if (ttimerr != nullptr)
    {
        qDebug() << "cast!!!";

        if (ttimerr->isActive())
        { ttimerr->stop(); }
    }

    std::string s1 = sender()->property("mission").toString().toStdString();
    P_MSN mission = s1;

    if (mission.exist())
    {
        switch (mission->GetReleaseState())
        {
        case Mission::R_RECRUIT_M:
        {
            Platform::msn_rct_M_judge(mission);
            emit s_timeUp();
            break;
        }

        default:
            break;
        }
    }

    std::string s2 = sender()->property("mngMission").toString().toStdString();
    P_MNG mng = s2;

    if (mng.exist())
    {
        switch (mng->GetReleaseState())
        {
        case Mission::R_TRANSLATING:
        {
            tm rcrtT = mng->GetRecruitTTime();

            if (TimeOut(currentTime, rcrtT))
            {
                Platform::msn_rct_T_judge(mng);
                emit s_timeUp();
            }

            tm msnDDL = mng->GetMissionDDL();

            if (TimeOut(currentTime, msnDDL))
            {
                Platform::msn_time_out(mng);
                emit s_timeUp();
            }

            break;
        }

        default:
            break;
        }
    }
}


/*************************************************************************
【函数名称】        TimeOut
【函数功能】        判断t1是否超过t2
【参数】
                  tm t1             输入
                  tm t2             输入
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
bool StateUpdateW::TimeOut(tm t1, tm t2)
{
    if (t1.tm_year < t2.tm_year)
    { return false; }
    else if (t1.tm_year > t2.tm_year)
    { return true; }
    else
    {
        if (t1.tm_mon < t2.tm_mon)
        { return false; }
        else if (t1.tm_mon > t2.tm_mon)
        { return true; }
        else
        {
            if (t1.tm_mday < t2.tm_mday)
            { return false; }
            else if (t1.tm_mday > t2.tm_mday)
            { return true; }
            else
            {
                if (t1.tm_hour < t2.tm_hour)
                { return false; }
                else if (t1.tm_hour > t2.tm_hour)
                { return true; }
                else
                {
                    if (t1.tm_min < t2.tm_min)
                    { return false; }
                    else if (t1.tm_min > t2.tm_min)
                    { return true; }
                    else
                    {
                        if (t1.tm_sec < t2.tm_sec)
                        { return false; }
                        else
                        { return true; }
                    }
                }
            }
        }
    }
}


/*************************************************************************
【函数名称】        TimeOut
【函数功能】        判断t1是否在1小时内超过t2
【参数】
                  tm t1             输入
                  tm t2             输入
【返回值】         void
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
bool StateUpdateW::TimeNearOut(tm current, tm DDL)
{
    return TimeOut(TimePlusHour(current), DDL);
}


/*************************************************************************
【函数名称】        TimePlusHour
【函数功能】        给时间+1h
【参数】           tm& t              输入
【返回值】         tm 返回+1h后的时间结构体
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
tm StateUpdateW::TimePlusHour(const tm& t)
{
    QDateTime dt(QDate(t.tm_year , t.tm_mon , t.tm_mday),  QTime(t.tm_hour,
                 t.tm_min, t.tm_sec));

    QDateTime dt2 = dt.addSecs(3600);
    return tm{dt2.time().second(), dt2.time().minute(), dt2.time().hour(),
              dt2.date().day(), dt2.date().month(), dt2.date().year(), 0, 0, 0};
}


/*************************************************************************
【函数名称】        TimeIntervalMs
【函数功能】        获取MS计的时间间隔
【参数】
                  tm pre                  输入
                  tm lat                  输入
【返回值】         int 返回以MS计的时间间隔 若t1晚于t2返回-1
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
int StateUpdateW::TimeIntervalMs(tm pre, tm lat)
{
    if (TimeOut(pre, lat))
    { return -1; }

    QDateTime dt1(QDate(pre.tm_year , pre.tm_mon , pre.tm_mday),  QTime(pre.tm_hour,
                  pre.tm_min, pre.tm_sec));
    QDateTime dt2(QDate(lat.tm_year , lat.tm_mon , lat.tm_mday),  QTime(lat.tm_hour,
                  lat.tm_min, lat.tm_sec));

    long long ms = QDateTime::fromMSecsSinceEpoch(
        dt2.toMSecsSinceEpoch() -
        dt1.toMSecsSinceEpoch())
        .toMSecsSinceEpoch();
    return static_cast<int>(ms);
}



