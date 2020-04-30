/*************************************************************************
【文件名】                 Datum.h
【功能模块和目的】          Datum类声明
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/

#ifndef GLOBAL_H
#define GLOBAL_H

#include <map>
#include "DBOP.h"
#include "message.h"
#include "stateupdatec.h"


/*************************************************************************
【类名】              Datum
【功能】              后端-数据模块-核心数据处理类
【接口说明】
    1   AddNewUser              添加用户
    2   UpdateDB                数据库更新
    3   SearchMissions          查询符合条件的任务

    4   AddNewMission           添加新任务
    5   MissionTrsfMngMission   发布阶段任务转换为负责阶段
    6   MngCreateSubMsn         负责阶段任务生成子任务
    7   AddNewMessage           添加新信息

    8   UserNameExist           查询用户名是否存在
    9   GetUserByName           通过用户名获取任务
    10  MissionNameExist        查询任务名是否存在
    11  GetMissionByName        通过任务名获取任务
    12  MngMsnNameExist         查询负责阶段任务名是否存在
    13  GetMngMsnByName         通过任务名获取负责阶段任务
    14  SubMsnKeyExist          查询子任务标识符是否存在
    15  GetSubMsnByKey          通过标识符获取子任务

    16  V_Find                  查询某一元素是否在某一vector中

【开发者及日期】      魏欣然 2019/08/01
【更改记录】          无
*************************************************************************/

class Datum
{
    friend class Platform;
    friend class StateUpdateW;

    /**数据库交互方法**/
public:
    //添加用户
    static bool AddNewUser(const User& user);
    //更新数据库
    static bool UpdateDB();
    //查询符合条件的任务
    static std::vector<std::string> SearchMissions(const std::string& s);
    //查询用户收到的消息
    static std::vector<int> SearchMessages(const std::string user);


    /**添加&转换方法**/
public:
    //添加新任务
    static bool AddNewMission(const Mission& mission);
    //发布阶段任务转换为负责阶段
    static bool MissionTrsfMngMission(const Mission& mission,
                                      const ManageMission& mng);
    //负责阶段任务生成子任务
    static bool MngCreateSubMsn(ManageMission& mng,
                                const std::vector<std::pair<std::string, std::string>>& assigns);
    //添加新信息
    static bool AddNewMessage(const std::string& sender,
                              const std::string& receiver, const std::string& text);

    /**查询方法**/
public:
    //查询用户名是否存在
    static bool UserNameExist(const std::string& username);
    //通过用户名获取任务
    static bool GetUserByName(const std::string& username, User*& result);
    //查询任务名是否存在
    static bool MissionNameExist(const std::string& missionName);
    //通过任务名获取任务
    static bool GetMissionByName(const std::string& missionName, Mission*& result);
    //查询负责阶段任务名是否存在
    static bool MngMsnNameExist(const std::string& missionName);
    //通过任务名获取负责阶段任务
    static bool GetMngMsnByName(const std::string& missionName,
                                ManageMission*& result);
    //查询子任务标识符是否存在
    static bool SubMsnKeyExist(const KEY_SUB& subKey);
    //通过标识符获取子任务
    static bool GetSubMsnByKey(const KEY_SUB& subKey, SubMission*& result);

    static bool MessageIdExist(const int id);
    static bool GetMessageByID(const int id, Message& result);
    static bool ReadMessage(const int id);


    //模板函数-查询某一元素是否在某一vector中
    template<typename T>
    static bool V_Find(std::vector <T, std::allocator<T>>& v, T x)
    {
        return !(std::find(v.begin(), v.end(), x) == v.end());
    }


    /**构造函数与析构函数**/
private:
    Datum();
    Datum(const Datum& g);
    virtual ~Datum();
    Datum& operator=(const Datum& g);

    /**数据成员**/
private:
    static std::map<std::string, User> s_LoadedUsers;
    static std::map<std::string, Mission> s_LoadedMissions;
    static std::map<std::string, ManageMission> s_LoadedMngMissions;
    static std::map<KEY_SUB, SubMission> s_LoadedSubMissions;
    static std::map<int, Message> s_LoadedMessages;

    static DBOP s_dbop;
    static int s_imessageNum;
};


#endif // GLOBAL_H
