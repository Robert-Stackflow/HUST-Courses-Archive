#include "socket/request.h"
#include<QDateTime>
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
char *Request::getIp() const
{
    return ip;
}

void Request::setIp(char *newIp)
{
    ip = newIp;
}

int Request::getPort() const
{
    return port;
}

void Request::setPort(int newPort)
{
    port = newPort;
}
const QString &Request::getConnTime() const
{
    return connTime;
}

void Request::setConnTime(const QString &newConnTime)
{
    connTime = newConnTime;
}

const QString &Request::getDisconnTime() const
{
    return disconnTime;
}

void Request::setDisconnTime(const QString &newDisconnTime)
{
    disconnTime = newDisconnTime;
}

int Request::getId() const
{
    return id;
}

Request::REQUESTSTATUS Request::getStatus() const
{
    return status;
}
QString Request::getStatusString()
{
    return statusList.at(status);
}

const QString &Request::getFilePath() const
{
    return filePath;
}

void Request::setFilePath(const QString &newFilePath)
{
    filePath = newFilePath;
}

const QString &Request::getPacket() const
{
    return packet;
}

void Request::setPacket(const QString &newPacket)
{
    packet = newPacket;
}
void Request::setStatus(REQUESTSTATUS newStatus)
{
    status = newStatus;
}
Request::Request(int id, char *ip, int port) : id(id),
    ip(ip),
    port(port)
{
    statusList<<"就绪"<<"成功"<<"文件不存在"<<"路径不合法"<<"失败";
    connTime=QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
    status=NORMAL;
}
