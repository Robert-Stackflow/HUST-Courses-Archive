#include"util/httphelper.h"
#include "qfileinfo.h"
#include <cstring>
#include "QsLog.h"
#include "util/httpparser.h"
#pragma warning(disable:4100)
const char* HttpHelper::getContentType(QString filename)
{
    if(filename.endsWith(".html"))
        return "text/html;charset=UTF-8";
    else if(filename.endsWith(".c")||filename.endsWith(".cpp")||filename.endsWith(".md"))
        return "text/plain;charset=UTF-8";
    else if(filename.endsWith(".xml"))
        return "application/xml";
    else if(filename.endsWith(".png"))
        return "image/png";
    else if(filename.endsWith(".jpg"))
        return "image/jpeg";
    else if(filename.endsWith(".jpeg"))
        return "image/jpeg";
    else if(filename.endsWith(".gif"))
        return "image/gif";
    else if(filename.endsWith(".pdf"))
        return "application/pdf";
    else if(filename.endsWith(".doc"))
        return "application/msword";
    else if(filename.endsWith(".ico"))
        return "image/x-icon";
    else if(filename.endsWith(".mp3"))
        return "audio/mp3";
    else if(filename.endsWith(".sql"))
        return "text/plain;charset=UTF-8";
    else if(filename.endsWith(".exe"))
        return "application/x-msdownload";
    return nullptr;
}
bool HttpHelper::isValidPath(QString filePath)
{
    if(filePath.contains(";")||filePath.contains("=")||filePath.contains("(")||!filePath.startsWith("/")||!filePath.contains("."))
        return false;
    return true;
}
QString HttpHelper::getFilePath(char* requestUrl)
{
    HttpParser httpPackage(requestUrl);
    QString filePath=QString::fromStdString(httpPackage["path"]);
    if(filePath=="/"||filePath=="")
        return "/index.html";
    if(!isValidPath(filePath))
        return nullptr;
    return QString::fromStdString(httpPackage["path"]);
}
char* HttpHelper::getResponse200(QString filename, int bytes)
{
    QString temp=QString::asprintf("HTTP/1.1 200 OK \r\nServer:Socket Server\r\nAccept-Ranges:bytes\r\nContent-Length:%d\r\nConnection:keep-alive\r\nContent-Type:%s\r\n\r\n",bytes,getContentType(filename));
    char* str=(char*)malloc((temp.size()+100)*sizeof(char));
    sprintf_s(str,temp.size()+100,"HTTP/1.1 200 OK \r\nServer:Socket Server\r\nAccept-Ranges:bytes\r\nContent-Length:%d\r\nConnection:keep-alive\r\nContent-Type:%s\r\n\r\n",bytes,getContentType(filename));
    return str;
}
char* HttpHelper::getResponse404(QString filename, int bytes)
{
    QString temp=QString::asprintf("HTTP/1.1 404 NOT FOUND \r\nServer:Socket Server\r\nAccept-Ranges:bytes\r\nContent-Length:%d\r\nConnection:keep-alive\r\nContent-Type:%s\r\n\r\n",bytes,getContentType(filename));
    char* str=(char*)malloc((temp.size()+100)*sizeof(char));
    sprintf_s(str,temp.size()+100,"HTTP/1.1 404 NOT FOUND \r\nServer:Socket Server\r\nAccept-Ranges:bytes\r\nContent-Length:%d\r\nConnection:keep-alive\r\nContent-Type:%s\r\n\r\n",bytes,getContentType(filename));
    return str;
}
char* HttpHelper::getResponse400(QString filename, int bytes)
{
    QString temp=QString::asprintf("HTTP/1.1 400 INVALID \r\nServer:Socket Server\r\nAccept-Ranges:bytes\r\nContent-Length:%d\r\nConnection:keep-alive\r\nContent-Type:%s\r\n\r\n",bytes,getContentType(filename));
    char* str=(char*)malloc((temp.size()+100)*sizeof(char));
    sprintf_s(str,temp.size()+100,"HTTP/1.1 400 INVALID \r\nServer:Socket Server\r\nAccept-Ranges:bytes\r\nContent-Length:%d\r\nConnection:keep-alive\r\nContent-Type:%s\r\n\r\n",bytes,getContentType(filename));
    return str;
}
