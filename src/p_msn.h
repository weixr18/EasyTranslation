/*************************************************************************
【文件名】                 p_msn.h
【功能模块和目的】          P_MSN类声明
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/


#ifndef P_MSN_H
#define P_MSN_H
#include <string>
#include "mission.h"


class P_MSN
{
public:
    P_MSN(const std::string& Missionname = "");
    P_MSN(Mission* u);
    virtual ~P_MSN();
    P_MSN& operator= (const P_MSN& p);

public:
    Mission* operator ->() const;
    Mission operator* () const;
    bool operator !=(const P_MSN& p) const;
    bool operator ==(const P_MSN& p) const;
    P_MSN& operator= (const Mission * (&Mission));
    bool exist() const;

private:
    std::string m_Key;
};

#endif //P_MSN_H
