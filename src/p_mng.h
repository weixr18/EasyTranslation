/*************************************************************************
【文件名】                 p_mng.h
【功能模块和目的】          P_MNG类声明
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/


#ifndef P_MNG_H
#define P_MNG_H
#include <string>
#include "managemission.h"


class P_MNG
{
public:
    P_MNG(const std::string& Missionname = "");
    P_MNG(const ManageMission * (&mng));
    virtual ~P_MNG();
    P_MNG& operator= (const P_MNG& p);

public:
    ManageMission* operator ->() const;
    ManageMission operator* () const;
    bool operator !=(const P_MNG& p) const;
    bool operator ==(const P_MNG& p) const;
    P_MNG& operator= (const ManageMission * (&mng));
    bool exist() const;

private:
    std::string m_Key;
};

#endif  //P_MNG_H
