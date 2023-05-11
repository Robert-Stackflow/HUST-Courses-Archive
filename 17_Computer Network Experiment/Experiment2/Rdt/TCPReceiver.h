#pragma once
#include "RdtReceiver.h"
class TCPReceiver :public RdtReceiver
{
private:
	int seq;
	Packet lastAckPkt;
public:
	TCPReceiver();
	virtual ~TCPReceiver();
public:
	void receive(const Packet& packet);
};

