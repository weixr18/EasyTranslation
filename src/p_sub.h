/*************************************************************************
【文件名】                 p_sub.h
【功能模块和目的】          P_SUB类声明
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/


#ifndef P_SUB_H
#define P_SUB_H
#include <string>
#include "submission.h"


class P_SUB
{
public:
    P_SUB(const KEY_SUB& key = KEY_SUB_NULL);
    P_SUB(const SubMission * (&SUB));
    virtual ~P_SUB();
    P_SUB& operator= (const P_SUB& p);

public:
    SubMission* operator ->() const;
    SubMission operator* () const;
    bool operator !=(const P_SUB& p) const;
    bool operator ==(const P_SUB& p) const;
    P_SUB& operator= (const SubMission * (&SUB));
    bool exist() const;

private:
    KEY_SUB m_Key;
};

#endif	//P_SUB_H
