#include "stateupdate.h"
#include "time.h"
#include <QDateTime>
#include <QDebug>
#include <QTimer>

StateUpdate::StateUpdate()
{
    checkAndUpdate1();
    checkAndUpdate2();
}


StateUpdate::~StateUpdate()
{

}


//检查mission
void StateUpdate::checkAndUpdate1()
{
    time_t timer = time(nullptr);
    tm currentTime = *localtime(&timer);
    currentTime.tm_year += 1900;
    currentTime.tm_mon += 1;

    for(auto pair: Global::allMissions)
    {
        P_MSN mission = pair.second.getMissionName();
        if (mission.exist() && mission->getReleaseState() == Mission::R_RECRUIT_M)
        {
            tm rcrtM = mission->getRecruitMTime();
            if (timeOut(currentTime, rcrtM))
            {
                Platform::msn_rct_M_judge(mission);
            }
            else if(timeNearOut(currentTime, rcrtM))
            {
                //设置timer
                int ms = timeIntervalMs(currentTime, rcrtM);
                if(ms >0)
                {
                    qDebug()<<"Set timer: " << ms << "ms";
                    QTimer* timer = new QTimer(this);
                    timer->setProperty("mission", QString::fromStdString(mission->getMissionName()));
                    QObject::connect(timer, &QTimer::timeout, this, &StateUpdate::checkMsnTime);
                    timer->start(ms);
                }
            }
        }
    }
}

//检查mngMission
void StateUpdate::checkAndUpdate2()
{
    time_t timer = time(nullptr);
    tm currentTime = *localtime(&timer);
    currentTime.tm_year += 1900;
    currentTime.tm_mon += 1;

    for(auto pair: Global::allMngMissions)
    {
        P_MNG mng = pair.second.getMissionName();
        if (mng.exist() && pair.second.getReleaseState() == Mission::R_TRANSLATING)
        {

            tm rcrtT = mng->getRecruitTTime();
            if(timeOut(currentTime, rcrtT))
            {
                Platform::msn_rct_T_judge(mng);
            }
            else if(timeNearOut(currentTime, rcrtT))
            {
                //设置timer
                int ms = timeIntervalMs(currentTime, rcrtT);
                if(ms >0)
                {
                    qDebug()<<"Set timer: " << ms << "ms";
                    QTimer* timer = new QTimer(this);
                    timer->setProperty("mngMission", QString::fromStdString(mng->getMissionName()));
                    QObject::connect(timer, &QTimer::timeout, this, &StateUpdate::checkMsnTime);
                    timer->start(ms);
                }
            }

            tm msnDDL = mng->getMissionDDL();
            if(timeOut(currentTime, msnDDL))
            {
                Platform::msn_time_out(mng);
            }
            else if(timeNearOut(currentTime, msnDDL))
            {
                //设置timer
                int ms = timeIntervalMs(currentTime, rcrtT);
                if(ms >0)
                {
                    qDebug()<<"Set timer: " << ms << "ms";
                    QTimer* timer = new QTimer(this);
                    timer->setProperty("mngMission", QString::fromStdString(mng->getMissionName()));
                    QObject::connect(timer, &QTimer::timeout, this, &StateUpdate::checkMsnTime);
                    timer->start(ms);
                }
            }
        }
    }
}


//到时间的响应
void StateUpdate::checkMsnTime()
{

    time_t timer = time(nullptr);
    tm currentTime = *localtime(&timer);
    currentTime.tm_year += 1900;
    currentTime.tm_mon += 1;

    std::string s1 = sender()->property("mission").toString().toStdString();
    P_MSN mission = s1;
    if (mission.exist())
    {
        switch (mission->getReleaseState())
        {
        case Mission::R_RECRUIT_M:
        {
            qDebug()<<"TimeOut!!";
            Platform::msn_rct_M_judge(mission);
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
        switch (mng->getReleaseState())
        {
        case Mission::R_TRANSLATING:
        {
            tm rcrtT = mng->getRecruitTTime();

            if(timeOut(currentTime, rcrtT))
            {
                qDebug()<<"TimeOut!!";
                Platform::msn_rct_T_judge(mng);
            }

            tm msnDDL = mng->getMissionDDL();
            if(timeOut(currentTime, msnDDL))
            {
                qDebug()<<"TimeOut!!";
                Platform::msn_time_out(mng);
            }
            break;
        }
        default:
            break;
        }
    }
}



//判断t1是否超过t2
bool StateUpdate::timeOut(tm t1, tm t2)
{
    if (t1.tm_year < t2.tm_year)
        return false;
    else if (t1.tm_year > t2.tm_year)
        return true;
    else
    {
        if (t1.tm_mon < t2.tm_mon)
            return false;
        else if (t1.tm_mon > t2.tm_mon)
            return true;
        else
        {
            if (t1.tm_mday < t2.tm_mday)
                return false;
            else if (t1.tm_mday > t2.tm_mday)
                return true;
            else
            {
                if (t1.tm_hour < t2.tm_hour)
                    return false;
                else if (t1.tm_hour > t2.tm_hour)
                    return true;
                else
                {
                    if (t1.tm_min < t2.tm_min)
                        return false;
                    else if (t1.tm_min > t2.tm_min)
                        return true;
                    else
                    {
                        if (t1.tm_sec < t2.tm_sec)
                            return false;
                        else
                            return true;
                    }
                }
            }
        }
    }
}


//判断是否1小时内到达DDL
bool StateUpdate::timeNearOut(tm current, tm DDL)
{
    return timeOut(timePlusHour(current), DDL);
}


//时间+1h
tm StateUpdate::timePlusHour(const tm &t)
{
    QDateTime dt(QDate(t.tm_year , t.tm_mon , t.tm_mday),  QTime(t.tm_hour, t.tm_min, t.tm_sec));

    QDateTime dt2 = dt.addSecs(3600);
    return tm{dt2.time().second(), dt2.time().minute(), dt2.time().hour(),
              dt2.date().day(), dt2.date().month(), dt2.date().year(), 0, 0, 0};
}


//获取以ms计的时间间隔
int StateUpdate::timeIntervalMs(tm pre, tm lat)
{
    if(timeOut(pre, lat))
        return -1;

    QDateTime dt1(QDate(pre.tm_year , pre.tm_mon , pre.tm_mday),  QTime(pre.tm_hour, pre.tm_min, pre.tm_sec));
    QDateTime dt2(QDate(lat.tm_year , lat.tm_mon , lat.tm_mday),  QTime(lat.tm_hour, lat.tm_min, lat.tm_sec));

    long long ms = QDateTime::fromMSecsSinceEpoch(
                                                  dt2.toMSecsSinceEpoch() -
                                                  dt1.toMSecsSinceEpoch())
                                                  .toMSecsSinceEpoch();
    return static_cast<int>(ms);
}


/*
  struct tm
{
    int tm_sec;   // seconds after the minute - [0, 60] including leap second
    int tm_min;   // minutes after the hour - [0, 59]
    int tm_hour;  // hours since midnight - [0, 23]
    int tm_mday;  // day of the month - [1, 31]
    int tm_mon;   // months since January - [0, 11]
    int tm_year;  // years since 1900
    int tm_wday;  // days since Sunday - [0, 6]
    int tm_yday;  // days since January 1 - [0, 365]
    int tm_isdst; // daylight savings time flag
};
*/

void StateUpdate::test123()
{
    //emit s_timeUp();
}


