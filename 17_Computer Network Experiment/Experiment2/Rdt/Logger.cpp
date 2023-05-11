#include "Logger.h"
#include <string>
#include <chrono>
FILE* Logger::fp = nullptr;
Logger* Logger::sInstance = nullptr;
bool Logger::fileOutputEnable = true;
char* Logger::fileOutputPath = nullptr;
bool Logger::consoleOutputEnable = true;
Logger::LogLevel Logger::level = Logger::INFO;
static const char TraceString[] = "[TRACE]";
static const char DebugString[] = "[DEBUG]";
static const char InfoString[] = "[INFO] ";
static const char WarnString[] = "[WARN] ";
static const char ErrorString[] = "[ERROR]";
static const char FatalString[] = "[FATAL]";
string now()
{
	time_t t;
	time(&t);
	char tmp[64];
	struct tm* timinfo;
	timinfo = localtime(&t);
	auto now = chrono::time_point_cast<chrono::milliseconds>(chrono::system_clock::now());
	int milliSecond = now.time_since_epoch().count() % 1000;
	int len = strftime(tmp, sizeof(tmp), "[%Y-%m-%d %H:%M:%S", timinfo);
	sprintf(tmp + len, ":%03u]",milliSecond);
	return tmp;
}
const char* getString(Logger::LogLevel level)
{
	switch (level)
	{
	case Logger::TRACE:
		return TraceString;
	case Logger::DEBUG:
		return DebugString;
	case Logger::INFO:
		return InfoString;
	case Logger::WARN:
		return WarnString;
	case Logger::ERROR:
		return ErrorString;
	case Logger::FATAL:
		return FatalString;
	}
	return "OFF";
}
Logger::Logger()
{
	fileOutputPath = new char[1024];
	strcpy(fileOutputPath, "./log.txt");
}
Logger& Logger::instance()
{
	if (!sInstance)
		sInstance = new Logger();
	return *sInstance;
}

void Logger::destroyInstance()
{
	delete sInstance;
	sInstance = nullptr;
}

string Logger::getPacketString(Packet packet)
{
	char payload[21];
	strncpy(payload, packet.payload, 20);
	payload[20] = '\0';
	return string("seqnum = " + std::to_string(packet.seqnum) + ",acknum = " + std::to_string(packet.acknum) + ",checknum = " + std::to_string(packet.checksum) + ",payload = " + payload);
}

void Logger::clearHistory()
{
	remove(fileOutputPath);
}

void Logger::setLogLevel(LogLevel newLevel)
{
	level = newLevel;
}

void Logger::setConsoleOutputEnable(bool enable)
{
	consoleOutputEnable = enable;
}

void Logger::setFileOutputEnable(bool enable)
{
	fileOutputEnable = enable;
}

void Logger::setFileOutputPath(const char* filePath)
{
	fileOutputPath = new char[1024];
	strcpy(fileOutputPath, filePath);
}

void Logger::Trace(initializer_list<string> il)
{
	log(Logger::TRACE, il);
}

void Logger::Debug(initializer_list<string> il)
{
	log(Logger::DEBUG, il);
}

void Logger::Info(initializer_list<string> il)
{
	log(Logger::INFO, il);
}
void Logger::Warn(initializer_list<string> il)
{
	log(Logger::WARN, il);
}

void Logger::Error(initializer_list<string> il)
{
	log(Logger::ERROR, il);
}

void Logger::Fatal(initializer_list<string> il)
{
	log(Logger::FATAL, il);
}
void Logger::TracePrior(initializer_list<string> il)
{
	bool isConsoleOutputEnable = consoleOutputEnable;
	bool isFileOutputEnable = fileOutputEnable;
	Logger::setConsoleOutputEnable(true);
	Logger::setFileOutputEnable(true);
	log(Logger::TRACE, il);
	Logger::setConsoleOutputEnable(isConsoleOutputEnable);
	Logger::setFileOutputEnable(isFileOutputEnable);
}

void Logger::DebugPrior(initializer_list<string> il)
{
	bool isConsoleOutputEnable = consoleOutputEnable;
	bool isFileOutputEnable = fileOutputEnable;
	Logger::setConsoleOutputEnable(true);
	Logger::setFileOutputEnable(true);
	log(Logger::DEBUG, il);
	Logger::setConsoleOutputEnable(isConsoleOutputEnable);
	Logger::setFileOutputEnable(isFileOutputEnable);
}

void Logger::InfoPrior(initializer_list<string> il)
{
	bool isConsoleOutputEnable = consoleOutputEnable;
	bool isFileOutputEnable = fileOutputEnable;
	Logger::setConsoleOutputEnable(true);
	Logger::setFileOutputEnable(true);
	log(Logger::INFO, il);
	Logger::setConsoleOutputEnable(isConsoleOutputEnable);
	Logger::setFileOutputEnable(isFileOutputEnable);
}
void Logger::WarnPrior(initializer_list<string> il)
{
	bool isConsoleOutputEnable = consoleOutputEnable;
	bool isFileOutputEnable = fileOutputEnable;
	Logger::setConsoleOutputEnable(true);
	Logger::setFileOutputEnable(true);
	log(Logger::WARN, il);
	Logger::setConsoleOutputEnable(isConsoleOutputEnable);
	Logger::setFileOutputEnable(isFileOutputEnable);
}

void Logger::ErrorPrior(initializer_list<string> il)
{
	bool isConsoleOutputEnable = consoleOutputEnable;
	bool isFileOutputEnable = fileOutputEnable;
	Logger::setConsoleOutputEnable(true);
	Logger::setFileOutputEnable(true);
	log(Logger::ERROR, il);
	Logger::setConsoleOutputEnable(isConsoleOutputEnable);
	Logger::setFileOutputEnable(isFileOutputEnable);
}

void Logger::FatalPrior(initializer_list<string> il)
{
	bool isConsoleOutputEnable = consoleOutputEnable;
	bool isFileOutputEnable = fileOutputEnable;
	Logger::setConsoleOutputEnable(true);
	Logger::setFileOutputEnable(true);
	log(Logger::FATAL, il);
	Logger::setConsoleOutputEnable(isConsoleOutputEnable);
	Logger::setFileOutputEnable(isFileOutputEnable);
}
void Logger::log(LogLevel destLevel, initializer_list<string> il)
{
	if (Logger::level <= destLevel)
	{
		string message;
		for (auto p = il.begin(); p != il.end(); p++)
			message += *p;
		char* str = new char[1024];
		sprintf(str, "%s %s %s\n", now().c_str(), getString(destLevel), message.c_str());
		printIntoConsole(str);
		printIntoFile(str);
	}
}
void Logger::printIntoConsole(const char* str)
{
	if (str == nullptr)
		return;
	if (consoleOutputEnable) {
		std::cout << str << std::endl;
	}
}

void Logger::printIntoFile(const char* str)
{
	if (str == nullptr)
		return;
	if (fp == nullptr)
		fp = new FILE();
	if (fileOutputEnable && fp != nullptr) {
		fopen_s(&fp, fileOutputPath, "a+");
		if (fp != nullptr) {
			fprintf(fp, "%s", str);
			fclose(fp);
		}
	}
}

Logger::~Logger()
{
	sInstance = nullptr;
	if (fp != nullptr)
		fclose(fp);
}
