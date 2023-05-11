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
	Logger::Info({ "[���ͷ�] ��ǰ����Ϊ:\n",windowStr });
}
bool SRRdtSender::send(const Message& message)
{
	if (packetNum < windowLength / 2) {
		//��������С�ڴ��ڳ���ʱ�����ͷ���
		//���������Ϊ0�����ʼ��ACK����
		if (packetNum == 0)
			for (int i = 0; i < windowLength / 2; i++)
				this->isACKReceived[i] = 0;
		this->isWindowFull = false;
		this->packets[this->packetNum].acknum = -1;
		this->packets[this->packetNum].seqnum = this->nextSendSeqNum;
		this->packets[this->packetNum].checksum = 0;
		memcpy(this->packets[this->packetNum].payload, message.data, sizeof(message.data));
		this->packets[this->packetNum].checksum = pUtils->calculateCheckSum(this->packets[this->packetNum]);
		Logger::Info({ "[���ͷ�] ���ͷ����ͱ���:", Logger::getPacketString(this->packets[this->packetNum]) });
		pns->startTimer(SENDER, Configuration::TIME_OUT, this->packets[this->packetNum].seqnum);
		pns->sendToNetworkLayer(RECEIVER, this->packets[this->packetNum]);
		this->packetNum++;
		//���������0-7��ѭ��
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
				//�����յ���һ�������ACKʱ�����һ�������
				Logger::Info({ "[���ͷ�] ���ͷ��յ������ڵ�һ�������ACK:", Logger::getPacketString(ackPkt) });
				//�������һ������ڳ���
				int slideLength = 0;
				pns->stopTimer(SENDER, this->packets[0].seqnum);
				for (int i = 0; i < windowLength / 2; i++) {
					if (isACKReceived[i] == 0)
						break;
					else
						slideLength++;
				}
				printWindow();
				Logger::Info({ "[���ͷ�] ���һ������ڳ���:",to_string(slideLength) });
				if (slideLength != this->packetNum) {
					//������ҳ��Ȳ����ڷ�����������Ҫ�ƶ���������
					for (int i = 0; i < packetNum - slideLength; i++) {
						this->packets[i] = this->packets[i + slideLength];
						this->isACKReceived[i] = this->isACKReceived[i + slideLength];
					}
					//��ʼ�������봰�ڵ�ACK����
					for (int j = this->packetNum - slideLength; j < windowLength / 2; j++)
						isACKReceived[j] = 0;
				}
				else {
					//������ҳ��ȵ��ڷ����������ʼ���������鼴��
					for (int i = 0; i < windowLength / 2; i++)
						isACKReceived[i] = 0;
				}
				this->isWindowFull = false;
				this->packetNum -= slideLength;
				this->firstWaitingAckSeqNum = (this->firstWaitingAckSeqNum + slideLength) % windowLength;
				printWindow();
			}
			else {
				//�����յ��ǵ�һ�������ACKʱ���رն�Ӧ��ʱ��
				pns->stopTimer(SENDER, this->packets[pos].seqnum);
				Logger::Info({ "[���ͷ�] ���ͷ��յ������ڷǵ�һ�������ACK:", Logger::getPacketString(ackPkt) });
			}
		}
		else {
			//�����յ��Ǵ����ڷ����ACKʱ���رն�Ӧ��ʱ��
			pns->stopTimer(SENDER, ackPkt.acknum);
			Logger::Warn({ "[���ͷ�] ���ͷ��յ��Ǵ����ڵ�ACK:", Logger::getPacketString(ackPkt) });
		}
	}
	else {
		Logger::Error({ "[���ͷ�] ���ͷ��յ���ACK����ʹ���:", Logger::getPacketString(ackPkt) });
	}
}

void SRRdtSender::timeoutHandler(int seqNum)
{
	int pos = 0;
	for (int i = 0; i < packetNum; i++)
		if (seqNum == packets[i].seqnum)
			pos = i;
	//���·���seqNum��Ӧ���飬��������ʱ��
	pns->stopTimer(SENDER, seqNum);
	Logger::Warn({ "[���ͷ�] ���ͷ���ʱ����ʱ�����·��ͱ���:", Logger::getPacketString(this->packets[pos]) });
	pns->sendToNetworkLayer(RECEIVER, this->packets[pos]);
	pns->startTimer(SENDER, Configuration::TIME_OUT, seqNum);
}

SRRdtSender::SRRdtSender() :packetNum(0), isWindowFull(false), nextSendSeqNum(0), firstWaitingAckSeqNum(0)
{
}

SRRdtSender::~SRRdtSender()
{
}
