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
		Logger::Info({ "[接收方] 接收方正确收到发送方的报文:",Logger::getPacketString(packet) });
		Message msg;
		memcpy(msg.data, packet.payload, sizeof(packet.payload));
		pns->delivertoAppLayer(RECEIVER, msg);
		lastAckPkt.acknum = packet.seqnum;
		lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
		Logger::Info({ "[接收方] 接收方发送确认报文:",Logger::getPacketString(lastAckPkt) });
		pns->sendToNetworkLayer(SENDER, lastAckPkt);
		this->seq++;
	}
	else{
		//如果收到的报文错误(失序或受损)，则发送最后一次确认的报文
		if (packet.acknum != seq)
			Logger::Error({ "[接收方] 接收方未收到正确报文[报文序号错误]:",Logger::getPacketString(packet) });
		else
			Logger::Error({ "[接收方] 接收方未收到正确报文[检验和错误]:",Logger::getPacketString(packet) });
		Logger::Info({ "[接收方] 接收方重新发送上次的确认报文:",Logger::getPacketString(lastAckPkt) });
		pns->sendToNetworkLayer(SENDER, lastAckPkt);
	}
}
