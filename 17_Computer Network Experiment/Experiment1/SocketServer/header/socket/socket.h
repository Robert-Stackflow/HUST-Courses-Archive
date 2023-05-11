
#include<iostream>
#include <WinSock2.h>
#include <windows.h>
#include <string>

class Socket {
protected:
    SOCKET socket;
    const int MAXCONNECTION = 5;
    const int MAXRECEIVE = 500;
protected:
    Socket();
    ~Socket();
    bool startup();
    bool close();
    bool listen(int backlog);
    bool connect( const char *ip,unsigned short int port) const;
    bool bind(const char *ip=nullptr,unsigned short int port=8080) const;
    //bool accept(SOCKET &clientSocket) const;
};


