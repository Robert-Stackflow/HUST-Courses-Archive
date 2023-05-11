#ifndef CLIENT_H
#define CLIENT_H
#pragma once
#include <QString>
#include <QObject>
#include <list>
#include "socket.h"
#include "exception.h"
#pragma warning(disable:4290)
class Client : public QObject,Socket {
    Q_OBJECT
public:
    Client(const char *ip = NULL,unsigned short int port=5050,int backlog = SOMAXCONN);
    ~Client();
    int start();
    bool close();
    bool isSuccess() const;
    void sendFile(const QString&filepath);
    void sendMessage(const QString &message);
private:
    QString message;
    QString filepath;
    bool success=false;
    bool isSendFile =false;
    bool isSendMessage =false;
signals:
    void fileChanged();
};
#endif // TCPSERVER_H
