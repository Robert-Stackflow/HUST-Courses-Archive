#include<stdio.h>
#include<stdlib.h>
#define N 20
char *strcopy(char *,const char *);
int main(void)
{
	char *s1=((char *)malloc(N+1)),*s2=((char *)malloc(N+1)),*s3=((char *)malloc(N+1));
	printf("Input a string:\n",s2);
	scanf("%s",s2);
	strcopy(s1,s2);
	printf("%s\n",s1);
	printf("Input a string again:\n");
	scanf("%s",s2);
	s3=strcopy(s1,s2);
	printf("%s\n",s3);
	return 0;
}
char *strcopy(char *t,const char *s)
{
	char *r=t;
	while(*r++=*s++);
	return(t);
}



