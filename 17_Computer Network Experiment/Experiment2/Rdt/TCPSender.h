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
	bool send(const Message& message);	//发送应用层下来的Message，由NetworkServiceSimulator调用,如果发送方成功地将Message发送到网络层，返回true;如果因为发送方处于等待正确确认状态而拒绝发送Message，则返回false
	void receive(const Packet& ackPkt);	//接受确认Ack，将被NetworkServiceSimulator调用	
	void timeoutHandler(int seqNum);	//Timeout handler，将被NetworkServiceSimulator调用
public:
	TCPSender();
	virtual ~TCPSender();
};

