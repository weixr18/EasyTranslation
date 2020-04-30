#include "mainwindow.h"
#include "ui_start_page.h"
#include <QDebug>


/*时间判断：
1. 1小时内判定有bug
2. 完成Timer部分
3. 完成*/

//快速添加
void MainWindow::debugger()
{
    if(!debuggerClicked)
    {
        debuggerClicked = true;

    Platform c;
    /*******用户注册*******/
/*
    P_USER p_user1 = std::string("");
    c.u_regist(p_user1, "1", "1", 10, "Wei Xinran", "111111","weixr18@mails.tsinghua.edu.cn");

    P_USER p_user2 = std::string("");
    c.u_regist(p_user2, "2", "2", 10, "Wu Yulun", "222222", "wyl18@mails.tsinghua.edu.cn");

    P_USER p_user3 = std::string("");
    c.u_regist(p_user3, "3", "3", 10, "Chen Jikun", "333333", "cjk18@mails.tsinghua.edu.cn");

    P_USER p_user4 = std::string("");
    c.u_regist(p_user4, "4", "4", 10, "Li Xiaohua", "444444", "lxh18@mails.tsinghua.edu.cn");

    P_USER p_user5 = std::string("");
    c.u_regist(p_user5, "5", "5", 10, "Zhang Hong", "555555", "zhanghong18@mails.tsinghua.edu.cn");
*/

    /*******发布任务*******/

    tm time3 = Mission::intToTime(2019, 7, 24, 10, 0);              //一个当前时间之前的时间
    tm time4 = Mission::intToTime(2019, 7, 24, 11, 0);              //一个time3之后，当前时间之前的时间
    tm time1 = Mission::intToTime(2019, 7, 30, 0, 40);              //一个当前时间之后的时间
    tm time2 = Mission::intToTime(2019, 10, 5, 22, 0);               //一个time1之后的时间

    P_USER p_user1 = string("1");
    P_USER p_user2 = string("2");
    P_USER p_user3 = string("3");

 /*   P_MSN p_mission1 = std::string("");
    c.u_release_mission(p_user1, p_mission1, "Halmlet", "A drama of William Shakephere.",
        "To be or Not to be,this is a question.", time1, time2, 200, Mission::English);               //正在招募M的任务


    P_MSN p_mission2 = std::string("");
    c.u_release_mission(p_user1, p_mission2, "Test2", "An introduction of test 2.",
        "A text of test 2.", time3, time2, 200, Mission::English);                                    //判断招募M失败任务

    P_MSN p_mission3 = std::string("");
    c.u_release_mission(p_user1, p_mission3, "Test3", "An introduction of test 3.",
        "A text of test 3.", time3, time2, 200);
    p_mission3->setReleaseState(Mission::R_CANCELED);			//取消任务界面还没写


    P_MSN p_mission4 = std::string("");
    c.u_release_mission(p_user1, p_mission4, "Test4", "An introduction of test 4.",
       "A text of test 4.", time3, time2, 200, Mission::English);
    c.u_apl_manager(p_user2, p_mission4);                                          //判定招募M成功任务
*/

    P_MSN p_mission5_1 = std::string("");
    P_MNG p_mng1_1 = std::string("");
    c.u_release_mission(p_user1, p_mission5_1, "Test5_1", "An introduction of test 5_1.",
        "A text of test 5_1.", time3, time2, 200, Mission::English);
    c.u_apl_manager(p_user2, p_mission5_1);
    p_mission5_1->setReleaseState(Mission::R_CHOOSE_M);  //此处用这句话代替超时判断
    c.r_choose_manager(p_user1, p_mission5_1, p_user2, p_mng1_1);
    c.m_set_recruit_T_time(p_user2, p_mng1_1, time1);                       //正在招募T任务【未加入默认设置】

/*
    P_MSN p_mission5_2 = std::string("");
    P_MNG p_mng2 = std::string("");
    c.u_release_mission(p_user1, p_mission5_2, "Test5_2", "An introduction of test 5_2",
        "A text of test 5_2.", time3, time2, 200, Mission::English);
    c.u_apl_manager(p_user2, p_mission5_2);
    p_mission5_2->setReleaseState(Mission::R_CHOOSE_M);
    c.r_choose_manager(p_user1, p_mission5_2, p_user2, p_mng2);
    c.m_set_recruit_T_time(p_user2, p_mng2, time4);                   //招募T失败任务


    P_MSN pMission5_3 = std::string("");
    P_MNG pMng3 = std::string("");
    c.u_release_mission(p_user4, pMission5_3, "Test5_3",
                        "An introduction of test 5_3.",
                        "This is an apple. I like apples. Apples are good for our health.",
                        time3, time2, 200, Mission::English);
    c.u_apl_manager(p_user2, pMission5_3);
    pMission5_3->setReleaseState(Mission::R_CHOOSE_M);
    c.r_choose_manager(p_user4, pMission5_3, p_user2, pMng3);
    c.u_apl_transltr(p_user3, pMng3);
    c.u_apl_transltr(p_user1, pMng3);
    c.u_apl_transltr(p_user5, pMng3);                                   //招募T成功任务
    pMng3->setManageState(ManageMission::M_CHS_T_AND_ASSIGN); //先用这句话代替时间判断


    P_MSN pMission5_4 = std::string("");
    P_MNG pMng4 = std::string("");
    c.u_release_mission(p_user1, pMission5_4, "Test5_4", "An introduction of test 5_4.",
        "This is an apple. I like apples. Apples are good for our health.",
        time3, time2, 50, Mission::English);
    c.u_apl_manager(p_user2, pMission5_4);
    pMission5_4->setReleaseState(Mission::R_CHOOSE_M);
    c.r_choose_manager(p_user1, pMission5_4, p_user2, pMng4);
    c.u_apl_transltr(p_user3, pMng4);
    c.u_apl_transltr(p_user4, pMng4);
    c.u_apl_transltr(p_user5, pMng4);
    pMng4->setManageState(ManageMission::M_CHS_T_AND_ASSIGN);

    std::vector<P_USER> v1;
    v1.push_back(p_user3);
    v1.push_back(p_user4);
    c.m_choose_tranlator(p_user2, pMng4, v1);

    std::pair<std::string, std::string> p1("3", "This is an apple.");
    std::pair<std::string, std::string> p2("4", "I like apples.");
    std::vector<std::pair<std::string, std::string>> v2;
    v2.push_back(p1);
    v2.push_back(p2);
    c.m_assign_mission(p_user2, pMng4, v2);



    P_MSN pMission5_5 = std::string("");
    P_MNG pMng5 = std::string("");
    c.u_release_mission(p_user1, pMission5_5, "Test5_5", "An introduction of test 5_5.",
        "This is an apple. I like apples. Apples are good for our health.",
        time3, time2, 50, Mission::English);
    c.u_apl_manager(p_user2, pMission5_5);
    pMission5_5->setReleaseState(Mission::R_CHOOSE_M);
    c.r_choose_manager(p_user1, pMission5_5, p_user2, pMng5);
    c.u_apl_transltr(p_user3, pMng5);
    c.u_apl_transltr(p_user4, pMng5);
    c.u_apl_transltr(p_user5, pMng5);
    pMng5->setManageState(ManageMission::M_CHS_T_AND_ASSIGN);

    std::vector<P_USER> v2_1;
    v2_1.push_back(p_user3);
    v2_1.push_back(p_user4);
    c.m_choose_tranlator(p_user2, pMng5, v2_1);

    std::pair<std::string, std::string> p2_1("3", "This is an apple.");
    std::pair<std::string, std::string> p2_2("4", "I like apples.");
    std::vector<std::pair<std::string, std::string>> v2_2;
    v2_2.push_back(p2_1);
    v2_2.push_back(p2_2);
    c.m_assign_mission(p_user2, pMng5, v2_2);


    P_SUB ps2_1(KEY_SUB(pMng5->getMissionName(), p_user3->GetUserName()));
    c.t_submit_translation(p_user3, ps2_1, "hhhhhhh");
    c.m_submit_feedback(p_user2, ps2_1, "OK");
    c.m_accept_translation(p_user2, ps2_1);

    P_SUB ps2_2(KEY_SUB(pMng5->getMissionName(), p_user4->GetUserName()));
    c.t_submit_translation(p_user4, ps2_2, "hahahhahahaha");
    c.m_submit_feedback(p_user2, ps2_2, "OK");
    c.m_accept_translation(p_user2, ps2_2);
    c.m_last_submittal(p_user2, pMng5, "hhhhhhh hahahhahahaha");

    p_user1->Charge(100);
    //c.r_pay_award(p_user1, pMng5);
*/

    qDebug()<<"Q_Datum::allUsers.size()"<<Datum::getUsersSize();
    qDebug()<< "Q_Datum::allMissions.size()"<<Datum::getMissionsSize();
    qDebug()<< "Q_Datum::allMngMissions.size()"<<Datum::getMngMissionsSize();
    qDebug()<< "Q_Datum::allSubMissions.size()"<<Datum::getSubMissionsSize();
    qDebug()<<"Q_user1->releasedMissions.size()"<<p_user1->m_ReleasedMissions.size();

    }
}

