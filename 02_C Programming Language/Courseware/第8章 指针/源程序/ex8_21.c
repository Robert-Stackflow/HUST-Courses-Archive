#include "stdio.h"
int main(void)
{	int x0[5],x1[5],x2[5],x3[5],x4[5];/*����5��һά����*/
	int *p[5],i,j;/*����ָ������p*/
	p[0]=x0;p[1]=x1;p[2]=x2,p[3]=x3,p[4]=x4;/*��ָ�������Ա��ֵ*/
	for(i=0;i<5;i++)
		for(j=0;j<5;j++)
			if(i==j) p[i][j]=1;/*��p��ʾ��ά����,��Ԫ�ظ�ֵ*/
			else p[i][j]=0;
	for(i=0;i<5;i++){
		for(j=0;j<5;j++)
			printf("%4d",p[i][j]);/*ָ�������ʾ��ά����Ԫ��*/
		printf("\n");
	}
	return 0;
}
