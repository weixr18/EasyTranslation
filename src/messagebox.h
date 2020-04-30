#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <QMainWindow>
#include "Platform.h"

namespace Ui {
class MessageBox;
}

class MessageBox : public QMainWindow
{
    Q_OBJECT

public:
    explicit MessageBox(QWidget *parent = nullptr, P_USER user = nullptr);
    ~MessageBox();

private:
    void TableInitialize();
    void GetUserMessages();

    void ReadMessage();
    void ReadMessageSuccess();

    void ReturnLast();

signals:
    void s_returnLast();

private:
    Ui::MessageBox *ui;
    std::vector<Message> userMessages;
    P_USER user;

};

#endif // MESSAGEBOX_H
