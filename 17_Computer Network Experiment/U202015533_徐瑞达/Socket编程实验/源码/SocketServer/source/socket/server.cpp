#include "socket/server.h"
#include "qdir.h"
#include "widget/floatbox.h"
#include "socket/request.h"
#include "util/socketconfig.h"
#include"util/httphelper.h"
#include "QsLog.h"
#include<fstream>
#include<QDebug>
#include <Ws2tcpip.h>
#include<windows.h>
#include<sys/stat.h>
#define BUFFER_SIZE 1024
#pragma warning(disable:4700)
#pragma warning(disable:4267)
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
Server::Server( const char *ip,unsigned short int port, int backlog):success(false)
{
    if (!startup()){
        QLOG_FATAL()<<"Socket创建失败";
        return;
    }
    if (!bind(ip,port)) {
        QLOG_FATAL()<<"Socket绑定失败";
        return;
    }
    if (!listen(backlog)) {
        QLOG_FATAL()<<"Socket监听失败";
        return;
    }
    success=true;
    QLOG_INFO()<<"Socket初始化成功";
};
int Server::start() {
    int rtn;
    char recvBuf[4096];
    u_long blockMode = 1;
    SOCKADDR_IN clientAddr;
    int addrLen = sizeof(clientAddr);
    if ((rtn = ioctlsocket(socket, FIONBIO, &blockMode) == SOCKET_ERROR)) {
        QLOG_ERROR()<<"ioctlsocket()运行失败";
        return false;
    }
    while(true)
    {
        FD_ZERO(&rfds);
        FD_ZERO(&wfds);
        FD_SET(socket, &rfds);
        if(!first_connetion){
            if (sessionSocket != INVALID_SOCKET) {
                FD_SET(sessionSocket, &rfds);
                FD_SET(sessionSocket, &wfds);
            }
        }
        int nTotal = select(0, &rfds, &wfds, NULL, NULL);
        if (FD_ISSET(socket, &rfds)) {
            nTotal--;
            clientPort = ntohs(clientAddr.sin_port);
            clientIp = inet_ntoa(clientAddr.sin_addr);
            addrString=QString::asprintf("[%s:%d]",clientIp,clientPort);
            QLOG_INFO()<<qUtf8Printable("监听到来自"+addrString+"的用户请求");
            sessionSocket = accept(socket, (LPSOCKADDR)&clientAddr, &addrLen);
            if (sessionSocket != INVALID_SOCKET){
                QLOG_INFO()<<qUtf8Printable("成功为用户"+addrString+"建立会话Socket");
            }else{
                if(request){
                    request->setStatus(Request::FAIL);
                    emit requestChanged();
                }
                QLOG_ERROR()<<qUtf8Printable("为用户"+addrString+"建立会话Socket失败");
            }
            Q_UNUSED(rtn)
            if ((rtn = ioctlsocket(sessionSocket, FIONBIO, &blockMode) == SOCKET_ERROR)) {
                QLOG_ERROR()<<"ioctlsocket()运行失败";
                if(request){
                    request->setStatus(Request::FAIL);
                    emit requestChanged();
                }
                return false;
            }
            FD_SET(sessionSocket, &rfds);
            FD_SET(sessionSocket, &wfds);
            first_connetion = false;
        }
        if (nTotal > 0) {
            if (FD_ISSET(sessionSocket, &rfds)) {
                memset(recvBuf, '\0', 4096);
                rtn = recv(sessionSocket, recvBuf, 4096, 0);
                QLOG_DEBUG()<<"接收到HTTP请求报文:\n"<<rtn;
                if (rtn > 0){
                    FILE *fp;
                    QString relativeFilePath=HttpHelper::getFilePath(recvBuf);
                    QString filePath=SocketConfig::getDirectory()+relativeFilePath;
                    fopen_s(&fp,filePath.toUtf8().data(), "rb");
                    if(fp!=nullptr)
                        handle200(addrString,filePath,recvBuf);
                    else if(HttpHelper::getFilePath(recvBuf)==nullptr)
                        handle400(addrString,relativeFilePath,recvBuf);
                    else if(fp==nullptr)
                        handle404(addrString,relativeFilePath,recvBuf);
                }else{
                    nTotal--;
                    closesocket(sessionSocket);
                    sessionSocket = INVALID_SOCKET;
                    QLOG_INFO()<<qUtf8Printable("客户端"+addrString+"断开连接...");
                }
            }
        }
    }
    closesocket(socket);
    WSACleanup();
    return 0;
}
void Server::handle404(QString addrString,QString filePath,char* recvBuf)
{
    FILE* fp = nullptr;
    char response404[200];
    char buffer[BUFFER_SIZE];
    if(request==nullptr){
        _id=SocketConfig::getRequestList().size();
        SocketConfig::getRequestList().append(new Request(_id,clientIp,clientPort));
        request=SocketConfig::getRequestList().at(_id);
        emit requestChanged();
        request->setStatus(Request::NOTEXIST);
        request->setFilePath(filePath);
        request->setPacket(recvBuf);
        emit requestChanged();
    }
    QString filePath404=SocketConfig::getDirectory()+"/404.html";
    fopen_s(&fp,filePath404.toUtf8().data(), "rb");
    if (fp!=nullptr)
    {
        struct stat statbuf;
        stat(filePath404.toUtf8().data(),&statbuf);
        QString str=HttpHelper::getResponse404(filePath404,statbuf.st_size);
        strcpy_s(response404,HttpHelper::getResponse404(filePath404,statbuf.st_size));
        QLOG_WARN()<<qUtf8Printable("未找到来自"+addrString+"的文件请求"+filePath+"对应的文件");
        if (send(sessionSocket,response404,str.size(), 0) < 0){
            QLOG_WARN()<<qUtf8Printable("向客户端"+addrString+"发送响应[文件不存在]失败");
        }
        memset(buffer, 0, BUFFER_SIZE);
        int length = 0;
        while ((length = fread(buffer, sizeof(char), BUFFER_SIZE, fp)) > 0){
            if (send(sessionSocket, buffer, length, 0) < 0){
                QLOG_ERROR()<<qUtf8Printable("向客户端"+addrString+"发送404页面失败");
                break;
            }
            memset(buffer, 0, BUFFER_SIZE);
        }
        fclose(fp);
    }
    request=nullptr;
}
void Server::handle400(QString addrString,QString filePath, char *recvBuf)
{
    FILE* fp = nullptr;
    char response400[200];
    char buffer[BUFFER_SIZE];
    if(request==nullptr){
        _id=SocketConfig::getRequestList().size();
        SocketConfig::getRequestList().append(new Request(_id,clientIp,clientPort));
        request=SocketConfig::getRequestList().at(_id);
        emit requestChanged();
        request->setStatus(Request::INVALID);
        request->setFilePath(filePath);
        request->setPacket(recvBuf);
        emit requestChanged();
    }
    QString filePath400=SocketConfig::getDirectory()+"/400.html";
    fopen_s(&fp,filePath400.toUtf8().data(), "rb");
    if (fp!=nullptr)
    {
        struct stat statbuf;
        stat(filePath400.toUtf8().data(),&statbuf);
        QString str=HttpHelper::getResponse400(filePath400,statbuf.st_size);
        strcpy_s(response400,HttpHelper::getResponse400(filePath400,statbuf.st_size));
        send(sessionSocket,response400,str.size(), 0);
        memset(buffer, 0, BUFFER_SIZE);
        int length = 0;
        while ((length = fread(buffer, sizeof(char), BUFFER_SIZE, fp)) > 0)
        {
            if (send(sessionSocket, buffer, length, 0) < 0)
                break;
            memset(buffer, 0, BUFFER_SIZE);
        }
        fclose(fp);
    }
    request=nullptr;
}
void Server::handle200(QString addrString, QString filePath, char *recvBuf)
{
    FILE* fp = nullptr;
    char response200[200];
    char buffer[BUFFER_SIZE];
    if(request==nullptr){
        _id=SocketConfig::getRequestList().size();
        SocketConfig::getRequestList().append(new Request(_id,clientIp,clientPort));
        request=SocketConfig::getRequestList().at(_id);
        request->setStatus(Request::SUCCESS);
        request->setFilePath(filePath);
        request->setPacket(recvBuf);
        emit requestChanged();
    }
    fopen_s(&fp,filePath.toUtf8().data(), "rb");
    QLOG_INFO()<<qUtf8Printable("监听到来自"+addrString+"的文件请求:"+filePath);
    if (fp!=nullptr)
    {
        struct stat statbuf;
        int ret = stat(filePath.toUtf8().data(),&statbuf);
        if(ret != 0)
            QLOG_WARN()<<qUtf8Printable("获取文件"+filePath+"字节数失败");
        else
            QLOG_INFO()<<qUtf8Printable("待发送文件"+filePath+"的字节数为"+QString::number(statbuf.st_size));
        QString str=HttpHelper::getResponse200(filePath,statbuf.st_size);
        strcpy_s(response200,HttpHelper::getResponse200(filePath,statbuf.st_size));
        if (send(sessionSocket,response200,str.size(), 0) < 0){
            QLOG_WARN()<<qUtf8Printable("向客户端"+addrString+"发送响应[文件就绪]失败");
        }
        memset(buffer, 0, BUFFER_SIZE);
        int length = 0;
        while ((length = fread(buffer, sizeof(char), BUFFER_SIZE, fp)) > 0)
        {
            if (send(sessionSocket, buffer, length, 0) < 0){
                QLOG_ERROR()<<qUtf8Printable("向客户端"+addrString+"发送文件"+filePath+"失败");
                request->setStatus(Request::FAIL);
                emit requestChanged();
                request=nullptr;
                fclose(fp);
                return;
            }
            memset(buffer, 0, BUFFER_SIZE);
        }
        fclose(fp);
    }
    QLOG_INFO()<<qUtf8Printable("向客户端"+addrString+"发送文件"+filePath+"成功");
    request=nullptr;
}
bool Server::close(){
    closesocket(socket);
    WSACleanup();
    QLOG_INFO()<<"Socket连接关闭";
    return true;
}
Server::~Server() {
};
bool Server::isSuccess() const
{
    return success;
}
