#include "socket/thread.h"
#include "QsLog.h"
#include "qdatetime.h"
#include "util/socketconfig.h"
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
SocketThread::SocketThread():QThread()
{
    qRegisterMetaType<Request>("Request");
}
void SocketThread::run(){
    server=new Server(SocketConfig::getIpAddress(),SocketConfig::getPort(),5);
    connect(server,SIGNAL(requestChanged()),this,SLOT(onRequestChanged()));
    if(server->isSuccess())
        emit startSuccess(),server->start();
    else
        emit startFail();
}

void SocketThread::finish(){
    if(server!=nullptr)
        server->close();
}
void SocketThread::onRequestChanged()
{
    emit requestChanged();
}
SocketThread::~SocketThread(){
    delete this->server;
}
