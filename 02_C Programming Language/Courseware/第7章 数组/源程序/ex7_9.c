#include "stdio.h"
void bubble_sort(int a[],int n);/*ð��������ԭ������*/
int main(void)
{	int x[]={31,25,12,86,42,6};
	bubble_sort(x,6); /*����ð����������ʵ������������������Ԫ�ظ���*/
	return 0;
}
void bubble_sort(int a[],int n)     /*����ð�����������β�����ʽ����a[]*/
{	int i,j,t,k;
	for(i=0;i<n-1;i++){             /* ������n-1��"ð��" */	
		for(j=0;j<n-i-1;j++)		/*����ÿһ��ð�ݵ�ѭ��*/
		   if(a[j]>a[j+1])          /*���������ڵ�Ԫ�ؽ��бȽ�*/
			   t=a[j],a[j]=a[j+1],a[j+1]=t; /*���a[j]>a[j+1]���򽻻�*/
		for(k=0;k<n;k++)            /*���ÿһ��"ð��"�����Ľ��*/
			printf("%d  ",a[k]);
		printf("\n");
	}
}