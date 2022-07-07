#include<stdio.h>
int main(void)
{
	int year;
	printf("Input year: ");   /* 提示语 */
	scanf("%d",&year);   /* 输入年份，存入变量year,  scanf的用法详见3.2.2  */
	if( (!(year%4) && year%100) || !(year%400) )  /* year是闰年 */
		printf("%d is a leap year\n",year); 
	else   /* year不是闰年 */
		printf("%d is not a leap year\n",year); 
	return 0;
}
