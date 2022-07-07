#include "stdio.h"
#define N 13
int day_of_year(int year,int month,int day,int (*pdaytab)[N]);
void month_day(int year,int yearday,int *p,int *pmonth,int *pday);
int main(void)
{
	  int day_tab[2][N]={
		  {0,31,28,31,30,31,30,31,31,30,31,30,31},/*ƽ���·�����*/
		  {0,31,29,31,30,31,30,31,31,30,31,30,31} /*�����·�����*/
	    };
	  int yy,mm,dd,yday;
	  printf("input the year,month, and day please!\n");
	  scanf("%d%d%d",&yy,&mm,&dd);
	  yday = day_of_year(yy,mm,dd,day_tab);/*�������ĵڼ���*/
	  printf("day of the year is %d\n",yday);
	  printf("input the year and the days of the year please!\n");
	  scanf("%d%d",&yy,&yday);
	  month_day(yy,yday,day_tab[0],&mm,&dd);/*���ݸ���ĵڼ��죬�����¡���*/
	  printf("It's %d month and %d day in %d.\n",mm,dd,yy);
	  return 0;
}
/* day_of_year�����������ꡢ�¡��ձ�ʾ������ת��Ϊ����ĵڼ��췵�� */
/* �βΣ�year���꣬month���£�day���գ�pdaytab��ָ��һά�����ָ�� */
int day_of_year(int year,int month,int day,int (*pdaytab)[N])
{	  int i,leap;	/*pdaytabΪָ����N������Ԫ�ص�һά�����ָ��*/
	  leap=year%4==0 && year%100 !=0 || year%400==0;
	  for(i=1;i<month;i++)
		  day+=*(*(pdaytab+leap)+i);
	  return day;
}
/* month_day����������ĳ��ĵڼ��죬����ת��Ϊ�����ĳ��ĳ�� */
/* �βΣ�year��ĳ�꣬yearday���죬p��ָ������Ԫ�ص�ָ��      */
/* pmonth��ָ��ת����ĳ�£�pday��ָ��ת����ĳ��              */
void month_day(int year,int yearday,int *p,int *pmonth,int *pday)
{
	  int i,leap;
	  leap=year%4==0 && year%100 !=0 || year%400==0;/*leap=1,����*/
	  for(i=1;yearday>*(p+leap*N+i);i++)
		  yearday-=*(p+leap*N+i);/*���μ�ȥÿ������*/
	  *pmonth=i;/*i�����·�*/
	  *pday=yearday;/*ʣ���������Ǹ��·ݵĵڼ���*/
}
