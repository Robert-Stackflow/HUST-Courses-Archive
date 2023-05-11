#include "stdafx.h"
#include "Global.h"
#include "StopWaitRdtSender.h"


StopWaitRdtSender::StopWaitRdtSender() :expectSequenceNumberSend(0), isWaitingState(false)
{
}

StopWaitRdtSender::~StopWaitRdtSender()
{
}

bool StopWaitRdtSender::getWaitingState() {
	return isWaitingState;
}

bool StopWaitRdtSender::send(const Message& message) {
	if (this->isWaitingState) { //���ͷ����ڵȴ�ȷ��״̬
		return false;
	}
	this->packetWaitingAck.acknum = -1; //���Ը��ֶ�
	this->packetWaitingAck.seqnum = this->expectSequenceNumberSend;
	this->packetWaitingAck.checksum = 0;
	memcpy(this->packetWaitingAck.payload, message.data, sizeof(message.data));
	this->packetWaitingAck.checksum = pUtils->calculateCheckSum(this->packetWaitingAck);
	pUtils->printPacket("���ͷ����ͱ���", this->packetWaitingAck);
	pns->startTimer(SENDER, Configuration::TIME_OUT, this->packetWaitingAck.seqnum);			//�������ͷ���ʱ��
	pns->sendToNetworkLayer(RECEIVER, this->packetWaitingAck);								//����ģ�����绷����sendToNetworkLayer��ͨ������㷢�͵��Է�

	this->isWaitingState = true;																					//����ȴ�״̬
	return true;
}

void StopWaitRdtSender::receive(const Packet& ackPkt) {
	if (this->isWaitingState == true) {//������ͷ����ڵȴ�ack��״̬�������´�������ʲô������
		//���У����Ƿ���ȷ
		int checkSum = pUtils->calculateCheckSum(ackPkt);
		//���У�����ȷ������ȷ�����=���ͷ��ѷ��Ͳ��ȴ�ȷ�ϵ����ݰ����
		if (checkSum == ackPkt.checksum && ackPkt.acknum == this->packetWaitingAck.seqnum) {
			this->expectSequenceNumberSend = 1 - this->expectSequenceNumberSend;			//��һ�����������0-1֮���л�
			this->isWaitingState = false;
			pUtils->printPacket("���ͷ���ȷ�յ�ȷ��", ackPkt);
			pns->stopTimer(SENDER, this->packetWaitingAck.seqnum);		//�رն�ʱ��
		}
		else {
			pUtils->printPacket("���ͷ�û����ȷ�յ�ȷ�ϣ��ط��ϴη��͵ı���", this->packetWaitingAck);
			pns->stopTimer(SENDER, this->packetWaitingAck.seqnum);									//���ȹرն�ʱ��
			pns->startTimer(SENDER, Configuration::TIME_OUT, this->packetWaitingAck.seqnum);			//�����������ͷ���ʱ��
			pns->sendToNetworkLayer(RECEIVER, this->packetWaitingAck);								//���·������ݰ�
		}
	}
}

void StopWaitRdtSender::timeoutHandler(int seqNum) {
	//Ψһһ����ʱ��,���迼��seqNum
	pUtils->printPacket("���ͷ���ʱ��ʱ�䵽���ط��ϴη��͵ı���", this->packetWaitingAck);
	pns->stopTimer(SENDER, seqNum);										//���ȹرն�ʱ��
	pns->startTimer(SENDER, Configuration::TIME_OUT, seqNum);			//�����������ͷ���ʱ��
	pns->sendToNetworkLayer(RECEIVER, this->packetWaitingAck);			//���·������ݰ�
}
