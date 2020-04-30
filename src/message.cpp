/*************************************************************************
【文件名】                 message.cpp
【功能模块和目的】          Message类实现
【开发者及日期】            魏欣然 2019/08/01
【更改记录】               无
*************************************************************************/

#include <iostream>
#include "message.h"

Message::Message():
    ID(-1)
{}


Message::~Message()
{}

Message::Message(const Message& m):
    ID(m.ID),
    content(m.content),
    sender(m.sender),
    receiver(m.receiver),
    sendTime(m.sendTime),
    isRead(m.isRead)
{}


Message::Message(const std::string& sender, const std::string& receiver,
                 const std::string& content, tm time, const int ID):
    ID(ID),
    content(content),
    sender(sender),
    receiver(receiver),
    sendTime(time)
{}


Message& Message::operator=(Message& m)
{
    if (ID == -1)
    {
        ID = m.ID;
        content = m.content;
        sender = m.sender;
        receiver = m.receiver;
        sendTime = m.sendTime;
        isRead = m.isRead;
    }
    return *this;
}

int Message::GetID() const
{
    return this->ID;
}

std::string Message::GetSender() const
{
    return this->sender;
}

std::string Message::GetReceiver() const
{
    return this->receiver;
}


std::string Message::GetContent() const
{
    return this->content;
}

tm Message::GetSendTime() const
{
    return this->sendTime;
}

bool Message::GetReadState() const
{
    return this->isRead;
}

void Message::setRead()
{
    this->isRead = true;
}



