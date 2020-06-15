#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

int dbSetUp(){

    QSqlDatabase database;

    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("./data/MyDataBase.db");
    database.setUserName("ET");
    database.setPassword("easytranslation");

    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
    }
    else
    {

        QSqlQuery sqlQuery;

        //table user
        sqlQuery.exec("CREATE TABLE user("
                      "name varchar(255) PRIMARY KEY,"
                      "password varchar(255),"
                      "balance double,"
                      "score int,"
                      "ID varchar(31),"
                      "realName varchar(255),"
                      "email varchar(255),"
                      "rel text,"
                      "incharge text,"
                      "ptcp text"
                      ")");


        //table mngmissions
        sqlQuery.exec("CREATE TABLE mngmissions("
                      "name varchar(255) PRIMARY KEY,"
                      "releaser varchar(255),"
                      "state int,"
                      "srcLang int,"
                      "tarLang int,"

                      "srcText text,"
                      "introduction text,"
                      "missionDDL varchar(255),"
                      "rcrtM varchar(255),"
                      "award int,"

                      "manager varchar(255),"
                      "Mcandidates text,"
                      "state2 int,"
                      "rcrtT varchar(255),"
                      "Tcandidates text,"

                      "translators text,"
                      "submissions text,"
                      "lastTrans text"
                      ")");

        //table messages
        sqlQuery.exec("CREATE TABLE messages("
                      "name varchar(255) PRIMARY KEY,"
                      "content text,"
                      "sender varchar(255),"
                      "receiver varchar(255),"
                      "sendTime varchar(255)"
                      ")");

        //table submissions
        sqlQuery.exec("CREATE TABLE submissions("
                      "id int PRIMARY KEY,"
                      "translator varchar(255),"
                      "releaser varchar(255),"
                      "srcLang int,"
                      "tarLang int,"

                      "introduction text,"
                      "missionDDL varchar(255),"
                      "manager varchar(255),"
                      "state2 int,"
                      "state3 int"
                      ")");



        //table missions
        sqlQuery.exec("CREATE TABLE missions("
                      "name varchar(255) PRIMARY KEY,"
                      "releaser varchar(255),"
                      "state int,"
                      "srcLang int,"
                      "tarLang int,"
                      "srcText text,"
                      "introduction text,"
                      "missionDDL varchar(255),"
                      "rcrtM varchar(255),"
                      "award int,"
                      "manager varchar(255),"
                      "Mcandidates text"
                      ")");

        //insert
        sqlQuery.exec("INSERT INTO messages VALUES("
                                 + QString::number(0) + ", "
                                 + QString("\"") + QString::fromStdString("hhhhhh") + QString("\"") + ", "
                                 + QString("\"") + QString::fromStdString("_me") + QString("\"") + ", "
                                 + QString("\"") + QString::fromStdString("_you") + QString("\"") + ", "
                                 + QString("\"") + QString::fromStdString("2020-06-15-17:17:00") + QString("\"")
                                 + ")");

    }
    return 0;
}


/*users

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
                         + ")"
*/

/*missions

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
    */

/* mngmissions

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
    */

/* submissions
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

    */

/* messages

            int id = m_SqlQuery.value(0).toInt();
            QString content = m_SqlQuery.value(1).toString();
            QString sender = m_SqlQuery.value(2).toString();
            QString receiver = m_SqlQuery.value(3).toString();
            tm sendTime = Mission::StringToTime(m_SqlQuery.value(4).toString().toStdString());
    */
