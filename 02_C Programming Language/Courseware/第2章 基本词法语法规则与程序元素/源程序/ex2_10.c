#include<stdio.h>
int main(void)
{
	int year;
	printf("Input year: ");   /* ��ʾ�� */
	scanf("%d",&year);   /* ������ݣ��������year,  scanf���÷����3.2.2  */
	if( (!(year%4) && year%100) || !(year%400) )  /* year������ */
		printf("%d is a leap year\n",year); 
	else   /* year�������� */
		printf("%d is not a leap year\n",year); 
	return 0;
}
