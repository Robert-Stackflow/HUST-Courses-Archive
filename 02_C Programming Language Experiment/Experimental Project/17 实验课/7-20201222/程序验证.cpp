#include<stdio.h>
#include<stdlib.h>
char u[]="UVWXYZ",v[]="xyz";
struct T
{
	int x;
	char c;
	char *t;
}a[]={{11,'A',u},{100,'B',v}},*p=a;
int main(void)
{
	int flag=0;
	scanf("%d",&flag);
	if(flag==1) 
	printf("%d",(++p)->x);
	else if(flag==2)
	printf("%c",(p++,p->c));
	else if(flag==3) 
	printf("%c",(*p++->t,*p->t));
	else if(flag==4)
	printf("%c",*(++p)->t);
	else if(flag==5)
	printf("%c",*++p->t);
	else if(flag==6)
	printf("%c",++(*p->t));
	return 0;
}



