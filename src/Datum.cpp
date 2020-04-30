/*************************************************************************
【文件名】                 Datum.cpp
【功能模块和目的】          Datum类实现
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/

#include "Datum.h"
#include <iostream>

Datum::Datum() {}
Datum::~Datum() {}
Datum::Datum(const Datum& g) {}
Datum& Datum::operator=(const Datum& g) { return *this; }


std::map<std::string, User> Datum::s_LoadedUsers =
    std::map<std::string, User>();
std::map<std::string, Mission> Datum::s_LoadedMissions =
    std::map<std::string, Mission>();
std::map<std::string, ManageMission> Datum::s_LoadedMngMissions =
    std::map<std::string, ManageMission>();
std::map<KEY_SUB, SubMission> Datum::s_LoadedSubMissions =
    std::map<KEY_SUB, SubMission>();
std::map<int, Message> Datum::s_LoadedMessages =
    std::map<int, Message>();

DBOP Datum::s_dbop = DBOP();
int Datum::s_imessageNum = s_dbop.GetMaxMessageID() + 1;

/******************************查找方法******************************/


//用户存在查找
bool Datum::UserNameExist(const std::string& username)
{
    auto iter = Datum::s_LoadedUsers.find(username);

    if (Datum::s_LoadedUsers.end() != iter)
    {
        return true;
    }
    else
    {
        return s_dbop.UserExist(username);
    }
}

//用户获取
bool Datum::GetUserByName(const std::string& username, User*& result)
{
    auto iter = Datum::s_LoadedUsers.find(username);

    if (Datum::s_LoadedUsers.end() != iter)
    {
        result = &((*iter).second);
        return true;
    }
    else
    {
        //如果数据库中找到，那么load该用户并返回true， 否则返回false
        if (s_dbop.UserExist(username))
        {
            User u1;
            s_dbop.GetUser(username, u1);
            s_LoadedUsers.insert(pair<std::string, User>(username, u1));

            iter = Datum::s_LoadedUsers.find(username);
            result = &((*iter).second);
            return true;
        }
        else
        {
            result = nullptr;
            return false;
        }
    }
}

//任务存在查找【同时在两张表查找】
bool Datum::MissionNameExist(const std::string& missionName)
{
    auto iter1 = Datum::s_LoadedMissions.find(missionName);
    auto iter2 = Datum::s_LoadedMngMissions.find(missionName);

    if (Datum::s_LoadedMissions.end() != iter1 ||
        Datum::s_LoadedMngMissions.end() !=
        iter2)					//.end()不等于iter迭代器，说明找到了
    {
        return true;
    }
    else
    {
        return (s_dbop.MissionExist(missionName) ||
                s_dbop.MngMissionExist(missionName));
    }
}


//任务获取【同时在两张表查找】
bool Datum::GetMissionByName(const std::string& missionName, Mission*& result)
{
    auto iter1 = Datum::s_LoadedMissions.find(missionName);
    auto iter2 = Datum::s_LoadedMngMissions.find(missionName);

    if (Datum::s_LoadedMissions.end() != iter1)
    {
        result = &((*iter1).second);
        return true;
    }
    else if (Datum::s_LoadedMngMissions.end() != iter2)
    {
        result = static_cast<Mission*>( &((*iter2).second) );
        return true;
    }
    else
    {
        if (s_dbop.MissionExist(missionName))
        {
            Mission m1;
            s_dbop.GetMission(missionName, m1);
            StateUpdateC::CheckAndUpdate(m1);
            s_LoadedMissions.insert(pair<std::string, Mission>(missionName, m1));

            iter1 = Datum::s_LoadedMissions.find(missionName);
            result = &((*iter1).second);
            return true;
        }
        else if (s_dbop.MngMissionExist(missionName))
        {
            ManageMission m2;
            s_dbop.GetMngMission(missionName, m2);
            StateUpdateC::CheckAndUpdate(m2);
            s_LoadedMngMissions.insert(pair<std::string, ManageMission>(missionName, m2));

            iter2 = Datum::s_LoadedMngMissions.find(missionName);
            result = static_cast<Mission*>( &((*iter2).second) );
            return true;
        }
        else
        {
            result = nullptr;
            return false;
        }
    }
}


//管理任务存在查找【只在管理表查找】
bool Datum::MngMsnNameExist(const std::string& missionName)
{
    auto iter = Datum::s_LoadedMngMissions.find(missionName);

    if (Datum::s_LoadedMngMissions.end() != iter)
    {
        return true;
    }
    else
    {
        return s_dbop.MngMissionExist(missionName);
    }
}


//管理任务获取【只在管理表查找】
bool Datum::GetMngMsnByName(const std::string& missionName,
                            ManageMission*& result)
{
    auto iter = Datum::s_LoadedMngMissions.find(missionName);

    if (Datum::s_LoadedMngMissions.end() != iter)
    {
        result = &((*iter).second);
        return true;
    }
    else
    {
        if (s_dbop.MngMissionExist(missionName))
        {
            ManageMission m2;
            s_dbop.GetMngMission(missionName, m2);
            StateUpdateC::CheckAndUpdate(m2);
            s_LoadedMngMissions.insert(pair<std::string, ManageMission>(missionName, m2));

            iter = Datum::s_LoadedMngMissions.find(missionName);
            result = &((*iter).second);
            return true;
        }
        else
        {
            result = nullptr;
            return false;
        }
    }
}


//子任务存在查找
bool Datum::SubMsnKeyExist(const KEY_SUB& subKey)
{
    auto iter = Datum::s_LoadedSubMissions.find(subKey);

    if (Datum::s_LoadedSubMissions.end() != iter)
    {
        return true;
    }
    else
    {
        return s_dbop.SubMissionExist(subKey);
    }
}


//子任务获取
bool Datum::GetSubMsnByKey(const KEY_SUB& subKey, SubMission*& result)
{
    auto iter = Datum::s_LoadedSubMissions.find(subKey);

    if (Datum::s_LoadedSubMissions.end() != iter)
    {
        result = &((*iter).second);
        return true;
    }
    else
    {
        if (s_dbop.SubMissionExist(subKey))
        {
            SubMission s;
            s_dbop.GetSubMission(subKey, s);
            s_LoadedSubMissions.insert(pair<KEY_SUB, SubMission>(subKey, s));

            iter = Datum::s_LoadedSubMissions.find(subKey);
            result = &((*iter).second);
            return true;
        }
        else
        {
            result = nullptr;
            return false;
        }
    }
}


//消息存在
bool Datum::MessageIdExist(const int id)
{
    auto iter = Datum::s_LoadedMessages.find(id);

    if (Datum::s_LoadedMessages.end() != iter)
    {
        return true;
    }
    else
    {
        return s_dbop.MessageExist(id);
    }
}

//消息获取
bool Datum::GetMessageByID(const int id, Message &result)
{
    auto iter = Datum::s_LoadedMessages.find(id);

    if (Datum::s_LoadedMessages.end() != iter)
    {
        result = (*iter).second;
        return true;
    }
    else
    {
        if (s_dbop.MessageExist(id))
        {
            Message msg;
            s_dbop.GetMessage(id,msg);
            s_LoadedMessages.insert(pair<int, Message>(id, msg));

            iter = Datum::s_LoadedMessages.find(id);
            result = (*iter).second;
            return true;
        }
        else
        {
            return false;
        }
    }
}

bool Datum::ReadMessage(const int id)
{
    auto iter = Datum::s_LoadedMessages.find(id);

    if (Datum::s_LoadedMessages.end() != iter)
    {
        (*iter).second.setRead();
        return true;
    }
    else
    {
        return false;
    }
}


/******************************数据库交互方法******************************/

//用户添加
bool Datum::AddNewUser(const User& user)
{
    if (UserNameExist(user.GetUserName()))
    {
        return false;
    }
    else
    {
        s_dbop.WriteUser(user);
        return true;
    }
}



//数据库更新
bool Datum::UpdateDB()
{
    for (auto pair : s_LoadedUsers)
    {
        if (!s_dbop.UserExist(pair.first))
        {
            qDebug() << "Error: User not exist\
                       \n\t from: Datum::updateDB()";
            continue;
        }

        s_dbop.UpdateUser(pair.second);
    }

    s_LoadedUsers.clear();


    for (auto pair : s_LoadedMissions)
    {
        if (!s_dbop.MissionExist(pair.first))
        {
            s_dbop.WriteMission(pair.second);
        }
        else
        {
            s_dbop.UpdateMission(pair.second);
        }
    }

    s_LoadedMissions.clear();


    for (auto pair : s_LoadedMngMissions)
    {
        if (!s_dbop.MngMissionExist(pair.first))
        {
            if (s_dbop.MissionExist(pair.first))
            {
                s_dbop.MissionTransferMng(pair.second);
            }
            else
            {
                qDebug() << "Transfer Error!!";
            }
        }
        else
        {
            s_dbop.UpdateMngMission(pair.second);
        }
    }

    s_LoadedMngMissions.clear();


    for (auto pair : s_LoadedSubMissions)
    {
        if (!s_dbop.SubMissionExist(pair.first))
        {
            s_dbop.WriteSubMission(pair.second);
        }
        else
        {
            s_dbop.UpdateSubMission(pair.second);
        }
    }

    s_LoadedSubMissions.clear();


    for (auto pair : s_LoadedMessages)
    {
        if (!s_dbop.MessageExist(pair.first))
        {
            s_dbop.WriteMessage(pair.second);
        }
        else
        {
            if(pair.second.GetReadState())
            {
                s_dbop.DeleteMessage(pair.first);
            }
        }
    }
    s_LoadedMessages.clear();

    return true;
}


std::vector<std::string> Datum::SearchMissions(const std::string& s)
{
    return s_dbop.SearchMissions(s);
}


std::vector<int> Datum::SearchMessages(const std::string user)
{
    return s_dbop.SearchMessages(user);
}

/******************************添加方法******************************/



//任务添加
bool Datum::AddNewMission(const Mission& mission)
{
    if (MissionNameExist(mission.GetMissionName()))
    {
        return false;
    }								//添加失败
    else
    {
        Datum::s_LoadedMissions.insert(pair<const std::string, Mission>
                                       (mission.GetMissionName(), mission));
        return true;
    }
}


//任务转换为管理任务
bool Datum::MissionTrsfMngMission(const Mission& mission,
                                  const ManageMission& mng)
{
    if (mission.GetMissionName() != mng.GetMissionName())
    {
        return false;
    }

    std::string missionName = mission.GetMissionName();
    auto iter = Datum::s_LoadedMissions.find(missionName);

    if (Datum::s_LoadedMissions.end() == iter)
    { return false; }

    Datum::s_LoadedMissions.erase(missionName);
    Datum::s_LoadedMngMissions.insert(std::pair<std::string, ManageMission>
                                      (missionName, mng));
    return true;
}


//管理任务创建子任务
bool Datum::MngCreateSubMsn(ManageMission& mng,
                            const std::vector<std::pair<std::string, std::string>>& assign)
{
    ULL subMsnNum = assign.size();

    if (subMsnNum == 0)
    {
        return false;
    }

    if (subMsnNum != mng.GetTranslators().size())
    {
        return false;
    }

    for (auto kvpair : assign)
    {
        if (!UserNameExist(kvpair.first))
        {
            return false;
        }

        if (!V_Find(mng.GetTranslators(), kvpair.first))
        {
            return false;
        }

        if (kvpair.second == std::string(""))
        {
            return false;
        }
    }

    for (auto kvpair : assign)
    {
        SubMission* temp = new SubMission(mng, kvpair.first);
        temp->SetSubMissionState(SubMission::T_WAIT_FOR_TRANS);
        temp->SetSrcSubText(kvpair.second);
        KEY_SUB key(mng.GetMissionName(), kvpair.first);
        Datum::s_LoadedSubMissions.insert(std::pair<KEY_SUB, SubMission>(key, *temp));
        delete temp; temp = nullptr;
    }

    return true;
}


bool Datum::AddNewMessage(const std::string& sender,
                          const std::string& receiver, const std::string& text)
{
    if (!UserNameExist(sender) || !UserNameExist(receiver))
    {
        return false;
    }
    else if (sender == receiver)
    {
        return false;
    }
    else if (text.size() == 0)
    {
        return false;
    }

    time_t timer = time(nullptr);
    tm currentTime = *localtime(&timer);
    currentTime.tm_year += 1900;
    currentTime.tm_mon += 1;

    Message m1(sender, receiver, text, currentTime, s_imessageNum);
    s_LoadedMessages.insert(pair<int, Message>(s_imessageNum, m1));
    s_imessageNum++;

    return true;
}


