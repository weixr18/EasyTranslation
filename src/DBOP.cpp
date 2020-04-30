/*************************************************************************
【文件名】                 DBOP.cpp
【功能模块和目的】          DBOP类实现-PART I
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/

#include "DBOP.h"


//构造函数
DBOP::DBOP()
{
    //建立并打开数据库
    m_DB.setDatabaseName("./data/MyDataBase.db");

    if (!m_DB.open())
    {
        qDebug() << "Error: Failed to connect database." << m_DB.lastError();
    }
    else
    {
        qDebug() << "Succeed to connect database." ;
    }

}

DBOP::~DBOP()
{

    //关闭数据库
    m_DB.close();
}


//用户名密码匹配
bool DBOP::NameMatchPassword(const std::string& name,
                             const std::string& password)
{
    m_SqlQuery.exec("select count(*) from users where name = "
                    + QString("\"") + QString::fromStdString(name) + QString("\"")
                    + "and password = "
                    + QString("\"") + QString::fromStdString(password) + QString("\""));
    m_SqlQuery.next();
    int Num = m_SqlQuery.value(0).toInt();

    return (Num > 0);
}

//按条件查找任务
std::vector<std::string> DBOP::SearchMissions(const std::string& s, ...)
{
    std::vector<std::string> v;

    if (s == "")
    {
        m_SqlQuery.exec("select * from missions");

        if (!m_SqlQuery.exec())
        {
            qDebug() << m_SqlQuery.lastError();
            return v;
        }
        else
        {
            while (m_SqlQuery.next())
            {
                std::string name = m_SqlQuery.value(0).toString().toStdString();
                v.push_back(name);
            }
        }

        m_SqlQuery.exec("select * from mngmissions");

        if (!m_SqlQuery.exec())
        {
            qDebug() << m_SqlQuery.lastError();
            return v;
        }
        else
        {
            while (m_SqlQuery.next())
            {
                std::string name = m_SqlQuery.value(0).toString().toStdString();
                v.push_back(name);
            }
        }

        return v;
    }

    return v;
}


//按用户查找消息
std::vector<int> DBOP::SearchMessages(const std::string &user)
{
    std::vector<int> v;

    m_SqlQuery.exec("select * from messages where receiver = "
                    "\"" + QString::fromStdString(user) + "\"");

    if (!m_SqlQuery.exec())
    {
        qDebug()<<"DBOP::SearchMessages";
        qDebug()<<"user:" <<QString::fromStdString(user);
        qDebug() << m_SqlQuery.lastError();
        return v;
    }
    else
    {
        while (m_SqlQuery.next())
        {
            int id = m_SqlQuery.value(0).toInt();
            v.push_back(id);
        }
    }
    return v;
}

//获取最大消息ID
int DBOP::GetMaxMessageID()
{
    m_SqlQuery.exec("SELECT MAX(id) FROM messages");
    if (!m_SqlQuery.exec())
    {
        qDebug() << m_SqlQuery.lastError();
        return -2;
    }
    else
    {
        m_SqlQuery.next();
        return m_SqlQuery.value(0).toInt();
    }
}

//字符串合并
std::string DBOP::JoinStrings(const std::vector<std::string>& v1)
{
    std::string train;

    for (ULL i = 0; i < v1.size(); i++)
    {
        train += v1[i];
        train += "|";
    }

    return train;

}

//字符串分割
std::vector<std::string> DBOP::SplitStrings(const std::string& s1)
{
    std::vector<std::string> dest;
    std::string str = s1;
    std::string substring;
    std::string::size_type start = 0, index;
    dest.clear();
    std::string separator = "|";
    index = str.find_first_of(separator, start);

    do
    {
        if (index != std::string::npos)
        {
            substring = str.substr(start, index - start);
            dest.push_back(substring);
            start = index + separator.size();
            index = str.find(separator, start);

            if (start == std::string::npos) { break; }
        }
    }
    while (index != std::string::npos);

    //the last part
    substring = str.substr(start);

    if (substring != "")
    { dest.push_back(substring); }

    return dest;
}



//字符串对合并
std::string DBOP::JoinPairStrings(const std::vector<KEY_SUB>& v2)
{
    std::string train;

    for (ULL i = 0; i < v2.size(); i++)
    {
        train += v2[i].first;
        train += "#";
        train += v2[i].second;
        train += "|";
    }

    return train;

}

//字符串对分割
std::vector<KEY_SUB> DBOP::SplitPairStrings(const std::string& s2)
{
    std::vector<KEY_SUB> dest;
    std::string str = s2;
    std::string substring;
    std::string::size_type start1 = 0, index;
    std::string separator = "|";
    std::string separator2 = "#";
    index = str.find_first_of(separator, start1);

    do
    {
        if (index != std::string::npos)
        {
            KEY_SUB piece;
            std::string subsub;
            substring = str.substr(start1, index - start1);

            std::string::size_type start2 = 0;
            std::string::size_type temp;
            temp = substring.find_first_of(separator2, start2);
            subsub = substring.substr(start2, temp - start2);
            piece.first = subsub;
            start2 = temp + separator2.size();
            subsub = substring.substr(start2);
            piece.second = subsub;
            dest.push_back(piece);

            start1 = index + separator.size();
            index = str.find(separator, start1);

            if (start1 == std::string::npos) { break; }
        }
    }
    while (index != std::string::npos);

    //the last part
    substring = str.substr(start1);

    if (substring != "")
    {
        KEY_SUB piece;
        std::string subsub;
        std::string::size_type temp;

        std::string::size_type start2 = 0;
        temp = substring.find_first_of(separator2, start2);
        subsub = substring.substr(start2, temp - start2);
        piece.first = subsub;
        start2 = temp + separator2.size();
        subsub = substring.substr(start2);
        piece.second = subsub;
        dest.push_back(piece);
    }

    return dest;
}


std::vector<KEY_SUB> DBOP::GenerateSubMissions(const string& name,
        const std::vector<std::string>& translators)
{
    std::vector<KEY_SUB> res;

    for (auto translator : translators)
    {
        KEY_SUB temp(name, translator);
        res.push_back(temp);
    }

    return res;
}


//用户存在
bool DBOP::UserExist(const std::string& username)
{
    m_SqlQuery.exec("select count(*) from users where name = "
                    + QString("\"") + QString::fromStdString(username) + QString("\""));
    m_SqlQuery.next();
    int Num = m_SqlQuery.value(0).toInt();

    return (Num > 0) ;
}

//写入用户
bool DBOP::WriteUser(const User& user)
{
    std::string released = JoinStrings(user.m_ReleasedMissions);
    std::string incharge = JoinStrings(user.m_InChargeMissions);
    std::string ptcp = JoinStrings(user.m_ParticipatingMissions);

    if (!m_SqlQuery.exec("INSERT INTO users VALUES("
                         + QString("\"") + QString::fromStdString(user.GetUserName()) + QString("\"") +
                         ", "
                         + QString("\"") + QString::fromStdString(user.GetPassword()) + QString("\"") +
                         ", "
                         + QString::number(user.GetBalance()) + ", "
                         + QString::number(user.GetScore()) + ", "
                         + QString("\"") + QString::fromStdString(user.GetIdNum()) + QString("\"") + ", "
                         + QString("\"") + QString::fromStdString(user.GetRealName()) + QString("\"") +
                         ", "
                         + QString("\"") + QString::fromStdString(user.GetEMail()) + QString("\"") + ", "
                         + QString("\"") + QString::fromStdString(released) + QString("\"") + ", "
                         + QString("\"") + QString::fromStdString(incharge) + QString("\"") + ", "
                         + QString("\"") + QString::fromStdString(ptcp) + QString("\"")
                         + ")"))
    {
        qDebug() << m_SqlQuery.lastError();
        return false;
    }
    else
    {
        return true;
    }
}

//读出用户
bool DBOP::GetUser(const std::string& username, User& user)
{

    m_SqlQuery.exec("select count(*) from users where name = "
                    + QString("\"") + QString::fromStdString(username) + QString("\""));
    m_SqlQuery.next();
    int Num = m_SqlQuery.value(0).toInt();

    if (Num > 0)
    {
        m_SqlQuery.exec("select * from users where name = "
                        + QString("\"") + QString::fromStdString(username) + QString("\"")
                       );
        m_SqlQuery.next();

        QString name = m_SqlQuery.value(0).toString();
        QString password = m_SqlQuery.value(1).toString();
        double balance = m_SqlQuery.value(2).toDouble();
        int score = m_SqlQuery.value(3).toInt();
        QString ID = m_SqlQuery.value(4).toString();
        QString realName = m_SqlQuery.value(5).toString();
        QString email = m_SqlQuery.value(6).toString();

        std::vector<std::string> rel = SplitStrings(m_SqlQuery.value(
                                           7).toString().toStdString());
        std::vector<std::string> incharge = SplitStrings(m_SqlQuery.value(
                                                8).toString().toStdString());
        std::vector<std::string> ptcp = SplitStrings(m_SqlQuery.value(
                                            9).toString().toStdString());


        User temp(name.toStdString(), password.toStdString(), score,
                  realName.toStdString(),
                  ID.toStdString(), email.toStdString());
        temp.Charge(balance);
        temp.m_ReleasedMissions = rel;
        temp.m_InChargeMissions = incharge;
        temp.m_ParticipatingMissions = ptcp;

        user = temp;
        return true;
    }
    else
    {
        return false;
    }

}

//更新用户
bool DBOP::UpdateUser(const User& user)
{
    m_SqlQuery.exec("select count(*) from users where name = "
                    + QString("\"") + QString::fromStdString(user.GetUserName()) + QString("\""));
    m_SqlQuery.next();
    int Num = m_SqlQuery.value(0).toInt();

    if (Num > 0)
    {
        m_SqlQuery.exec("delete from users where name = "
                        + QString("\"") + QString::fromStdString(user.GetUserName()) + QString("\""));

        if (m_SqlQuery.exec())
        {
            return WriteUser(user);
        }
        else
        {
            qDebug() << m_SqlQuery.lastError();
            return false;
        }
    }
    else
    {
        return false;
    }
}
