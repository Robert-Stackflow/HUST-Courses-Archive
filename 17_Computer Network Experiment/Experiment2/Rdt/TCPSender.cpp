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
		Logger::InfoPrior({ "[发送方] 当前窗口为:\n",windowStr });
	else
		Logger::Info({ "[发送方] 当前窗口为:\n",windowStr });
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
		Logger::Info({ "[发送方] 发送方发送报文:", Logger::getPacketString(this->packets[packetNum]) });
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
		Logger::InfoPrior({ "[发送方] 已接收到的ACK数目:", to_string(ackCount),",新接收到的ACK序号:", to_string(ackPkt.acknum),",此时的窗口内第一个分组的序号:", to_string(firstWaitingAckSeqNum) });
		if (checkSum == ackPkt.checksum && ackPkt.acknum >= this->firstWaitingAckSeqNum) {
			if (ackPkt.acknum == this->packets[0].seqnum) {
				this->ackCount++;
				if (ackCount == 4) {
					//ACK数目大于3，快速重传报文，重启计时器
					pns->stopTimer(SENDER, this->packets[0].seqnum);
					pns->sendToNetworkLayer(RECEIVER, this->packets[0]);
					Logger::InfoPrior({ "[发送方] 冗余ACK大于3,快速重传当前窗口第一个报文:", Logger::getPacketString(packets[0]) });
					printWindow(true);
					pns->startTimer(SENDER, Configuration::TIME_OUT, this->packets[0].seqnum);
					this->ackCount = 0;
					return;
				}
			}
			else this->ackCount = 1;
			if (this->ackCount == 1) {
				//如果ackCount==1，说明窗口内第一个分组发送成功，向右滑动窗口
				int slideLength = ackPkt.acknum - this->firstWaitingAckSeqNum;
				firstWaitingAckSeqNum = ackPkt.acknum;
				Logger::Info({ "[发送方] 发送方接收到ACK报文:", Logger::getPacketString(ackPkt) });
				if (this->firstWaitingAckSeqNum == this->nextSendSeqNum)
					pns->stopTimer(SENDER, this->packets[0].seqnum);
				else {
					pns->stopTimer(SENDER, this->packets[0].seqnum);
					pns->startTimer(SENDER, Configuration::TIME_OUT, this->packets[slideLength].seqnum);
				}
				printWindow(false);
				Logger::Info({ "[发送方] 向右滑动窗口长度:",to_string(slideLength) });
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
	Logger::Warn({ "[发送方] 发送方定时器超时，重发上一次发送的报文:",Logger::getPacketString(this->packets[0]) });
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
