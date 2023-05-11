#ifndef THREAD_H
#define THREAD_H
#include<QThread>
#include"server.h"
class SocketThread:public QThread
{
    Q_OBJECT
public:
    SocketThread();
    ~SocketThread();
    void run();
    void finish();
private:
    Server* server;
signals:
    void startFail();
    void startSuccess();
    void requestChanged();
public slots:
    void onRequestChanged();
};
#endif // THREAD_H
