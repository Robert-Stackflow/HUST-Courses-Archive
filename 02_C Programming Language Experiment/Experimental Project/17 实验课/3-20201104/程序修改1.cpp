#include<stdio.h>
#include<math.h>
int main(void)
{
	int i,x,k,flag=0;
	printf("本程序判断合数,请输入大于1的整数,以ctrl+Z结束\n");
	while(scanf("%d",&x)!=EOF)
	{
	for(i=2,k=x>>1;i<=k;i++)
	{
		if(x%i==0)
			{
				flag=1;
				k=i;
			}
	}	
	if(flag==1)
		printf("%d是合数\n",x);
	else
		printf("%d不是合数\n",x);
	flag=0;
	}
	return 0;
 } 
