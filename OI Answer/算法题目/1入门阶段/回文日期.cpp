#include<stdio.h>
#include<stdlib.h>
int due[13]={0,31,29,31,30,31,30,31,31,30,31,30,31};
int judge(int num)
{
	int a,b,an=0;
	a=num/10000;
	b=num%10000;
	while(a)
	{
		an=an*10+a%10;
		a/=10;
	}
	if(an==b) return 1;
	else return 0;
}
int main(void)
{
    int m,n,mm,nn,check,ans=0;
    scanf("%d%d",&m,&n);
    mm=m/10000;
    nn=n/10000;
    for(int year=mm;year<=nn;year++)
    {
    	if(mm==nn)
    	{
    	for(int month=1;(month<=n%10000)/100;month++)
    	{
    	for(int day=1;day<=due[month];day++)
    	{
    		check=year*10000+month*100+day;
    		if(judge(check)) ans++;
		}
		}
		break;
		}
    	for(int month=1;month<=12;month++)
    	{
    		for(int day=1;day<=due[month];day++)
    		{
    			check=year*10000+month*100+day;
    			if(judge(check)) ans++;
			}
		}
	}
	printf("%d",ans);
}
