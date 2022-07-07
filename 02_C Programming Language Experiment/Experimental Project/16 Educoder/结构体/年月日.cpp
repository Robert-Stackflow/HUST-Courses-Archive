#include<stdio.h>
/**********  Begin  **********/
struct date{
	int year;
	int month;
	int day; 
};
int main()
{
	struct date start;
	scanf("%d %d %d",&start.year,&start.month,&start.day);
	int sum,leap,i;
    int mdays[12]={0,31,28,31,30,31,30,31,31,30,31,30};
    sum=0;
    for (i=1;i<start.month;i++)
    {
        sum+=mdays[i];
    }
    sum+=start.day;
    if(start.year%400==0||(start.year%4==0&&!(start.year%100==0)))
        leap=1;
    else
        leap=0;
    if(leap==1&&start.month>2)
        ++sum;
    if ((leap==0&&start.day==29)||(start.month>12))
    	printf("不存在这样的日期");
    else printf("%d",sum);
/**********   End   **********/
	return 0; 
}
