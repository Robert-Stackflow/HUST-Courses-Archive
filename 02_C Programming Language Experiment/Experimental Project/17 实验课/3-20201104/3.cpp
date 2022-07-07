#include<stdio.h> 
double abs(double a)//定义绝对值函数 
{
	if(a<0)
		a=-a;
	return a;
}
int main(void)
{
	double a,b,max=0;
	int day,flag=1;
	while(flag){
	printf("请输入天数:\n");
	scanf("%d",&day);
	printf("请输入这些天的收盘价格:\n");
	scanf("%lf",&b);//提示输入收盘天数与每天收盘价格 
	for(int i=1;i<day;++i)
		{
			a=b;
			scanf("%lf",&b);
			if(abs(a-b)>max)//if语句将每次的最大波动值赋给max	
				max=abs(a-b);
		} 
	printf("\n这%d天最大波动值为%.2lf\n",day,max);//输出最大波动值 
	max=0;
	printf("\n是否需要继续计算？(0 or 1)\n\n");
	scanf("%d",&flag);//用于决定是否继续循环的语句
	}
	
	return 0;
}
