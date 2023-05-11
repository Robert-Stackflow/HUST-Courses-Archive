#include "socket/client.h"
#include "qdatetime.h"
#include "qdir.h"
#include "socket/response.h"
#include "widget/floatbox.h"
#include "util/socketconfig.h"
#include "QsLog.h"
#include<fstream>
#include<QDebug>
#include<windows.h>
#include"socket/packet.h"
#pragma warning(disable:4100)
#define BUFFER_SIZE 1024
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
Client::Client(const char *ip,unsigned short int port, int backlog):success(false)
{
    if (!startup()){
        QLOG_FATAL()<<"Socket创建失败";
        return;
    }
    if (!connectServer(ip,port)) {
        QLOG_FATAL()<<"Socket连接失败";
        return;
    }
    success=true;
    QLOG_INFO()<<"Socket初始化成功";
};
int Client::start()
{
    int rtn;
    int _id;
    Response* response=nullptr;
    while(true){
        if(isSendMessage){
            Message messagePacket=Message();
            strcpy_s(messagePacket.message,this->message.toUtf8().data());
            if((::send(socket,(const char*)&messagePacket,sizeof(Message),0)) == WSAECONNABORTED){
                QLOG_ERROR()<<"消息发送失败:"<<message;
                return -1;
            }
            QLOG_INFO()<<"消息发送成功:"<<message;
            UniversalRes result={};
            rtn = recv(socket,(char*)&result,sizeof(UniversalRes),0);
            if(rtn>0)
                QLOG_INFO()<<"收到服务端的响应回执";
            else
                QLOG_WARN()<<"未能收到服务端的响应回执";
            isSendMessage = false;
        }else if(isSendFile){
            FilePath filepathPacket=FilePath();
            _id=SocketConfig::responseList.size();
            response=new Response(_id,this->filepath);
            SocketConfig::responseList.append(response);
            emit fileChanged();
            strcpy_s(filepathPacket.filePath,this->filepath.toUtf8().data());
            if((::send(socket,(const char*)&filepathPacket,sizeof(FilePath),0)) == WSAECONNABORTED){
                QLOG_ERROR()<<"文件请求发送失败:"<<filepath;
                response->setStatus(Response::FAIL);
                emit fileChanged();
                return -1;
            }
            QLOG_INFO()<<"文件请求发送成功:"<<filepath;
            UniversalRes result={};
            rtn = recv(socket,(char*)&result,sizeof(UniversalRes),0);
            if(rtn>0&&result.status==1){
                QLOG_INFO()<<"收到服务端的响应回执,准备接收文件";
                int fileSize=result.data;
                QLOG_INFO()<<qUtf8Printable("预计文件大小为"+QString::number(fileSize)+"字节");
                {
                    FILE * fp;
                    int fileBytesReceived=0;
                    char buffer[BUFFER_SIZE];
                    QString filename="./file/"+QFileInfo(this->filepath).fileName();
                    fopen_s(&fp,filename.toUtf8().data(), "wb");
                    if(NULL == fp)
                    {
                        response->setStatus(Response::FAIL);
                        emit fileChanged();
                        QLOG_ERROR()<<qUtf8Printable("文件"+filename+"不能打开");
                    }
                    else
                    {
                        memset(buffer, 0, BUFFER_SIZE);
                        int length = 0;
                        while ((length = recv(socket, buffer, BUFFER_SIZE, 0)) > 0)
                        {
                            if (fwrite(buffer, sizeof(char), length, fp) < length)
                            {
                                response->setStatus(Response::FAIL);
                                emit fileChanged();
                                QLOG_ERROR()<<qUtf8Printable("文件"+QFileInfo(this->filepath).fileName()+"写入失败");
                                break;
                            }
                            fileBytesReceived+=length;
                            if(fileBytesReceived>=fileSize)
                                break;
                            memset(buffer, 0, BUFFER_SIZE);
                        }
                        response->setBytes(fileBytesReceived);
                        response->setStatus(Response::SUCCESS);
                        emit fileChanged();
                        QLOG_INFO()<<qUtf8Printable("文件"+QFileInfo(this->filepath).fileName()+"接收成功");
                    }
                    fclose(fp);
                }
            }else if(rtn>0&&result.status==2){
                response->setStatus(Response::NOTEXIST);
                emit fileChanged();
                QLOG_ERROR()<<qUtf8Printable("未找到在服务器上的文件"+this->filepath);
            }else{
                response->setStatus(Response::FAIL);
                emit fileChanged();
                QLOG_WARN()<<"未收到服务端的响应回执，文件请求失败";
            }isSendFile = false;
        }
    }
}
bool Client::close(){
    closesocket(socket);
    WSACleanup();
    QLOG_INFO()<<"Socket连接关闭";
    return true;
}
Client::~Client() {

};
bool Client::isSuccess() const
{
    return success;
}
void Client::sendMessage(const QString &message)
{
    this->message = message;
    this->isSendMessage=true;
}
void Client::sendFile(const QString &filepath)
{
    this->filepath = filepath;
    this->isSendFile=true;
}
