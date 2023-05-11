#ifndef SOCKETCONFIG_H
#define SOCKETCONFIG_H
#include"socket/request.h"
#include<QString>
#include<QList>
class SocketConfig
{
private:
    static QList<Request*> requestList;
    static int port;
    static char ipAddress[1024];
    static QString directory;
    static SocketConfig* sinstance;
public:
    static SocketConfig& instace();
    static void deleteInstace();
    static int getPort();
    static void setPort(int newPort);
    static char *getIpAddress();
    static QString getIpAddressString();
    static QString getAddress();
    static void clearIpAddress();
    static void setIpAddressString(QString newIpAddress);
    static const QString &getDirectory();
    static void setDirectory(const QString &newDirectory);
public:
    static  QList<Request *> &getRequestList();
};
#endif // SOCKETCONFIG_H
