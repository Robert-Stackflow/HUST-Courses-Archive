#include<stdio.h>
int main(void)
{
	char date[5];
	int fault=0;
	scanf("%s",date);
	int day=(date[3]-'0')*10+date[4]-'0';
	if(date[0]=='1')
	{
		if(date[1]>'2')
		{fault++;if(day>=32||day==0) fault++;}
		else if(date[1]=='1') 
		{if(day>=31||day==0) fault++;}
		else if(date[1]=='2'||date[1]=='0') 
		{if(day>=32||day==0) fault++;}
	}
	else if(date[0]=='0')
	{
		if(date[1]=='2')
		{if(day>=29||day==0) fault++;}	
		else if(date[1]=='0')
		{fault++;if(day>=32||day==0) fault++;}
		else if(date[1]=='4'||date[1]=='6'||date[1]=='9')
		{if(day>=31||day==0) fault++;}
		else
		{if(day>=32||day==0) fault++;}
}
	else
	{
		fault++;
		if(date[1]=='4'||date[1]=='6'||date[1]=='9')
		{if(day>=31) fault++;}
		else
		{if(day>=32) fault++;}
	}
	printf("%d",fault);
}
