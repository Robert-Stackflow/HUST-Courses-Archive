#ifndef HTTPHELPER_H
#define HTTPHELPER_H
#include<QString>
class HttpHelper{
public:
    static const char* getContentType(QString filename);
    static QString getFilePath(char* requestUrl);
    static bool isValidPath(QString filePath);
    static char* getResponse404(QString filename, int bytes);
    static char* getResponse400(QString filename, int bytes);
    static char *getResponse200(QString filename, int bytes);
};

#endif // HTTPHELPER_H
