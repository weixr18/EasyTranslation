/*************************************************************************
【文件名】                 stateupdateW.h
【功能模块和目的】          StateUpdateW类声明
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/


#ifndef STATEUPDATEW_H
#define STATEUPDATEW_H
#include <Platform.h>
#include <QMainWindow>

namespace Ui
{
    class StateUpdateW;
}

/*************************************************************************
【类名】              StateUpdateW
【功能】              前端-刷新组件
【接口说明】
                     1. 构造函数
                     2. 析构函数
                     3. checkAndUpdate1 检查所有发布阶段任务 设置计时器
                     4. checkAndUpdate2 检查所有负责阶段任务 设置计时器
【开发者及日期】      魏欣然 2019/08/01
【更改记录】          无
*************************************************************************/

class StateUpdateW : public QMainWindow
{
    Q_OBJECT

public:
    //构造函数
    explicit StateUpdateW(QWidget* parent = nullptr);
    //析构函数
    ~StateUpdateW();

public:
    //检查发布阶段任务并设置定时器
    void CheckAndUpdate1();
    //检查负责阶段任务并设置定时器
    void CheckAndUpdate2();

private:
    //定时器响应，根据任务阶段判断应该如何处理
    void CheckMsnTime();
    //判断t1是否超过t2
    static bool TimeOut(tm t1, tm t2);
    //判断t1在1小时内是否超过t2
    static bool TimeNearOut(tm current, tm DDL);
    //给时间+1h
    static tm TimePlusHour(const tm& t);
    //计算t1和t2之间的时间差以毫秒为单位
    static int TimeIntervalMs(tm t1, tm t2);

signals:
    //信号-计时器到时间啦
    void s_timeUp();

private:
    Ui::StateUpdateW* ui;
};

#endif // STATEUPDATEW_H
