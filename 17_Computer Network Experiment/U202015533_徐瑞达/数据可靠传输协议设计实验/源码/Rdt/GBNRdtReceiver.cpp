#include "stdafx.h"
#include "Global.h"
#include "GBNRdtReceiver.h"
#include "Logger.h"

GBNRdtReceiver::GBNRdtReceiver() :seq(1)
{
	lastAckPkt.acknum = 0;
	lastAckPkt.seqnum = -1;
	lastAckPkt.checksum = 0;
	for (int i = 0; i < Configuration::PAYLOAD_SIZE; i++)
		lastAckPkt.payload[i] = '.';
	lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
}

GBNRdtReceiver::~GBNRdtReceiver()
{
}

void GBNRdtReceiver::receive(const Packet& packet)
{
	int checkSum = pUtils->calculateCheckSum(packet);
	if (checkSum == packet.checksum && this->seq == packet.seqnum){
		Logger::Info({ "[���շ�] ���շ���ȷ�յ����ͷ��ı���:",Logger::getPacketString(packet) });
		Message msg;
		memcpy(msg.data, packet.payload, sizeof(packet.payload));
		pns->delivertoAppLayer(RECEIVER, msg);
		lastAckPkt.acknum = packet.seqnum;
		lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
		Logger::Info({ "[���շ�] ���շ�����ȷ�ϱ���:",Logger::getPacketString(lastAckPkt) });
		pns->sendToNetworkLayer(SENDER, lastAckPkt);
		this->seq++;
	}
	else{
		//����յ��ı��Ĵ���(ʧ�������)���������һ��ȷ�ϵı���
		if (packet.acknum != seq)
			Logger::Error({ "[���շ�] ���շ�δ�յ���ȷ����[������Ŵ���]:",Logger::getPacketString(packet) });
		else
			Logger::Error({ "[���շ�] ���շ�δ�յ���ȷ����[����ʹ���]:",Logger::getPacketString(packet) });
		Logger::Info({ "[���շ�] ���շ����·����ϴε�ȷ�ϱ���:",Logger::getPacketString(lastAckPkt) });
		pns->sendToNetworkLayer(SENDER, lastAckPkt);
	}
}
