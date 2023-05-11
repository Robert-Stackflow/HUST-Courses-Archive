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
		Logger::Info({ "[接收方] 接收方正确收到报文", Logger::getPacketString(packet) });
		Message msg;
		memcpy(msg.data, packet.payload, sizeof(packet.payload));
		pns->delivertoAppLayer(RECEIVER, msg);
		this->lastAckPkt.acknum = this->seq + 1;
		this->lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
		Logger::Info({ "[接收方] 接收方向发送方发送确认报文:", Logger::getPacketString(lastAckPkt) });
		pns->sendToNetworkLayer(SENDER, lastAckPkt);
		this->seq++;
	}
	else {
		if (packet.acknum != seq)
			Logger::Error({ "[接收方] 接收方未收到正确报文[报文序号错误]:",Logger::getPacketString(packet) });
		else
			Logger::Error({ "[接收方] 接收方未收到正确报文[检验和错误]:",Logger::getPacketString(packet) });
		Logger::InfoPrior({ "[接收方] 接收方发送冗余ACK:", Logger::getPacketString(lastAckPkt) });
		pns->sendToNetworkLayer(SENDER, lastAckPkt);
	}
}
