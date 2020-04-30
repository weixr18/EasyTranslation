#ifndef STATEUPDATE_H
#define STATEUPDATE_H
#include <CTP.h>
#include <QMainWindow>


class StateUpdate : public QMainWindow
{
    Q_OBJECT

public:
    StateUpdate();
    virtual ~StateUpdate();

public:
    void checkAndUpdate1();
    void checkAndUpdate2();
    void checkMsnTime();

    static bool timeOut(tm current, tm DDL);
    static bool timeNearOut(tm current, tm DDL);
    static tm timePlusHour(const tm &t);
    static int timeIntervalMs(tm t1, tm t2);

    void test123();

signals:
    void s_timeUp();

};

#endif // STATEUPDATE_H
