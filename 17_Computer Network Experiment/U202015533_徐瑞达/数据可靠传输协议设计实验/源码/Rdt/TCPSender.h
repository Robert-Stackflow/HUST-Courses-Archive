#pragma once
#include "RdtSender.h"
class TCPSender :public RdtSender
{
private:
	static const int windowLength = 8;
	bool isWindowFull;
	int nextSendSeqNum;
	int packetNum;
	int firstWaitingAckSeqNum;
	Packet packets[windowLength];
	int ackCount=0;
	int current_rcv_ack;
	int last_rcv_ack;
public:
	void printWindow(bool isPrior);
	bool getWaitingState();
	bool send(const Message& message);	//����Ӧ�ò�������Message����NetworkServiceSimulator����,������ͷ��ɹ��ؽ�Message���͵�����㣬����true;�����Ϊ���ͷ����ڵȴ���ȷȷ��״̬���ܾ�����Message���򷵻�false
	void receive(const Packet& ackPkt);	//����ȷ��Ack������NetworkServiceSimulator����	
	void timeoutHandler(int seqNum);	//Timeout handler������NetworkServiceSimulator����
public:
	TCPSender();
	virtual ~TCPSender();
};

