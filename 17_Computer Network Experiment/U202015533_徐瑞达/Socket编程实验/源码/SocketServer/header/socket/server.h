#ifndef SERVER_H
#define SERVER_H
#include "socket/request.h"
#pragma once
#include <QObject>
#include "socket.h"
#pragma warning(disable:4290)
class Server :public QObject, public Socket {
    Q_OBJECT
private:
    fd_set rfds;
    fd_set wfds;
    bool success=false;
    SOCKET sessionSocket;
    Request* request=nullptr;
    int _id;
    int clientPort;
    char* clientIp;
    QString addrString;
    bool first_connetion = true;
private:
    void handle200(QString addrString, QString filePath, char *recvBuf);
    void handle400(QString addrString, QString filePath, char *recvBuf);
    void handle404(QString addrString, QString filePath, char *recvBuf);
public:
    Server(const char *ip = NULL,unsigned short int port=5050, int backlog = SOMAXCONN);
    ~Server();
    int start();
    bool close();
    bool isSuccess() const;
signals:
    void requestChanged();
};
#endif // TCPSERVER_H
