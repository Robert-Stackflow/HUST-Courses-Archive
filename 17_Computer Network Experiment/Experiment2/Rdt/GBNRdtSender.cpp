#include "stdafx.h"
#include "Global.h"
#include "GBNRdtSender.h"
#include "Logger.h"
#include <string>
bool GBNRdtSender::getWaitingState()
{
	return isWindowFull;
}
void GBNRdtSender::printWindow()
{
	string windowStr = "order\t";
	for (int i = 0; i < windowLength; i++)
		windowStr += to_string(i), windowStr += "\t";
	windowStr += "\nseqnum\t";
	for (int i = 0; i < windowLength; i++) {
		if (i < packetNum)
			windowStr += to_string(packets[i].seqnum), windowStr += "\t";
		else
			windowStr += '-', windowStr += "\t";
	}
	Logger::Info({ "[发送方] 当前窗口为:\n",windowStr });
}
bool GBNRdtSender::send(const Message& message)
{
	if (nextSendSeqNum < firstWaitingAckSeqNum + windowLength) {
		//当下一个待发送的分组序号在窗口内，发送该分组
		this->isWindowFull = false;
		this->packets[packetNum].acknum = -1;
		this->packets[packetNum].checksum = 0;
		this->packets[packetNum].seqnum = this->nextSendSeqNum;
		memcpy(this->packets[packetNum].payload, message.data, sizeof(message.data));
		this->packets[packetNum].checksum = pUtils->calculateCheckSum(packets[packetNum]);
		Logger::Info({ "[发送方] 发送方发送报文:", Logger::getPacketString(this->packets[packetNum]) });
		//如果待发送分组为窗口内第一个分组，启动定时器
		if (firstWaitingAckSeqNum == nextSendSeqNum)
			pns->startTimer(SENDER, Configuration::TIME_OUT, this->packets[packetNum].seqnum);
		pns->sendToNetworkLayer(RECEIVER, this->packets[packetNum]);
		this->packetNum++;
		if (packetNum > windowLength)
			this->isWindowFull = true;
		this->nextSendSeqNum++;
		return true;
	}
	else {
		this->isWindowFull = true;
		return false;
	}
}

void GBNRdtSender::receive(const Packet& ackPkt)
{
	if (this->packetNum > 0) {
		//如果窗口内存在分组，则处理收到的ACK
		int checkSum = pUtils->calculateCheckSum(ackPkt);
		if (checkSum == ackPkt.checksum && ackPkt.acknum >= this->firstWaitingAckSeqNum) {
			Logger::Info({ "[发送方] 发送方收到确认:", Logger::getPacketString(ackPkt) });
			//计算向右滑动窗口长度
			int slideLength = ackPkt.acknum - firstWaitingAckSeqNum + 1;
			firstWaitingAckSeqNum = ackPkt.acknum + 1;
			if (this->firstWaitingAckSeqNum == this->nextSendSeqNum) {
				pns->stopTimer(SENDER, this->packets[0].seqnum);
			}
			else {
				pns->stopTimer(SENDER, this->packets[0].seqnum);
				pns->startTimer(SENDER, Configuration::TIME_OUT, this->packets[slideLength].seqnum);
			}
			printWindow();
			Logger::Info({ "[发送方] 向右滑动窗口长度:",to_string(slideLength) });
			//向右滑动窗口，并减小packetNum
			for (int i = 0; i < packetNum - slideLength; i++)
				packets[i] = packets[i + slideLength];
			this->packetNum = this->packetNum - slideLength;
			printWindow();
		}
	}
}

void GBNRdtSender::timeoutHandler(int seqNum)
{
	//超时时，发送窗口内所有已发送分组，并重启计时器
	Logger::Warn({ "[发送方] 发送方定时器超时，重发上一次发送的报文:",Logger::getPacketString(this->packets[0]) });
	pns->stopTimer(SENDER, this->packets[0].seqnum);
	pns->startTimer(SENDER, Configuration::TIME_OUT, this->packets[0].seqnum);
	for (int i = 0; i < packetNum; i++)
		pns->sendToNetworkLayer(RECEIVER, this->packets[i]);
}

GBNRdtSender::GBNRdtSender() :packetNum(0), isWindowFull(false), nextSendSeqNum(1), firstWaitingAckSeqNum(1)
{
}

GBNRdtSender::~GBNRdtSender()
{
}
