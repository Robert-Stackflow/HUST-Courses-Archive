#include "stdio.h"
#define N 6
int main(void)
{	int i,*p[N],sum=0;/*ע�⣺p�е�Ԫ�ض�������ָ�� */
	for(i=0;i<N;i++){
		scanf("%d",p[i]); /* ������ָ��p[i]��ֵ�������ü��� */
		sum+=*p[i];
	}
	for(i=0;i<N;i++)
		printf("p[%d]=%p,result=%d\n",i,p[i],*p[i]);
	printf("sum=%d\n",sum);
	return 0;
}
