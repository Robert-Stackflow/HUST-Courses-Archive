#ifndef CVALIDATOR_H
#define CVALIDATOR_H
#include "qdir.h"
#include "qregexp.h"
#include "qvalidator.h"
class CValidator{
public:
    enum DIR{
        VALID,
        NOTEXIST,
        CONTAINCHINESE,
    };
    const static QRegExp portRegExp;
    const static QRegExpValidator* portValidator;
    const static QRegExp ipRegExp;
    const static QRegExpValidator* ipValidator;
    static DIR checkDir(const QString& directory);
    static bool checkIp(const QString& ip);
    static bool checkPort(const QString& port);
    static bool checkPort(int port);
    static QString getInfo(CValidator::DIR result);
    static bool checkFile(char* fileName);
};
#endif // CVALIDATOR_H
