#ifndef LOGGER_H
#define LOGGER_H
#pragma once
#include "stdafx.h"
#include <iomanip>
#include <ctime>
#include <cstdio>
#include "DataStructure.h"
class Logger
{
public:
	enum LogLevel {
		TRACE = 0,
		DEBUG,
		INFO,
		WARN,
		ERROR,
		FATAL,
		OFF
	};
	static FILE* fp;
	static LogLevel level;
	static Logger* sInstance;
	static char* fileOutputPath;
	static bool fileOutputEnable;
	static bool consoleOutputEnable;
public:
	Logger();
	~Logger();
	static Logger& instance();
	static void clearHistory();
	static void destroyInstance();
	static string getPacketString(Packet packet);
	static void setLogLevel(LogLevel newLevel);
	static void setConsoleOutputEnable(bool enable);
	static void setFileOutputEnable(bool enable);
	static void setFileOutputPath(const char* filePath);
	static void TracePrior(initializer_list<string> il);
	static void DebugPrior(initializer_list<string> il);
	static void InfoPrior(initializer_list<string> il);
	static void WarnPrior(initializer_list<string> il);
	static void ErrorPrior(initializer_list<string> il);
	static void FatalPrior(initializer_list<string> il);
	static void Trace(initializer_list<string> il);
	static void Debug(initializer_list<string> il);
	static void Info(initializer_list<string> il);
	static void Warn(initializer_list<string> il);
	static void Error(initializer_list<string> il);
	static void Fatal(initializer_list<string> il);
private:
	static void log(LogLevel destLevel, initializer_list<string> il);
	static void printIntoConsole(const char* str);
	static void printIntoFile(const char* str);
};
#endif