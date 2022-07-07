#include<stdio.h> 
int main(void)
{
	int x=5,y=1,t=-1;
	if(x>y)
	{
		int x=100,y=1000;/*如果把y=1000去掉呢? 如果去掉int呢？如果一个用int,一个没用int呢？ */ 
		t=x;
		x=y;
		y=t;
		printf("x=%d,y=%d,t=%d\n",x,y,t);
	 } 
	 printf("x=%d,y=%d,t=%d\n",x,y,t);
	 return 0;
}
