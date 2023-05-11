#include "stdafx.h"
#include "Global.h"
#include "SRRdtReceiver.h"
#include "Logger.h"
#include <string>
#pragma warning(disable:26495)
SRRdtReceiver::SRRdtReceiver() :firstWaitingSeqNum(0), packetNum(0)
{
	Ack.acknum = -1;
	Ack.checksum = 0;
	Ack.seqnum = -1;
	for (int i = 0; i < Configuration::PAYLOAD_SIZE; i++)
		Ack.payload[i] = '.';
	Ack.checksum = pUtils->calculateCheckSum(Ack);
}

SRRdtReceiver::~SRRdtReceiver()
{
}

void SRRdtReceiver::printWindow()
{
	string windowStr = "order\t";
	for (int i = 0; i < windowLength / 2; i++)
		windowStr += to_string(i), windowStr += "\t";
	windowStr += "\nseqnum\t";
	for (int i = 0; i < windowLength / 2; i++) {
		if (isPacketReceived[i])
			windowStr += to_string(packets[i].seqnum), windowStr += "\t";
		else
			windowStr += '-', windowStr += "\t";
	}
	Logger::Info({ "[���շ�] ��ǰ����Ϊ:\n",windowStr });
}

void SRRdtReceiver::receive(const Packet& packet)
{
	if (this->packetNum == 0)
		for (int i = 0; i < windowLength / 2; i++)
			isPacketReceived[i] = 0;
	int checksum = pUtils->calculateCheckSum(packet);
	if (checksum == packet.checksum) {
		bool isInWindow = false;
		for (int i = 0; i < windowLength / 2; i++) {
			if (packet.seqnum == (firstWaitingSeqNum + i) % windowLength) {
				isInWindow = true;
				break;
			}
		}
		if (isInWindow) {
			//������յ��ķ�������ڴ�����
			for (int i = 0; i < windowLength / 2; i++) {
				if (packet.seqnum == (this->firstWaitingSeqNum + i) % windowLength) {
					packets[i] = packet;
					isPacketReceived[i] = true;
					Logger::Info({ "[���շ�] ���շ���ȷ�յ����ͷ��ı���:", Logger::getPacketString(this->packets[i]) });
					this->Ack.acknum = packets[0].seqnum;
					this->Ack.checksum = pUtils->calculateCheckSum(Ack);
					pns->sendToNetworkLayer(SENDER, this->Ack);
					Logger::Info({ "[���շ�] ���շ�����ȷ�ϱ���:", Logger::getPacketString(this->packets[i]) });
				}
			}
			if (isPacketReceived[0]) {
				Logger::Info({ "[���շ�] ���շ��յ����Ǵ����ڵ�һ������ı���" });
				int slideLength = 0;
				for (int i = 0; i < windowLength / 2 && this->isPacketReceived[i]; i++)
					slideLength++;
				for (int i = 0; i < slideLength; i++) {
					Message msg;
					memcpy(msg.data, this->packets[i].payload, sizeof(this->packets[i].payload));
					pns->delivertoAppLayer(RECEIVER, msg);
				}
				printWindow();
				Logger::Info({ "[���շ�] ���һ������ڳ���:",to_string(slideLength) });
				for (int i = 0; i < this->packetNum - slideLength; i++)
					this->packets[i] = this->packets[i + slideLength];
				this->packetNum -= slideLength;
				this->firstWaitingSeqNum = (this->firstWaitingSeqNum + slideLength) % windowLength;
				for (int i = 0; i < windowLength / 2; i++)
					isPacketReceived[i] = 0;
				printWindow();
			}
		}
		else {
			Logger::Warn({ "[���շ�] ���շ��յ����ͷ��ķǴ����ڱ���:", Logger::getPacketString(packet) });
			this->Ack.acknum = packet.seqnum;
			this->Ack.checksum = pUtils->calculateCheckSum(Ack);
			pns->sendToNetworkLayer(SENDER, this->Ack);
		}
	}
	else {
		Logger::Error({ "[���շ�] ���շ�δ��ȷ�յ�����[����ʹ���]:",  Logger::getPacketString(packet) });
	}
}
