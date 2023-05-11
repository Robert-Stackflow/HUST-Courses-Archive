#include<iostream>
#include <WinSock2.h>
#include <windows.h>
#include <string>
class Socket {
protected:
    SOCKET socket;
protected:
    Socket();
    ~Socket();
    bool startup();
    bool close();
    bool listen(int backlog);
    bool connectServer( const char *ip,unsigned short int port) const;
    bool bind(const char *ip=nullptr,unsigned short int port=5050) const;
};


