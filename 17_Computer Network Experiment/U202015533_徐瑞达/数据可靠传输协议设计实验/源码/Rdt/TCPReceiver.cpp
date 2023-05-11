#include "stdafx.h"
#include "Global.h"
#include "TCPReceiver.h"
#include "Logger.h"
TCPReceiver::TCPReceiver() :seq(1)
{
	lastAckPkt.acknum = 0;
	lastAckPkt.checksum = 0;
	lastAckPkt.seqnum = -1;
	for (int i = 0; i < Configuration::PAYLOAD_SIZE; i++)
		lastAckPkt.payload[i] = '.';
	lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
}

TCPReceiver::~TCPReceiver()
{
}

void TCPReceiver::receive(const Packet& packet)
{
	int checkSum = pUtils->calculateCheckSum(packet);
	if (checkSum == packet.checksum && this->seq == packet.seqnum) {
		Logger::Info({ "[���շ�] ���շ���ȷ�յ�����", Logger::getPacketString(packet) });
		Message msg;
		memcpy(msg.data, packet.payload, sizeof(packet.payload));
		pns->delivertoAppLayer(RECEIVER, msg);
		this->lastAckPkt.acknum = this->seq + 1;
		this->lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
		Logger::Info({ "[���շ�] ���շ����ͷ�����ȷ�ϱ���:", Logger::getPacketString(lastAckPkt) });
		pns->sendToNetworkLayer(SENDER, lastAckPkt);
		this->seq++;
	}
	else {
		if (packet.acknum != seq)
			Logger::Error({ "[���շ�] ���շ�δ�յ���ȷ����[������Ŵ���]:",Logger::getPacketString(packet) });
		else
			Logger::Error({ "[���շ�] ���շ�δ�յ���ȷ����[����ʹ���]:",Logger::getPacketString(packet) });
		Logger::InfoPrior({ "[���շ�] ���շ���������ACK:", Logger::getPacketString(lastAckPkt) });
		pns->sendToNetworkLayer(SENDER, lastAckPkt);
	}
}
