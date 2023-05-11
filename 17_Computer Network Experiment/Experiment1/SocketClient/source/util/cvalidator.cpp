#include "util/cvalidator.h"
#include "util/sockethelper.h"
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
const QRegExp CValidator::portRegExp=QRegExp("^([0-9]|[1-9]\\d{1,3}|[1-5]\\d{4}|6[0-4]\\d{3}|65[0-4]\\d{2}|655[0-2]\\d|6553[0-5])$");
const QRegExpValidator* CValidator::portValidator=new QRegExpValidator(CValidator::portRegExp,0);
const QRegExp CValidator::ipRegExp=QRegExp("^((2(5[0-5]|[0-4]\\d))|[0-1]?\\d{1,2})(\\.((2(5[0-5]|[0-4]\\d))|[0-1]?\\d{1,2})){3}$");
const QRegExpValidator* CValidator::ipValidator=new QRegExpValidator(CValidator::ipRegExp,0);
CValidator::DIR CValidator::checkDir(const QString& directory)
{
    QDir dir(directory);
    if(!dir.exists())
        return CValidator::DIR::NOTEXIST;
    if(directory.contains(QRegExp("[\\x4e00-\\x9fa5]+")))
        return CValidator::DIR::CONTAINCHINESE;
    return CValidator::DIR::VALID;
}
QString CValidator::getInfo(CValidator::DIR result){
    if(result==CValidator::NOTEXIST)
        return "路径不存在";
    if(result==CValidator::CONTAINCHINESE)
        return "不能包含中文";
    return "";
}
bool CValidator::checkIp(const QString& ip)
{
    QString _ip=ip;
    int position=0;
    QStringList list=_ip.split('.');
    if(CValidator::ipValidator->validate(_ip,position)&&list.size()==4&&list.at(0)!=""&&list.at(1)!=""&&list.at(2)!=""&&list.at(3)!="")
        return true;
    return false;
}
bool CValidator::checkPort(const QString& port)
{
    return checkPort(port.toInt());
}
bool CValidator::checkPort(int port)
{
    if(port<1||port>65535)
        return false;
    return true;
}
