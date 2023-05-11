#include "stdafx.h"
#include "Global.h"
#include "SRRdtSender.h"
#include "Logger.h"
#include <string>
#pragma warning(disable:26495)
bool SRRdtSender::getWaitingState()
{
	return isWindowFull;
}
void SRRdtSender::printWindow()
{
	string windowStr = "order\t";
	for (int i = 0; i < windowLength / 2; i++)
		windowStr += to_string(i), windowStr += "\t";
	windowStr += "\nseqnum\t";
	for (int i = 0; i < windowLength / 2; i++) {
		if (i < packetNum)
			windowStr += to_string(packets[i].seqnum), windowStr += "\t";
		else
			windowStr += '-', windowStr += "\t";
	}
	Logger::Info({ "[发送方] 当前窗口为:\n",windowStr });
}
bool SRRdtSender::send(const Message& message)
{
	if (packetNum < windowLength / 2) {
		//当分组数小于窗口长度时，发送分组
		//如果分组数为0，则初始化ACK数组
		if (packetNum == 0)
			for (int i = 0; i < windowLength / 2; i++)
				this->isACKReceived[i] = 0;
		this->isWindowFull = false;
		this->packets[this->packetNum].acknum = -1;
		this->packets[this->packetNum].seqnum = this->nextSendSeqNum;
		this->packets[this->packetNum].checksum = 0;
		memcpy(this->packets[this->packetNum].payload, message.data, sizeof(message.data));
		this->packets[this->packetNum].checksum = pUtils->calculateCheckSum(this->packets[this->packetNum]);
		Logger::Info({ "[发送方] 发送方发送报文:", Logger::getPacketString(this->packets[this->packetNum]) });
		pns->startTimer(SENDER, Configuration::TIME_OUT, this->packets[this->packetNum].seqnum);
		pns->sendToNetworkLayer(RECEIVER, this->packets[this->packetNum]);
		this->packetNum++;
		//分组序号在0-7内循环
		this->nextSendSeqNum = (this->nextSendSeqNum + 1) % windowLength;
		if (this->packetNum == windowLength / 2)
			this->isWindowFull = true;
		return true;
	}
	else {
		this->isWindowFull = true;
		return false;
	}
}

void SRRdtSender::receive(const Packet& ackPkt)
{
	int check_sum = pUtils->calculateCheckSum(ackPkt);
	if (check_sum == ackPkt.checksum) {
		int pos = 0;
		bool isInWindow = false;
		for (int i = 0; i < packetNum; i++)
			if (ackPkt.acknum == packets[i].seqnum)
				isACKReceived[i] = 1, pos = i, isInWindow = true;
		if (isInWindow) {
			if (isACKReceived[0] == 1) {
				//当接收到第一个分组的ACK时，向右滑动窗口
				Logger::Info({ "[发送方] 发送方收到窗口内第一个分组的ACK:", Logger::getPacketString(ackPkt) });
				//计算向右滑动窗口长度
				int slideLength = 0;
				pns->stopTimer(SENDER, this->packets[0].seqnum);
				for (int i = 0; i < windowLength / 2; i++) {
					if (isACKReceived[i] == 0)
						break;
					else
						slideLength++;
				}
				printWindow();
				Logger::Info({ "[发送方] 向右滑动窗口长度:",to_string(slideLength) });
				if (slideLength != this->packetNum) {
					//如果向右长度不等于分组数，则需要移动数组内容
					for (int i = 0; i < packetNum - slideLength; i++) {
						this->packets[i] = this->packets[i + slideLength];
						this->isACKReceived[i] = this->isACKReceived[i + slideLength];
					}
					//初始化新移入窗口的ACK数组
					for (int j = this->packetNum - slideLength; j < windowLength / 2; j++)
						isACKReceived[j] = 0;
				}
				else {
					//如果向右长度等于分组数，则初始化整个数组即可
					for (int i = 0; i < windowLength / 2; i++)
						isACKReceived[i] = 0;
				}
				this->isWindowFull = false;
				this->packetNum -= slideLength;
				this->firstWaitingAckSeqNum = (this->firstWaitingAckSeqNum + slideLength) % windowLength;
				printWindow();
			}
			else {
				//当接收到非第一个分组的ACK时，关闭对应计时器
				pns->stopTimer(SENDER, this->packets[pos].seqnum);
				Logger::Info({ "[发送方] 发送方收到窗口内非第一个分组的ACK:", Logger::getPacketString(ackPkt) });
			}
		}
		else {
			//当接收到非窗口内分组的ACK时，关闭对应计时器
			pns->stopTimer(SENDER, ackPkt.acknum);
			Logger::Warn({ "[发送方] 发送方收到非窗口内的ACK:", Logger::getPacketString(ackPkt) });
		}
	}
	else {
		Logger::Error({ "[发送方] 发送方收到的ACK检验和错误:", Logger::getPacketString(ackPkt) });
	}
}

void SRRdtSender::timeoutHandler(int seqNum)
{
	int pos = 0;
	for (int i = 0; i < packetNum; i++)
		if (seqNum == packets[i].seqnum)
			pos = i;
	//重新发送seqNum对应分组，并重启计时器
	pns->stopTimer(SENDER, seqNum);
	Logger::Warn({ "[发送方] 发送方定时器超时，重新发送报文:", Logger::getPacketString(this->packets[pos]) });
	pns->sendToNetworkLayer(RECEIVER, this->packets[pos]);
	pns->startTimer(SENDER, Configuration::TIME_OUT, seqNum);
}

SRRdtSender::SRRdtSender() :packetNum(0), isWindowFull(false), nextSendSeqNum(0), firstWaitingAckSeqNum(0)
{
}

SRRdtSender::~SRRdtSender()
{
}
