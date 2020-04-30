/*************************************************************************
【文件名】                 message.h
【功能模块和目的】          Message类声明
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/


#ifndef MESSAGE_H
#define MESSAGE_H
#include <string>
#include "time.h"

class Message
{
public:
    Message();
    Message(const Message& m);
    Message(const std::string& sender, const std::string& receiver,
            const std::string& content, tm time, const int ID);
    virtual ~Message();
    Message& operator=(Message& m);

public:
    int GetID() const;
    std::string GetContent() const;
    std::string GetSender() const;
    std::string GetReceiver() const;
    tm GetSendTime() const;
    bool GetReadState() const;
    void setRead();

private:
    int ID{-1};
    std::string content;
    std::string sender;
    std::string receiver;
    tm sendTime;
    bool isRead{false};

};

#endif // MESSAGE_H
