#ifndef SR_RDT_SENDER_H
#define SR_RDT_SENDER_H
#pragma once
#include "RdtSender.h"
class SRRdtSender :public RdtSender
{
private:
	static const int windowLength = 8;
	bool isWindowFull;
	int nextSendSeqNum;
	int packetNum;
	int firstWaitingAckSeqNum;
	int isACKReceived[windowLength / 2];
	Packet packets[windowLength / 2];
public:
	bool getWaitingState();
	void printWindow();
	bool send(const Message& message);						//����Ӧ�ò�������Message����NetworkServiceSimulator����,������ͷ��ɹ��ؽ�Message���͵�����㣬����true;�����Ϊ���ͷ����ڵȴ���ȷȷ��״̬���ܾ�����Message���򷵻�false
	void receive(const Packet& ackPkt);						//����ȷ��Ack������NetworkServiceSimulator����	
	void timeoutHandler(int seqNum);					//Timeout handler������NetworkServiceSimulator����

public:
	SRRdtSender();
	virtual ~SRRdtSender();
};
#endif