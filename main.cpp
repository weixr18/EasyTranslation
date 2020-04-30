/*************************************************************************
【文件名】                 main.cpp
【功能模块和目的】          main函数
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/


#include "mainwindow.h"
#include <QApplication>
#include <QDebug>


/*************************************************************************
【函数名称】       main
【函数功能】       主函数，程序起点
【参数】
                  int     argc    输入
                  char*   argv[]  输入
【返回值】         无
【开发者及日期】    魏欣然 2019/08/01
【更改记录】       无
*************************************************************************/
int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.setWindowTitle("众包翻译平台");
    w.show();

    return a.exec();
}