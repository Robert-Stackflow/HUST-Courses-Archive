#include "stdio.h"
void swap(int u,int v); /* ������������ԭ��*/
int main(void)
{
	int x,y; /* �������ͱ���x,y*/
	printf("input two integers for x and y please!\n");
	scanf("%d%d",&x,&y); /* �Ӽ��������x,y��ֵ */
	printf("in function main, before swap,x=%d and y=%d\n",x,y);
	swap(x,y); /* ��x,yֵ֮Ϊʵ�ε��ý������� */
	printf("in function main, after swap,x=%d and y=%d\n",x,y);
	return 0;
}
void swap(int u,int v) /* ���彻������ */
{
	int t; /* �����ֲ����ͱ���t */
	printf("in function swap, before swap,u=%d and v=%d\n",u,v);
	t=u;u=v;v=t; /* ����u,vֵ֮ */
	printf("in function swap, after swap,u=%d and v=%d\n",u,v);
}

