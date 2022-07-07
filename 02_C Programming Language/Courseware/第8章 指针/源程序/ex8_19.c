#include "stdio.h"
#define N 6
int main(void)
{	int i,*p[N],sum=0;/*注意：p中的元素都是悬挂指针 */
	for(i=0;i<N;i++){
		scanf("%d",p[i]); /* 对悬挂指针p[i]赋值，副作用极大。 */
		sum+=*p[i];
	}
	for(i=0;i<N;i++)
		printf("p[%d]=%p,result=%d\n",i,p[i],*p[i]);
	printf("sum=%d\n",sum);
	return 0;
}
