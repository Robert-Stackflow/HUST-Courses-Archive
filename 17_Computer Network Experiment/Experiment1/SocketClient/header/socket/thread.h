#ifndef THREAD_H
#define THREAD_H
#include<QThread>
#include"client.h"
class SocketThread:public QThread
{
    Q_OBJECT
public:
    SocketThread();
    ~SocketThread();
    void run();
    void finish();
private:
    Client* client;
signals:
    void startFail();
    void startSuccess();
    void fileChanged();
public slots:
    void onSendMessage(QString message);
    void onSendFile(QString filepath);
};

#endif // THREAD_H
