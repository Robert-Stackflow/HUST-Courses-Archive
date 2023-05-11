#include "TCPSender.h"
#include "stdafx.h"
#include "Global.h"
#include "Logger.h"
#include <string>
#pragma warning(disable:26495)
bool TCPSender::getWaitingState()
{
	return isWindowFull;
}
void TCPSender::printWindow(bool isPrior)
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
	if (isPrior)
		Logger::InfoPrior({ "[���ͷ�] ��ǰ����Ϊ:\n",windowStr });
	else
		Logger::Info({ "[���ͷ�] ��ǰ����Ϊ:\n",windowStr });
}
bool TCPSender::send(const Message& message)
{
	if (nextSendSeqNum < firstWaitingAckSeqNum + windowLength) {
		this->isWindowFull = false;
		this->packets[packetNum].acknum = -1;
		this->packets[packetNum].checksum = 0;
		this->packets[packetNum].seqnum = this->nextSendSeqNum;
		memcpy(this->packets[packetNum].payload, message.data, sizeof(message.data));
		this->packets[packetNum].checksum = pUtils->calculateCheckSum(this->packets[packetNum]);
		Logger::Info({ "[���ͷ�] ���ͷ����ͱ���:", Logger::getPacketString(this->packets[packetNum]) });
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

void TCPSender::receive(const Packet& ackPkt)
{
	if (this->packetNum > 0) {
		int checkSum = pUtils->calculateCheckSum(ackPkt);
		Logger::InfoPrior({ "[���ͷ�] �ѽ��յ���ACK��Ŀ:", to_string(ackCount),",�½��յ���ACK���:", to_string(ackPkt.acknum),",��ʱ�Ĵ����ڵ�һ����������:", to_string(firstWaitingAckSeqNum) });
		if (checkSum == ackPkt.checksum && ackPkt.acknum >= this->firstWaitingAckSeqNum) {
			if (ackPkt.acknum == this->packets[0].seqnum) {
				this->ackCount++;
				if (ackCount == 4) {
					//ACK��Ŀ����3�������ش����ģ�������ʱ��
					pns->stopTimer(SENDER, this->packets[0].seqnum);
					pns->sendToNetworkLayer(RECEIVER, this->packets[0]);
					Logger::InfoPrior({ "[���ͷ�] ����ACK����3,�����ش���ǰ���ڵ�һ������:", Logger::getPacketString(packets[0]) });
					printWindow(true);
					pns->startTimer(SENDER, Configuration::TIME_OUT, this->packets[0].seqnum);
					this->ackCount = 0;
					return;
				}
			}
			else this->ackCount = 1;
			if (this->ackCount == 1) {
				//���ackCount==1��˵�������ڵ�һ�����鷢�ͳɹ������һ�������
				int slideLength = ackPkt.acknum - this->firstWaitingAckSeqNum;
				firstWaitingAckSeqNum = ackPkt.acknum;
				Logger::Info({ "[���ͷ�] ���ͷ����յ�ACK����:", Logger::getPacketString(ackPkt) });
				if (this->firstWaitingAckSeqNum == this->nextSendSeqNum)
					pns->stopTimer(SENDER, this->packets[0].seqnum);
				else {
					pns->stopTimer(SENDER, this->packets[0].seqnum);
					pns->startTimer(SENDER, Configuration::TIME_OUT, this->packets[slideLength].seqnum);
				}
				printWindow(false);
				Logger::Info({ "[���ͷ�] ���һ������ڳ���:",to_string(slideLength) });
				for (int i = 0; i < packetNum - slideLength; i++)
					packets[i] = packets[i + slideLength];
				this->packetNum = this->packetNum - slideLength;
				printWindow(false);
			}
		}
	}
}

void TCPSender::timeoutHandler(int seqNum)
{
	Logger::Warn({ "[���ͷ�] ���ͷ���ʱ����ʱ���ط���һ�η��͵ı���:",Logger::getPacketString(this->packets[0]) });
	pns->stopTimer(SENDER, this->packets[0].seqnum);
	pns->startTimer(SENDER, Configuration::TIME_OUT, this->packets[0].seqnum);
	pns->sendToNetworkLayer(RECEIVER, this->packets[0]);
}

TCPSender::TCPSender() :packetNum(0), isWindowFull(false), nextSendSeqNum(1), firstWaitingAckSeqNum(1)
{
}

TCPSender::~TCPSender()
{
}
