#ifndef LOGGERCONFIG_H
#define LOGGERCONFIG_H
#include "QsLog.h"
#include "qcoreapplication.h"
class LoggerConfig{
public:
    static QsLogging::Level loggerLevel;
    static QString logPath;
    static QString dataDir;
    static QsLogging::LogRotationOption rotationOption;
    static QsLogging::MaxSizeBytes maxSizeBytes;
    static QsLogging::MaxOldLogCount maxOldLogCount;
};
QsLogging::Level LoggerConfig::loggerLevel=QsLogging::DebugLevel;
QString LoggerConfig::logPath="/data/socket server.log";
QString LoggerConfig::dataDir="./data";
QsLogging::LogRotationOption LoggerConfig::rotationOption=QsLogging::DisableLogRotation;
QsLogging::MaxSizeBytes LoggerConfig::maxSizeBytes=QsLogging::MaxSizeBytes(512);
QsLogging::MaxOldLogCount LoggerConfig::maxOldLogCount=QsLogging::MaxOldLogCount(0);
#endif // LOGGERCONFIG_H
