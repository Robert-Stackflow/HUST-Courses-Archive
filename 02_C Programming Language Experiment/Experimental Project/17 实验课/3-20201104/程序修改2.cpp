#include<stdio.h>
#include<math.h>
int main(void)
{
	int i,x,k,flag=0;
	printf("本程序判断合数,请输入大于1的整数,以ctrl+Z结束\n");
	while(scanf("%d",&x)!=EOF)
	{
	int i=2;
	int k;
	k=x>>1;
	do{
		if(x%i==0)
			{
				flag=1;
				break;
			}
			i++;
	}while(i<=k);	
	if(flag==1)
		printf("%d是合数\n",x);
	else
		printf("%d不是合数\n",x);
	flag=0;
	}
	return 0;
 } 
