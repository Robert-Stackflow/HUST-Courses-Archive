#include "stdio.h"
void swap(int *p1,int *p2); /* ����ָ������Ľ�������ԭ��*/
int main(void)
{
	int x,y;
	printf("input two integers for x and y please!\n");
	scanf("%d%d",&x,&y); /* �Ӽ��������x,y��ֵ */
	printf("before swap,x=%d and y=%d\n",x,y);
	swap(&x,&y); /*��x,yַ֮Ϊʵ��*/
	printf("after swap,x=%d and y=%d\n",x,y);
	return 0;
}
void swap(int *p1,int *p2)
{
	int t;
	t=*p1;*p1=*p2;*p2=t; /* ����ָ��p1,p2��ָ����ֵ֮ */
}

