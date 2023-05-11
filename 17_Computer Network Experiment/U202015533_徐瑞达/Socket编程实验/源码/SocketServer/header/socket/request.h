#ifndef REQUEST_H
#define REQUEST_H
#include <QString>
#include <QStringList>
class Request{
public:
    QStringList statusList;
    enum REQUESTSTATUS{
        NORMAL,
        SUCCESS,
        NOTEXIST,
        INVALID,
        FAIL,
    };
    Request() {}
    Request(int id, char *ip, int port);
    char *getIp() const;
    void setIp(char *newIp);
    int getPort() const;
    void setPort(int newPort);
    const QString &getConnTime() const;
    void setConnTime(const QString &newConnTime);
    const QString &getDisconnTime() const;
    void setDisconnTime(const QString &newDisconnTime);
    int getId() const;
    void setId(int newId);
    REQUESTSTATUS getStatus() const;
    void setStatus(REQUESTSTATUS newStatus);
    QString getStatusString();
    const QString &getFilePath() const;
    void setFilePath(const QString &newFilePath);
    const QString &getPacket() const;
    void setPacket(const QString &newPacket);

private:
    int id;
    char* ip;
    int port;
    QString filePath;
    REQUESTSTATUS status;
    QString connTime;
    QString disconnTime;
    QString packet;
};
#endif // REQUEST_H
