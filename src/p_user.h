/*************************************************************************
【文件名】                 p_user.h
【功能模块和目的】          P_USER类声明
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/


#ifndef P_USER_H
#define P_USER_H
#include <string>
#include "user.h"

class P_USER
{
public:
    P_USER(std::string username = "");
    P_USER(User* u);
    virtual ~P_USER();
    P_USER& operator= (const P_USER& p);

public:
    User* operator ->() const;
    User operator*() const;
    bool operator !=(const P_USER& p) const;
    bool operator ==(const P_USER& p) const;
    P_USER& operator= (const User * (&user));
    bool exist() const;

private:
    std::string m_Key;
};

#endif	//P_MSN_H
