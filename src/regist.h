/*************************************************************************
【文件名】                 regist.h
【功能模块和目的】          Regist类声明
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/

#ifndef REGIST_H
#define REGIST_H

#include <QMainWindow>
#include <QPushButton>
#include <QString>
#include <QMessageBox>
#include "regist_2.h"

namespace Ui
{
    class Regist;
}

/*************************************************************************
【类名】              Regist
【功能】              前端-功能界面-注册页1
【接口说明】
                     1. 构造函数，用于构造界面
                     2. 析构函数
【开发者及日期】      魏欣然 2019/08/01
【更改记录】          无
*************************************************************************/

class Regist : public QMainWindow
{
    Q_OBJECT

public:
    //构造函数
    explicit Regist(QWidget* parent = nullptr);
    //析构函数
    ~Regist();

private:
    //继续注册
    void ConTinueReg();
    //注册成功
    void RegSucceed(P_USER user);

    bool FormatCheckPass();

private slots:
    //取消注册
    void on_cancel_clicked();

signals:
    //信号-取消注册
    void s_regCancel();
    //信号-注册成功
    void s_regSucceed(P_USER user);

private:
    Ui::Regist* ui;
    Regist_2* nxtpge;
    std::string tempName;
    std::string tempID;
    std::string tempRealName;
    std::string tempEmail;
};


#endif // REGIST_H
