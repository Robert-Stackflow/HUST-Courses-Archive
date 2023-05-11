#ifndef SR_RDT_RECEIVER_H
#define SR_RDT_RECEIVER_H
#pragma once
#include "RdtReceiver.h"
class SRRdtReceiver :public RdtReceiver
{
private:
	static const int windowLength = 8;
	Packet Ack;
	int packetNum;
	int firstWaitingSeqNum;
	Packet packets[windowLength / 2];
	bool isPacketReceived[windowLength / 2];
public:
	SRRdtReceiver();
	virtual ~SRRdtReceiver();

public:
	void printWindow();
	void receive(const Packet& packet);	//接收报文，将被NetworkService调用
};
#endif