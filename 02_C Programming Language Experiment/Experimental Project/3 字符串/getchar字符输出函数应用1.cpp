#include<stdio.h>
int main(void)
{
	char c1,c2,c3;
	//�ո�ͻ��з�Ҳ��Ϊһ���ַ����Ա���ȡ 
	//�ո��ֵ��32�����з���10
	//����������gets����ʱ����ͨ��getchar()������ջ��з���ո� 
	c1=getchar();
	c2=getchar();
	c3=getchar();
	printf("\n%c%c%c",c1,c2,c3);
	printf("\n%d %d %d",c1,c2,c3);
	return 0;
 } 
