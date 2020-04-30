/*************************************************************************
【文件名】                 regist_3.h
【功能模块和目的】          Regist_3类声明
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/

#ifndef REGIST_3_H
#define REGIST_3_H

#include <QMainWindow>
#include <QSqlQuery>
#include "Platform.h"

namespace Ui
{
    class Regist_3;
}

/*************************************************************************
【类名】              Regist_3
【功能】              前端-功能界面-注册页3
【接口说明】
                     1. 构造函数，用于构造界面
                     2. 析构函数
【开发者及日期】      魏欣然 2019/08/01
【更改记录】          无
*************************************************************************/

class Regist_3 : public QMainWindow
{
    Q_OBJECT

public:
    //构造函数
    explicit Regist_3(QWidget* parent = nullptr, std::string name = "",
                      std::string id = "", std::string email = "",
                      std::string reanName = "", std::string password = "");
    //析构函数
    ~Regist_3();

private:
    //注册成功
    void RegistSucceed();
    //返回起始页
    void Scd_ReturnMain();

signals:
    //信号-注册成功
    void s_regSucceed(P_USER user);

private:
    Ui::Regist_3* ui;
    std::string tempName;
    std::string tempID;
    std::string tempRealName;
    std::string tempEmail;
    std::string tempPW;
    int tempScore;
};

#endif // REGIST_3_H
