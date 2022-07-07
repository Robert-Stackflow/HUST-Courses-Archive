#include "stdio.h"
#define N 6
int main(void)
{	int i,a[N],*p[N],sum=0;
	for(i=0;i<N;i++){
		p[i]=&a[i];
		scanf("%d",p[i]);
		sum+=*p[i];
	}
	for(i=0;i<N;i++)
		printf("p[%d]=%p,result=%d\n",i,p[i],*p[i]);
	printf("sum=%d\n",sum);
	return 0;
}