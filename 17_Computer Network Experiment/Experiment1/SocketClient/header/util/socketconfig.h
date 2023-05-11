#ifndef SOCKETCONFIG_H
#define SOCKETCONFIG_H
#include "socket/response.h"
#include<QString>
class SocketConfig
{
private:
    static int port;
    static char ipAddress[1024];
    static QString directory;
    static SocketConfig* sinstance;
public:
    static QList<Response*> responseList;
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
};
#endif // SOCKETCONFIG_H
