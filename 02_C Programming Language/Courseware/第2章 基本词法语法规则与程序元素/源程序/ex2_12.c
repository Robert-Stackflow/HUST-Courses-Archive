#include<stdio.h>
#define N  10
int main(void)
{
	int i,sum;    /* i��ѭ��������sum���ۼ�����������ź�ֵ */
    i=1;          /* ѭ��������ʼ��Ϊ1  */
	sum=0;        /* �ۼ�����ʼ��Ϊ0  */
	while(i<=N)   /* ѭ����� 1+2+...+N */
		sum+=i++;          /* �ȼ��� sum=sum+i,i++; */
	printf("sum=%d\n",sum);  /* �����ֵ */
	return 0;
}
