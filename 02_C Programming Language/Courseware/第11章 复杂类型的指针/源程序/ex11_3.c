#include "stdio.h"
#include "stdlib.h"
#define I 2
#define J 3
#define K 4
int main(void)
{	int v[I][J][K],(*p)[J][K]=v,(*p1)[K]=v[0],n=1;/*p��ָ����һ�������ָ��*/
	int i,j,k;	/*�����p1��ָ���¶��������ָ��*/
	for(i=0;i<I;i++)
		for(j=0;j<J;j++)
			for(k=0;k<K;k++)/* ��ָ���¶��������ָ�������������Ԫ�� */
				*(*(p1+j)+k+i*J*K)=n++;
	/* Ҳ������*(*(*(p+i)+j)+k)=n++; Ҳ������v[i][j][k]=n++; */
	for(i=0;i<I;i++){
		for(j=0;j<J;j++){ /* ��ָ����һ�������ָ�������������Ԫ�� */
			for(k=0;k<K;k++)
				printf("%4d",*(*(*(p+i)+j)+k));
			/* Ҳ������printf("%d   ",*(*(p1+j)+k+i*J*K)); */
			/* Ҳ������printf("%d  ",v[i][j][k]); */
				printf("\n");
		}
		printf("\n");
	}
	return 0;
}

