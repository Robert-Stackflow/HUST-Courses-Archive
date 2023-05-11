#include "stdafx.h"
#include "Global.h"
#include "RdtSender.h"
#include "RdtReceiver.h"
#include "SRRdtSender.h"
#include "SRRdtReceiver.h"
#include "GBNRdtSender.h"
#include "GBNRdtReceiver.h"
#include "TCPSender.h"
#include "TCPReceiver.h"
#include "StopWaitRdtSender.h"
#include "StopWaitRdtReceiver.h"
#include "Logger.h"
void testSR();
void testGBN();
void testTCP();
void testStopWait();
int main(int argc, char* argv[])
{
	Logger logger = Logger::instance();
	Logger::setLogLevel(Logger::INFO);
	Logger::clearHistory();
	Logger::setFileOutputEnable(true);
	Logger::setConsoleOutputEnable(true);
	int option = 0;
	printf("--------------------------Rdt--------------------------\n");
	printf("   1.StopWait        2.GBN        3.SR        4.TCP    \n");
	printf("-------------------------------------------------------\n");
	printf("Input Your Option[1-4]:");
	if (scanf("%d", &option)) {
		system("cls");
		switch (option) {
		case 1:
			testStopWait();
			break;
		case 2:
			testGBN();
			break;
		case 3:
			testSR();
			break;
		case 4:
			testTCP();
			break;
		}
	}
	return 0;
}
void testTCP()
{
	Logger::Info({ "运行TCP协议" });
	RdtSender* ps = new TCPSender();
	RdtReceiver* pr = new TCPReceiver();
	pns->setRunMode(1);
	pns->init();
	pns->setRtdSender(ps);
	pns->setRtdReceiver(pr);
	pns->setInputFile("input.txt");
	pns->setOutputFile("output.txt");
	pns->start();
	delete ps;
	delete pr;
	delete pUtils;
	delete pns;
}
void testSR()
{
	Logger::Info({ "运行SR协议" });
	RdtSender* ps = new SRRdtSender();
	RdtReceiver* pr = new SRRdtReceiver();
	pns->setRunMode(1);
	pns->init();
	pns->setRtdSender(ps);
	pns->setRtdReceiver(pr);
	pns->setInputFile("input.txt");
	pns->setOutputFile("output.txt");
	pns->start();
	delete ps;
	delete pr;
	delete pUtils;
	delete pns;
}
void testGBN()
{
	Logger::Info({ "运行GBN协议" });
	RdtSender* ps = new GBNRdtSender();
	RdtReceiver* pr = new GBNRdtReceiver();
	pns->setRunMode(1);
	pns->init();
	pns->setRtdSender(ps);
	pns->setRtdReceiver(pr);
	pns->setInputFile("input.txt");
	pns->setOutputFile("output.txt");

	pns->start();

	delete ps;
	delete pr;
	delete pUtils;
	delete pns;
}
void testStopWait()
{
	Logger::Info({ "运行StopWait协议" });
	RdtSender* ps = new StopWaitRdtSender();
	RdtReceiver* pr = new StopWaitRdtReceiver();
	pns->setRunMode(1);
	pns->init();
	pns->setRtdSender(ps);
	pns->setRtdReceiver(pr);
	pns->setInputFile("input.txt");
	pns->setOutputFile("output.txt");

	pns->start();

	delete ps;
	delete pr;
	delete pUtils;
	delete pns;
}