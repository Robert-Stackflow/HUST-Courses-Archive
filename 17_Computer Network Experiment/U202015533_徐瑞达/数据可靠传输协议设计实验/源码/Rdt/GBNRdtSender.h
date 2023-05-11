#ifndef GBN_RDT_SENDER_H
#define GBN_RDT_SENDER_H
#pragma once
#include "RdtSender.h"
#include <math.h>
class GBNRdtSender :public RdtSender
{
private:
	static const int windowLength = 8;
	bool isWindowFull;
	int nextSendSeqNum;
	int packetNum;
	int firstWaitingAckSeqNum;
	Packet packets[windowLength];
public:
	void printWindow();
	bool getWaitingState();
	bool send(const Message& message);	//����Ӧ�ò�������Message����NetworkServiceSimulator����,������ͷ��ɹ��ؽ�Message���͵�����㣬����true;�����Ϊ���ͷ����ڵȴ���ȷȷ��״̬���ܾ�����Message���򷵻�false
	void receive(const Packet& ackPkt);	//����ȷ��Ack������NetworkServiceSimulator����	
	void timeoutHandler(int seqNum);	//Timeout handler������NetworkServiceSimulator����
public:
	GBNRdtSender();
	virtual ~GBNRdtSender();
};
#endif