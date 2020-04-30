/*************************************************************************
【文件名】                 DBOP2.cpp
【功能模块和目的】          DBOP类实现-PART II
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/

#include "DBOP.h"


//任务存在
bool DBOP::MissionExist(const std::string& name)
{
    m_SqlQuery.exec("select count(*) from missions where name = "
                    + QString("\"") + QString::fromStdString(name) + QString("\""));
    m_SqlQuery.next();
    int Num = m_SqlQuery.value(0).toInt();

    return (Num > 0);
}

//写入任务
bool DBOP::WriteMission(const Mission& mission)
{
    std::string mngCandidates = JoinStrings(mission.m_MngCandidates);

    if (!m_SqlQuery.exec("INSERT INTO missions VALUES("
                         + QString("\"") + QString::fromStdString(mission.GetMissionName()) +
                         QString("\"") + ", "
                         + QString("\"") + QString::fromStdString(mission.GetReleaser()) + QString("\"")
                         + ", "
                         + QString::number(mission.GetReleaseState()) + ", "
                         + QString::number(mission.GetSrcLanguage()) + ", "
                         + QString::number(mission.GetTarLanguage()) + ", "
                         + QString("\"") + QString::fromStdString(mission.GetSrcText()) + QString("\"") +
                         ", "
                         + QString("\"") + QString::fromStdString(mission.GetIntroduction()) +
                         QString("\"") + ", "
                         + QString("\"") + QString::fromStdString(Mission::TimeToString(
                                     mission.GetMissionDDL())) + QString("\"") + ", "
                         + QString("\"") + QString::fromStdString(Mission::TimeToString(
                                     mission.GetRecruitMTime())) + QString("\"") + ", "
                         + QString::number(mission.GetAwardAmount()) + ", "
                         + QString("\"") + QString::fromStdString(mission.GetManager()) + QString("\"") +
                         ", "
                         + QString("\"") + QString::fromStdString(mngCandidates) + QString("\"")
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

//读出任务
bool DBOP::GetMission(const std::string& missionName, Mission& mission)
{
    m_SqlQuery.exec("select count(*) from missions where name = "
                    + QString("\"") + QString::fromStdString(missionName) + QString("\""));
    m_SqlQuery.next();
    int Num = m_SqlQuery.value(0).toInt();

    if (Num > 0)
    {
        m_SqlQuery.exec("select * from missions where name = "
                        + QString("\"") + QString::fromStdString(missionName) + QString("\"")
                       );
        m_SqlQuery.next();

        QString name = m_SqlQuery.value(0).toString();
        QString releaser = m_SqlQuery.value(1).toString();
        Mission::ReleaseState state = Mission::IntToReleaseState(m_SqlQuery.value(
                                          2).toInt());
        Mission::Language srcLang = Mission::IntToLanguage(m_SqlQuery.value(3).toInt());
        Mission::Language tarLang = Mission::IntToLanguage(m_SqlQuery.value(4).toInt());

        QString srcText = m_SqlQuery.value(5).toString();
        QString introduction = m_SqlQuery.value(6).toString();
        tm missionDDL = Mission::StringToTime(m_SqlQuery.value(
                7).toString().toStdString());
        tm rcrtM = Mission::StringToTime(m_SqlQuery.value(8).toString().toStdString());
        int award = m_SqlQuery.value(9).toInt();

        QString manager = m_SqlQuery.value(10).toString();
        std::vector<std::string> Mcandidates = SplitStrings(m_SqlQuery.value(
                11).toString().toStdString());

        Mission temp(name.toStdString(), releaser.toStdString(),
                     introduction.toStdString(),
                     srcText.toStdString(), rcrtM, missionDDL, award, state, srcLang, tarLang);
        temp.m_MngCandidates = Mcandidates;
        temp.SetManager(manager.toStdString());

        mission = temp;
        return true;
    }
    else
    {
        return false;
    }
}

//更新任务
bool DBOP::UpdateMission(const Mission& mission)
{
    m_SqlQuery.exec("select count(*) from missions where name = "
                    + QString("\"") + QString::fromStdString(mission.GetMissionName()) +
                    QString("\""));
    m_SqlQuery.next();
    int Num = m_SqlQuery.value(0).toInt();

    if (Num > 0)
    {
        m_SqlQuery.exec("delete from missions where name = "
                        + QString("\"") + QString::fromStdString(mission.GetMissionName()) +
                        QString("\""));

        if (m_SqlQuery.exec())
        {
            return WriteMission(mission);
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



//任务转换
bool DBOP::MissionTransferMng(const ManageMission& mng)
{
    std::string name = mng.GetMissionName();

    if (MngMissionExist(name))
    {
        return false;
    }

    if (!MissionExist(name))
    {
        return false;
    }

    m_SqlQuery.exec("delete from missions where name = "
                    + QString("\"") + QString::fromStdString(name) + QString("\""));

    if (m_SqlQuery.exec())
    {
        qDebug() << "Transfered!";
        return WriteMngMission(mng);
    }
    else
    {
        qDebug() << m_SqlQuery.lastError();
        return false;
    }

}



//mng任务存在
bool DBOP::MngMissionExist(const std::string& name)
{
    m_SqlQuery.exec("select count(*) from mngmissions where name = "
                    + QString("\"") + QString::fromStdString(name) + QString("\""));
    m_SqlQuery.next();
    int Num = m_SqlQuery.value(0).toInt();

    return (Num > 0);
}

//写入mng任务
bool DBOP::WriteMngMission(const ManageMission& mng)
{
    std::string mngCandidates = JoinStrings(mng.m_MngCandidates);
    std::string trslCandidates = JoinStrings(mng.m_TrsltrCandidates);
    std::string translators = JoinStrings(mng.m_Translators);

    if (!m_SqlQuery.exec("INSERT INTO mngmissions VALUES("
                         /*0*/
                         + QString("\"") + QString::fromStdString(
                             mng.GetMissionName()) + QString("\"") + ", "
                         + QString("\"") + QString::fromStdString(mng.GetReleaser()) + QString("\"") +
                         ", "
                         + QString::number(mng.GetReleaseState()) + ", "
                         + QString::number(mng.GetSrcLanguage()) + ", "
                         + QString::number(mng.GetTarLanguage()) + ", "
                         /*5*/
                         + QString("\"") + QString::fromStdString(mng.GetSrcText()) + QString("\"") +
                         ", "
                         + QString("\"") + QString::fromStdString(
                             mng.GetIntroduction()) + QString("\"") + ", "
                         + QString("\"") + QString::fromStdString(Mission::TimeToString(
                                     mng.GetMissionDDL())) + QString("\"") + ", "
                         + QString("\"") + QString::fromStdString(Mission::TimeToString(
                                     mng.GetRecruitMTime())) + QString("\"") + ", "
                         + QString::number(mng.GetAwardAmount()) + ", "
                         /*10*/
                         + QString("\"") + QString::fromStdString(mng.GetManager()) + QString("\"") +
                         ", "
                         + QString("\"") + QString::fromStdString(
                             mngCandidates) + QString("\"") + ", "
                         + QString::number(mng.GetManageState()) + ", "
                         + QString("\"") + QString::fromStdString(Mission::TimeToString(
                                     mng.GetRecruitTTime())) + QString("\"") + ", "
                         + QString("\"") + QString::fromStdString(trslCandidates) + QString("\"") + ", "
                         /*15*/
                         + QString("\"") + QString::fromStdString(translators) + QString("\"") + ", "
                         + QString("\"") + QString::fromStdString(
                             mng.GetLastTranslation()) + QString("\"")
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

//读出mng任务
bool DBOP::GetMngMission(const std::string& name, ManageMission& mng)
{
    m_SqlQuery.exec("select count(*) from mngmissions where name = "
                    + QString("\"") + QString::fromStdString(name) + QString("\""));
    m_SqlQuery.next();
    int Num = m_SqlQuery.value(0).toInt();

    if (Num > 0)
    {
        m_SqlQuery.exec("select * from mngmissions where name = "
                        + QString("\"") + QString::fromStdString(name) + QString("\"")
                       );
        m_SqlQuery.next();

        QString name = m_SqlQuery.value(0).toString();
        QString releaser = m_SqlQuery.value(1).toString();
        Mission::ReleaseState state = Mission::IntToReleaseState(m_SqlQuery.value(
                                          2).toInt());
        Mission::Language srcLang = Mission::IntToLanguage(m_SqlQuery.value(3).toInt());
        Mission::Language tarLang = Mission::IntToLanguage(m_SqlQuery.value(4).toInt());

        QString srcText = m_SqlQuery.value(5).toString();
        QString introduction = m_SqlQuery.value(6).toString();
        tm missionDDL = Mission::StringToTime(m_SqlQuery.value(
                7).toString().toStdString());
        tm rcrtM = Mission::StringToTime(m_SqlQuery.value(8).toString().toStdString());
        int award = m_SqlQuery.value(9).toInt();

        QString manager = m_SqlQuery.value(10).toString();
        std::vector<std::string> Mcandidates = SplitStrings(m_SqlQuery.value(
                11).toString().toStdString());
        ManageMission::ManageState state2 = ManageMission::IntToManageState(
                                                m_SqlQuery.value(12).toInt());
        tm rcrtT = Mission::StringToTime(m_SqlQuery.value(13).toString().toStdString());
        std::vector<std::string> Tcandidates = SplitStrings(m_SqlQuery.value(
                14).toString().toStdString());

        std::vector<std::string> translators = SplitStrings(m_SqlQuery.value(
                15).toString().toStdString());
        std::vector<KEY_SUB> submissions = GenerateSubMissions(name.toStdString(),
                                           translators);
        QString lastTrans = m_SqlQuery.value(16).toString();


        Mission temp(name.toStdString(), releaser.toStdString(),
                     introduction.toStdString(),
                     srcText.toStdString(), rcrtM, missionDDL, award, state, srcLang, tarLang);
        temp.m_MngCandidates = Mcandidates;
        temp.SetManager(manager.toStdString());

        ManageMission mngt(temp);
        mngt.SetManageState(state2);
        mngt.SetRecruitTTime(rcrtT);
        mngt.m_TrsltrCandidates = Tcandidates;
        mngt.m_Translators = translators;
        mngt.m_SubMissions = submissions;
        mngt.SetLastTranslation(lastTrans.toStdString());

        mng = mngt;
        return true;

    }
    else
    {
        return false;
    }
}

//更新mng任务
bool DBOP::UpdateMngMission(const ManageMission& mng)
{
    m_SqlQuery.exec("select count(*) from mngmissions where name = "
                    + QString("\"") + QString::fromStdString(mng.GetMissionName()) + QString("\""));
    m_SqlQuery.next();
    int Num = m_SqlQuery.value(0).toInt();

    if (Num > 0)
    {
        m_SqlQuery.exec("delete from mngmissions where name = "
                        + QString("\"") + QString::fromStdString(mng.GetMissionName()) + QString("\""));

        if (m_SqlQuery.exec())
        {
            return WriteMngMission(mng);
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


//子任务存在
bool DBOP::SubMissionExist(const KEY_SUB key)
{
    m_SqlQuery.exec("select count(*) from submissions where name = "
                    + QString("\"") + QString::fromStdString(key.first) + QString("\"")
                    + "and translator = "
                    + QString("\"") + QString::fromStdString(key.second) + QString("\"") );
    m_SqlQuery.next();
    int Num = m_SqlQuery.value(0).toInt();

    return (Num > 0);
}

//写入子任务
bool DBOP::WriteSubMission(const SubMission& sub)
{
    std::string histories = JoinPairStrings(sub.m_History);

    if (!m_SqlQuery.exec("INSERT INTO submissions VALUES("
                         /*0*/
                         + QString("\"") + QString::fromStdString(
                             sub.GetMissionName()) + QString("\"") + ", "
                         + QString("\"") + QString::fromStdString(sub.GetTranslator()) + QString("\"") +
                         ", "
                         + QString("\"") + QString::fromStdString(sub.GetReleaser()) + QString("\"") +
                         ", "
                         + QString::number(sub.GetSrcLanguage()) + ", "
                         + QString::number(sub.GetTarLanguage()) + ", "

                         /*5*/
                         + QString("\"") + QString::fromStdString(sub.GetIntroduction()) + QString("\"")
                         + ", "
                         + QString("\"") + QString::fromStdString(Mission::TimeToString(
                                     sub.GetMissionDDL())) + QString("\"") + ", "
                         + QString("\"") + QString::fromStdString(sub.GetManager()) + QString("\"") +
                         ", "
                         + QString::number(sub.GetManageState()) + ", "
                         + QString::number(sub.GetSubMissionState()) + ", "

                         /*10*/
                         + QString("\"") + QString::fromStdString(sub.GetSrcSubText()) + QString("\"") +
                         ", "
                         + QString("\"") + QString::fromStdString(
                             histories) + QString("\"") + ", "
                         + QString("\"") + QString::fromStdString(sub.GetTranslation()) + QString("\"")
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

//读出子任务
bool DBOP::GetSubMission(const KEY_SUB key, SubMission& sub)
{
    m_SqlQuery.exec("select count(*) from submissions where name = "
                    + QString("\"") + QString::fromStdString(key.first) + QString("\"")
                    + "and translator = "
                    + QString("\"") + QString::fromStdString(key.second) + QString("\"") );
    m_SqlQuery.next();
    int Num = m_SqlQuery.value(0).toInt();

    if (Num > 0)
    {
        m_SqlQuery.exec("select * from submissions where name = "
                        + QString("\"") + QString::fromStdString(key.first) + QString("\"")
                        + "and translator = "
                        + QString("\"") + QString::fromStdString(key.second) + QString("\"") );
        m_SqlQuery.next();

        QString name = m_SqlQuery.value(0).toString();
        QString translator = m_SqlQuery.value(1).toString();
        QString releaser = m_SqlQuery.value(2).toString();
        Mission::Language srcLang = Mission::IntToLanguage(m_SqlQuery.value(3).toInt());
        Mission::Language tarLang = Mission::IntToLanguage(m_SqlQuery.value(4).toInt());

        QString introduction = m_SqlQuery.value(5).toString();
        tm missionDDL = Mission::StringToTime(m_SqlQuery.value(
                6).toString().toStdString());
        QString manager = m_SqlQuery.value(7).toString();
        ManageMission::ManageState state2 = ManageMission::IntToManageState(
                                                m_SqlQuery.value(8).toInt());
        SubMission::SubMissionState state3 = SubMission::IntToSubMissionState(
                m_SqlQuery.value(9).toInt());

        QString srcSubtext = m_SqlQuery.value(10).toString();
        std::vector<KEY_SUB> history = SplitPairStrings(m_SqlQuery.value(
                                           11).toString().toStdString());
        QString translation = m_SqlQuery.value(12).toString();


        SubMission s1(name.toStdString(), translator.toStdString(),
                      releaser.toStdString(),
                      srcLang, tarLang, introduction.toStdString(), missionDDL,
                      manager.toStdString(), state2, state3,
                      srcSubtext.toStdString(), history, translation.toStdString());

        sub = s1;
        return true;
    }
    else
    {
        return false;
    }
}

//更新子任务
bool DBOP::UpdateSubMission(const SubMission& sub)
{
    m_SqlQuery.exec("select count(*) from submissions where name = "
                    + QString("\"") + QString::fromStdString(sub.GetMissionName()) + QString("\"")
                    + "and translator = "
                    + QString("\"") + QString::fromStdString(sub.GetTranslator()) + QString("\"") );
    m_SqlQuery.next();
    int Num = m_SqlQuery.value(0).toInt();

    if (Num > 0)
    {
        m_SqlQuery.exec("delete from submissions where name = "
                        + QString("\"") + QString::fromStdString(sub.GetMissionName()) + QString("\"")
                        + "and translator = "
                        + QString("\"") + QString::fromStdString(sub.GetTranslator()) + QString("\"") );

        if (m_SqlQuery.exec())
        {
            return WriteSubMission(sub);
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


//消息存在
bool DBOP::MessageExist(const int id)
{
    m_SqlQuery.exec("select count(*) from messages where id = "
                    + QString::number(id));
    m_SqlQuery.next();
    int Num = m_SqlQuery.value(0).toInt();

    return (Num > 0);
}


//写入消息
bool DBOP::WriteMessage(const Message &message)
{
    if (!m_SqlQuery.exec("INSERT INTO messages VALUES("
                         + QString::number(message.GetID()) + ", "
                         + QString("\"") + QString::fromStdString(message.GetContent()) + QString("\"") + ", "
                         + QString("\"") + QString::fromStdString(message.GetSender()) + QString("\"") + ", "
                         + QString("\"") + QString::fromStdString(message.GetReceiver()) + QString("\"") + ", "
                         + QString("\"") + QString::fromStdString(Mission::TimeToString(
                                     message.GetSendTime())) + QString("\"")
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


//读出消息
bool DBOP::GetMessage(const int id, Message& message)
{
    if (MessageExist(id))
    {
        m_SqlQuery.exec("select * from messages where id = "
                        + QString::number(id));
        m_SqlQuery.next();

        int id = m_SqlQuery.value(0).toInt();
        QString content = m_SqlQuery.value(1).toString();
        QString sender = m_SqlQuery.value(2).toString();
        QString receiver = m_SqlQuery.value(3).toString();
        tm sendTime = Mission::StringToTime(m_SqlQuery.value(4).toString().toStdString());

        Message msg1(sender.toStdString(), receiver.toStdString(),
                     content.toStdString(), sendTime, id);

        message = msg1;
        return true;
    }
    else
    {
        return false;
    }
}


//删除消息
bool DBOP::DeleteMessage(const int id)
{
    if (MessageExist(id))
    {
        m_SqlQuery.exec("delete from messages where id = "
                        + QString::number(id));

        if (m_SqlQuery.exec())
        {
            return true;
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


