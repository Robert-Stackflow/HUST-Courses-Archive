#include "util/sockethelper.h"
#include "util/socketconfig.h"
#include<QDebug>
#include<WinSock2.h>
#include<stdio.h>
#include<QString>
#include<QHostInfo>
#include<QHostAddress>
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
QStringList SocketHelper::getIpList()
{
    QStringList ipList;
    ipList<<"127.0.0.1";
    QString hostName = QHostInfo::localHostName();
    QHostInfo hostInfo = QHostInfo::fromName(hostName);
    QList<QHostAddress> addrList = hostInfo.addresses();
    for(int i=0;i<addrList.count();i++)
        if(QAbstractSocket::IPv4Protocol == addrList.at(i).protocol())
            ipList<<addrList.at(i).toString();
   return ipList;
}
int SocketHelper::TestWSAStartUp()
{
    WSADATA wsaData;
    if (WSAStartup(0x0101, &wsaData))
        return 1;
    if (wsaData.wVersion != 0x0101){
        WSACleanup();
        return 2;
    }
    return 0;
}
void SocketHelper::TestSocket() {
    SOCKET udpSock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    SOCKET tcpSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    Q_UNUSED(udpSock);
    Q_UNUSED(tcpSock);
}
void SocketHelper::TestBind() {
    //绑定SOCKET和主机地址
    SOCKET sServSock = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    //htons 和 htonl 函数把主机字节顺序转换为网络字节顺序，分别用于短整型和长整型数据
    addr.sin_port = htons(5050);
    addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
    addr.sin_port=SocketConfig::getPort();
    qDebug("分配的端口号为%d", addr.sin_port);
    qDebug("主机地址为%lul", addr.sin_addr.S_un.S_addr);
    //必须进行LPSOCKADDR类型转换
    bind(sServSock, (LPSOCKADDR)&addr, sizeof(addr));
}
void SocketHelper::TestAccept() {
    SOCKET sServSock; //服务器监听 socket
    sockaddr_in addr;
    int nSockErr;
    Q_UNUSED(nSockErr);
    int nNumConns = 0; //当前请求连接数
    SOCKET sConns[5]; //会话 SOCKET 数组
    sockaddr ConnAddrs[5];//请求连接的客户端地址
    int nAddrLen;
    //创建服务器监听 socket
    sServSock = socket(AF_INET, SOCK_STREAM, 0);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(5050);
    addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
    if (bind(sServSock, (LPSOCKADDR)&addr, sizeof(addr)) == SOCKET_ERROR)
    {
        nSockErr = WSAGetLastError();
        Q_UNUSED(nSockErr);
        //绑定出错处理
    }
    //监听客户端请求连接
    if (listen(sServSock, 2) == SOCKET_ERROR)
    {
        nSockErr = WSAGetLastError();
        Q_UNUSED(nSockErr);
        //出错处理
    }
    while (nNumConns < 5) {
        //每当收到客户端连接请求，创建新的会话 SOCKET，保存在/ //sConns 数组中
        //客户端地址保存在 ConnAddrs 数组中
        sConns[nNumConns] = accept(sServSock, &ConnAddrs[nNumConns], &nAddrLen);
        if (sConns[nNumConns] == INVALID_SOCKET)
        {
            nSockErr = WSAGetLastError();
            Q_UNUSED(nSockErr);
            //创建会话 SOCKET 出错处理
        }
        else
        {
            //创建会话 SOCKET 成功，启动新的线程与客户端会话
            //StartNewHandlerThread(sConns[nNumConns]);
            //当前请求连接数+1
            nNumConns++;
        }
    }
}
