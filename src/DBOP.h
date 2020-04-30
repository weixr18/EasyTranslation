/*************************************************************************
【文件名】                 DBOP.h
【功能模块和目的】          DBOP类声明
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/

#ifndef DBOP_H
#define DBOP_H
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <stdarg.h>

#include "user.h"
#include "mission.h"
#include "managemission.h"
#include "submission.h"
#include "message.h"


/*************************************************************************
【类名】              DBOP
【功能】              后端-数据模块-数据库操作
【接口说明】
                    见下方注释
【开发者及日期】      魏欣然 2019/08/01
【更改记录】          无
*************************************************************************/
class DBOP
{
    /**数据读写操作**/
public:
    //查找用户是否存在
    bool UserExist(const std::string& username);
    //写入用户数据
    bool WriteUser(const User& user);
    //获取用户数据
    bool GetUser(const std::string& username, User& user);
    //更新用户数据
    bool UpdateUser(const User& user);

    //查找任务是否存在
    bool MissionExist(const std::string& name);
    //写入任务数据
    bool WriteMission(const Mission& mission);
    //获取任务数据
    bool GetMission(const std::string& name, Mission& mission);
    //更新任务数据
    bool UpdateMission(const Mission& mission);

    //发布阶段任务转换为负责阶段任务
    bool MissionTransferMng(const ManageMission& mng);

    //查找负责阶段任务是否存在
    bool MngMissionExist(const std::string& name);
    //写入负责阶段任务数据
    bool WriteMngMission(const ManageMission& mng);
    //获取负责阶段任务数据
    bool GetMngMission(const std::string& name, ManageMission& mng);
    //更新负责阶段任务数据
    bool UpdateMngMission(const ManageMission& mng);

    //查找子任务是否存在
    bool SubMissionExist(const KEY_SUB key);
    //写入子任务数据
    bool WriteSubMission(const SubMission& sub);
    //获取子任务数据
    bool GetSubMission(const KEY_SUB key, SubMission& sub);
    //更新子任务数据
    bool UpdateSubMission(const SubMission& sub);

    //查找消息是否存在
    bool MessageExist(const int id);
    //写入消息数据
    bool WriteMessage(const Message& message);
    //获取消息数据
    bool GetMessage(const int id, Message& message);
    //删除消息数据
    bool DeleteMessage(const int id);


    /**数据查询服务**/
public:
    //查询用户名密码是否匹配
    bool NameMatchPassword(const std::string& name, const std::string& password);
    //查找符合条件的任务
    std::vector<std::string> SearchMissions(const std::string& s, ...);
    //查找某一用户收到的任务
    std::vector<int> SearchMessages(const std::string& user);
    //获得Message最大标号
    int GetMaxMessageID();

    /**数据准备/转换方法**/
private:
    //将字符串分割为字符串vector
    std::vector<std::string> SplitStrings(const std::string& s1);
    //将字符串vector合并为字符串
    std::string JoinStrings(const std::vector<std::string>& v1);

    //将字符串分割为字符串对向量
    std::vector<KEY_SUB> SplitPairStrings(const std::string& s2);
    //将字符串对向量合并为字符串
    std::string JoinPairStrings(const std::vector<KEY_SUB>& v2);

    //由任务名和翻译者列表生成子任务列表
    std::vector<KEY_SUB> GenerateSubMissions(const string& name,
            const std::vector<std::string>& translators);

public:
    /**构造函数析构函数等**/
    //构造函数
    DBOP();
    //拷贝构造函数
    DBOP(const DBOP& dbop);
    //析构函数
    virtual ~DBOP();
    //赋值运算符
    DBOP& operator=(const DBOP& dbop);

    /**数据成员**/
private:
    QSqlDatabase m_DB {QSqlDatabase::addDatabase("QSQLITE")};
    QSqlQuery m_SqlQuery ;

};

#endif // DBOP_H
