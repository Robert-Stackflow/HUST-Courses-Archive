#include<stdio.h>
int main(void)
{
	int year;
	printf("Input year: ");  /* ��ʾ�� */
	scanf("%d",&year); /* ������ݣ��������year  */
	if(!(year%4) && year%100 || !(year%400)) /* ������ */
		printf("%d is a leap year\n",year); 
	else   /* �������� */
		printf("%d is not a leap year\n",year); 
	return 0;
}
