#include "stdio.h"
enum color{ OFF=0,RED=1,YELLOW=2,GREEN=3};
struct traffic_light{
	unsigned short int east:2;	/* �����״̬�ֶ� */
	unsigned short int south:2;	/* �����״̬�ֶ� */
	unsigned short int west:2;	/* �����״̬�ֶ� */
	unsigned short int north:2;	/* �����״̬�ֶ� */
	unsigned short int reserve:8; /* �����ֶ� */
	unsigned short int east_on:4;	/* ����ƿ�ͨʱ���ֶ� */
	unsigned short int south_on:4;	/* ����ƿ�ͨʱ���ֶ� */
	unsigned short int west_on:4;	/* ����ƿ�ͨʱ���ֶ� */
	unsigned short int north_on:4;	/* ����ƿ�ͨʱ���ֶ� */
};

int main(void)
{		struct traffic_light Jiedaokou={0,0,0,0,0,0,0,0,0};
		Jiedaokou.west=GREEN;Jiedaokou.west_on=5;
		printf("Jiedaokou.west=%u\t",Jiedaokou.west);
		printf("Jiedaokou.west_on=%u\n",Jiedaokou.west_on);
		printf("Jiedaokou.east=%u\t",Jiedaokou.east);
		printf("Jiedaokou.east_on=%u\n",Jiedaokou.east_on);
		return 0;
}
