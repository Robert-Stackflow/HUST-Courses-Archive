#include<stdio.h>
int main(void)
{
	int year;
	printf("Input year: ");  /* 提示语 */
	scanf("%d",&year); /* 输入年份，存入变量year  */
	if(!(year%4) && year%100 || !(year%400)) /* 是闰年 */
		printf("%d is a leap year\n",year); 
	else   /* 不是闰年 */
		printf("%d is not a leap year\n",year); 
	return 0;
}
