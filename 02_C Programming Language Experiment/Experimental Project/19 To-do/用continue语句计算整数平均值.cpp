#include<stdio.h>
int main(void)
{
	long long sum,i,count1,d;
	for(sum=i=count1=0;i<10;++i)
	{
		scanf("%lld",&d);
		if(d<=0)
			continue;
		sum+=d;
		++count1;
	}
	if(count1)
		printf("numbers=%lld, average=%.6f\n",count1,(double)sum/count1);
    else
        printf("numbers=0, average=0.000000");
	return 0;
}
