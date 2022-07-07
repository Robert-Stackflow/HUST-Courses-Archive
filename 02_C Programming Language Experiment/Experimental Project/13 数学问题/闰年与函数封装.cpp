#include<stdio.h> 
int isleap(int year){
    if((!(year%4)&&(year%100))||!(year%400))
		return 1;
	else
		return 0;
}
int main(void)
{
	int year;
	printf("ÇëÊäÈëÄê·İ:");
	scanf("%d",&year);
	if (isleap(year))
		printf("The year %d is a leap year",year);
	else
		printf("The year %d isn't a leap year",year);
	return 0;
}
