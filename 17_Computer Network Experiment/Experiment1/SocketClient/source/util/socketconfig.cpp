#include "util/socketconfig.h"
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#pragma warning(disable:4477)
int SocketConfig::port;
QList<Response*> SocketConfig::responseList;
char SocketConfig::ipAddress[1024]={0};
QString SocketConfig::directory="D:/Ruida/Server";
SocketConfig* SocketConfig::sinstance=nullptr;
SocketConfig& SocketConfig::instace()
{
    if (!sinstance){
        sinstance = new SocketConfig();
        setPort(8080);
        clearIpAddress();
        setDirectory("D:/Ruida/Server");
    }
    return *sinstance;
}
void SocketConfig::deleteInstace()
{
    delete sinstance;
}
int SocketConfig::getPort()
{
    return port;
}
void SocketConfig::setPort(int newPort)
{
    port = newPort;
}
char* SocketConfig::getIpAddress()
{
    return ipAddress;
}
QString SocketConfig::getIpAddressString()
{
    return QString(ipAddress);
}
QString SocketConfig::getAddress()
{
    return QString(getIpAddressString()+":"+QString::number(port));
}
void SocketConfig::clearIpAddress()
{
    memset(ipAddress,0,sizeof(ipAddress));
}
void SocketConfig::setIpAddressString(QString newIpAddress)
{
    memset(ipAddress,0,sizeof(ipAddress));
    sscanf_s(newIpAddress.toUtf8().data(),"%[^:]",ipAddress,sizeof(ipAddress));
}
const QString &SocketConfig::getDirectory()
{
    return directory;
}
void SocketConfig::setDirectory(const QString &newDirectory)
{
    directory = newDirectory;
}
