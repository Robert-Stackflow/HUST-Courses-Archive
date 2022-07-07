#include<stdio.h>
int main(void)
{
	int budget[12],left[12],remaining=0,bank=0;
	float benefit=0;
	for(int i=0;i<12;i++)
	{
	scanf("%d",&budget[i]);
	left[i]=300-budget[i];//存储每月结余 
	}
	for(int i=0;i<12;i++)
	{
		remaining+=left[i];//计算截止到当月的结余 
		if(remaining<0) {printf("-%d\n",i+1);return 0;}
		//当截止到当月的结余小于0时则输出并结束程序 
		if(remaining/100) 
		{
			bank+=100*(remaining/100);
			//否则将超过一百的部分存入银行 
			remaining-=100*(remaining/100);
			//将结余减去对应的值 
		}
	}
	benefit=remaining+bank+bank*0.2;
	printf("%.f",benefit);
}
