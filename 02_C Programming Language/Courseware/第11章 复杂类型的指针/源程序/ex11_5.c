#include "stdio.h"
#define N 13
int day_of_year(int year,int month,int day,int (*pdaytab)[N]);
void month_day(int year,int yearday,int *p,int *pmonth,int *pday);
int main(void)
{
	  int day_tab[2][N]={
		  {0,31,28,31,30,31,30,31,31,30,31,30,31},/*平年月份天数*/
		  {0,31,29,31,30,31,30,31,31,30,31,30,31} /*闰年月份天数*/
	    };
	  int yy,mm,dd,yday;
	  printf("input the year,month, and day please!\n");
	  scanf("%d%d%d",&yy,&mm,&dd);
	  yday = day_of_year(yy,mm,dd,day_tab);/*计算该年的第几天*/
	  printf("day of the year is %d\n",yday);
	  printf("input the year and the days of the year please!\n");
	  scanf("%d%d",&yy,&yday);
	  month_day(yy,yday,day_tab[0],&mm,&dd);/*根据该年的第几天，计算月、日*/
	  printf("It's %d month and %d day in %d.\n",mm,dd,yy);
	  return 0;
}
/* day_of_year函数：根据年、月、日表示的日期转换为该年的第几天返回 */
/* 形参：year：年，month：月，day：日，pdaytab：指向一维数组的指针 */
int day_of_year(int year,int month,int day,int (*pdaytab)[N])
{	  int i,leap;	/*pdaytab为指向有N个整型元素的一维数组的指针*/
	  leap=year%4==0 && year%100 !=0 || year%400==0;
	  for(i=1;i<month;i++)
		  day+=*(*(pdaytab+leap)+i);
	  return day;
}
/* month_day函数：根据某年的第几天，将其转换为该年的某月某日 */
/* 形参：year：某年，yearday：天，p：指向数组元素的指针      */
/* pmonth：指向转换的某月，pday：指向转换的某日              */
void month_day(int year,int yearday,int *p,int *pmonth,int *pday)
{
	  int i,leap;
	  leap=year%4==0 && year%100 !=0 || year%400==0;/*leap=1,闰年*/
	  for(i=1;yearday>*(p+leap*N+i);i++)
		  yearday-=*(p+leap*N+i);/*依次减去每月天数*/
	  *pmonth=i;/*i就是月份*/
	  *pday=yearday;/*剩余天数就是该月份的第几天*/
}
