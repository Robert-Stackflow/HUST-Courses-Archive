#include<stdio.h>
int main(void)
{
	int budget[12],left[12],remaining=0,bank=0;
	float benefit=0;
	for(int i=0;i<12;i++)
	{
	scanf("%d",&budget[i]);
	left[i]=300-budget[i];//�洢ÿ�½��� 
	}
	for(int i=0;i<12;i++)
	{
		remaining+=left[i];//�����ֹ�����µĽ��� 
		if(remaining<0) {printf("-%d\n",i+1);return 0;}
		//����ֹ�����µĽ���С��0ʱ��������������� 
		if(remaining/100) 
		{
			bank+=100*(remaining/100);
			//���򽫳���һ�ٵĲ��ִ������� 
			remaining-=100*(remaining/100);
			//�������ȥ��Ӧ��ֵ 
		}
	}
	benefit=remaining+bank+bank*0.2;
	printf("%.f",benefit);
}
