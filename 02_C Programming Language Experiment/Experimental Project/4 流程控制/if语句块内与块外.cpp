#include<stdio.h> 
int main(void)
{
	int x=5,y=1,t=-1;
	if(x>y)
	{
		int x=100,y=1000;/*�����y=1000ȥ����? ���ȥ��int�أ����һ����int,һ��û��int�أ� */ 
		t=x;
		x=y;
		y=t;
		printf("x=%d,y=%d,t=%d\n",x,y,t);
	 } 
	 printf("x=%d,y=%d,t=%d\n",x,y,t);
	 return 0;
}
