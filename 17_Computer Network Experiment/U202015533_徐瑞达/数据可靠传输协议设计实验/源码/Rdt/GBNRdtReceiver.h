#ifndef GBN_RDT_RECEIVER_H
#define GBN_RDT_RECEIVER_H
#pragma once
#include "RdtReceiver.h"
class GBNRdtReceiver :public RdtReceiver
{
private:
	int seq;
	Packet lastAckPkt;
public:
	GBNRdtReceiver();
	virtual ~GBNRdtReceiver();
public:
	void receive(const Packet& packet);
};
#endif