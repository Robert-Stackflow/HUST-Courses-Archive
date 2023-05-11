#ifndef SOCKETHELPER_H
#define SOCKETHELPER_H
#include <QStringList>
class SocketHelper{
public:
    static int TestWSAStartUp();
    static void TestSocket();
    static void TestBind();
    static void TestAccept();
    static QStringList getIpList();
};
#endif // SOCKETHELPER_H
