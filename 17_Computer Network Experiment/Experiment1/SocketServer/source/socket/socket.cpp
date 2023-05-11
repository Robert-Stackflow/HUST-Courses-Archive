#include "socket/socket.h"
#include "QsLog.h"
#include "util/sockethelper.h"
#include <QDebug>
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
Socket::Socket() : socket(-1) {
}
Socket::~Socket() {
    if (this->socket == -1)
        ::closesocket(socket);
    WSACleanup();
}

bool Socket::startup() {
    QLOG_INFO()<<"初始化WinSock服务...";
    if (this->socket != -1)
        return false;
    int flag=SocketHelper::TestWSAStartUp();
    if(flag==1){
        QLOG_FATAL()<<"Winsock初始化错误";
    }else if(flag==2){
        QLOG_FATAL()<<"Winsock版本不支持";
    }
    if ((socket = ::socket(AF_INET, SOCK_STREAM,IPPROTO_TCP)) == -1) {
        WSACleanup();
        return false;
    }
    return true;
}
bool Socket::bind(const char *ip,unsigned short int port) const {
    QLOG_INFO()<<"准备绑定套接字...";
    if (this->socket == -1)
        return false;
    sockaddr_in addr;
    ZeroMemory((char *)&addr, sizeof(sockaddr_in));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    if (ip == nullptr)
        addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
    else
        addr.sin_addr.S_un.S_addr = inet_addr(ip);
    if (::bind(socket, (const sockaddr *)&addr, sizeof(addr)) == SOCKET_ERROR){
        closesocket(socket);
        WSACleanup();
        return false;
    }
    return true;
}


bool Socket::listen(int backlog) {
    QLOG_INFO()<<qUtf8Printable(QString::asprintf("准备监听(最大连接数量为%d)...",backlog));
    if (this->socket == -1)
        return false;
    if (::listen(socket, backlog) == SOCKET_ERROR) {
        closesocket(socket);
        WSACleanup();
        return false;
    }
    return true;
}

bool Socket::connect(const char *ip, unsigned short int port) const {
    if (this->socket == -1)
        return false;
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.S_un.S_addr = inet_addr(ip);
    if (::connect(socket, (const sockaddr*)&addr, sizeof(addr)) == -1)
        return false;
    return true;
}

bool Socket::close() {
    if (this->socket == -1)
        return false;
    ::closesocket(socket);
    socket = -1;
    return true;
}

