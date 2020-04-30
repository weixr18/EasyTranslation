/*************************************************************************
【文件名】                 stateupdatec.h
【功能模块和目的】          StateUpdateC类声明
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/


#ifndef STATEUPDATEC_H
#define STATEUPDATEC_H
#include <time.h>
#include "mission.h"
#include "managemission.h"


class StateUpdateC
{
public:
    StateUpdateC();
    virtual ~StateUpdateC();

public:
    static void CheckAndUpdate(Mission& mission);
    static void CheckAndUpdate(ManageMission& mng);

private:
    static bool RcrtMJudge(Mission& mission);
    static bool RcrtTJudge(ManageMission& mng);
    static bool MissionTimeOutJudge(ManageMission& mng);

    static bool TimeOut(tm current, tm DDL);


};

#endif // STATEUPDATEC_H
