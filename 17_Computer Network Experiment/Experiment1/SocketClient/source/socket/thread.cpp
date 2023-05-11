#include "socket/thread.h"
#include "QsLog.h"
#include "util/socketconfig.h"
SocketThread::SocketThread():QThread()
{
}
void SocketThread::run(){
    client=new Client(SocketConfig::getIpAddress(),SocketConfig::getPort(),5);
    connect(client,&Client::fileChanged,[=]{
        emit fileChanged();
    });
    if(client->isSuccess())
        emit startSuccess(),client->start();
    else
        emit startFail();
}

void SocketThread::finish(){
    if(client!=nullptr)
        client->close();
}
void SocketThread::onSendMessage(QString message)
{
    client->sendMessage(message);
}
void SocketThread::onSendFile(QString filepath)
{
    client->sendFile(filepath);
}
SocketThread::~SocketThread(){
    delete this->client;
}
