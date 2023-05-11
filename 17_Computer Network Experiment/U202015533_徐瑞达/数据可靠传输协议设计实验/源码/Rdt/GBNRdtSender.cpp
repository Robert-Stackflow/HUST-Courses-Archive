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
	Logger::Info({ "[���ͷ�] ��ǰ����Ϊ:\n",windowStr });
}
bool GBNRdtSender::send(const Message& message)
{
	if (nextSendSeqNum < firstWaitingAckSeqNum + windowLength) {
		//����һ�������͵ķ�������ڴ����ڣ����͸÷���
		this->isWindowFull = false;
		this->packets[packetNum].acknum = -1;
		this->packets[packetNum].checksum = 0;
		this->packets[packetNum].seqnum = this->nextSendSeqNum;
		memcpy(this->packets[packetNum].payload, message.data, sizeof(message.data));
		this->packets[packetNum].checksum = pUtils->calculateCheckSum(packets[packetNum]);
		Logger::Info({ "[���ͷ�] ���ͷ����ͱ���:", Logger::getPacketString(this->packets[packetNum]) });
		//��������ͷ���Ϊ�����ڵ�һ�����飬������ʱ��
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
		//��������ڴ��ڷ��飬�����յ���ACK
		int checkSum = pUtils->calculateCheckSum(ackPkt);
		if (checkSum == ackPkt.checksum && ackPkt.acknum >= this->firstWaitingAckSeqNum) {
			Logger::Info({ "[���ͷ�] ���ͷ��յ�ȷ��:", Logger::getPacketString(ackPkt) });
			//�������һ������ڳ���
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
			Logger::Info({ "[���ͷ�] ���һ������ڳ���:",to_string(slideLength) });
			//���һ������ڣ�����СpacketNum
			for (int i = 0; i < packetNum - slideLength; i++)
				packets[i] = packets[i + slideLength];
			this->packetNum = this->packetNum - slideLength;
			printWindow();
		}
	}
}

void GBNRdtSender::timeoutHandler(int seqNum)
{
	//��ʱʱ�����ʹ����������ѷ��ͷ��飬��������ʱ��
	Logger::Warn({ "[���ͷ�] ���ͷ���ʱ����ʱ���ط���һ�η��͵ı���:",Logger::getPacketString(this->packets[0]) });
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
