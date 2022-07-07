#include<stdio.h> 
int main(void)
{
	for(int i=100;i<=999;i++) //for循环语句确定是三位数 
	{
		int t;
		t=i*i;
		if(t%1000==i)//if判断该数平方末三位是否是该数本身 
			printf("%d\n",i);//若结果为真，输出该值。 
	}
	return 0;
}
