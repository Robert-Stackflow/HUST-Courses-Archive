#include<stdio.h> 
int length(char num[])
{
	int i=0;
	while(num[i]!='\0')
	++i;
	return i; 
}
int main(void)
{
	
	char s[100];
	char c;
	gets(s);
	int k;
	scanf("%d",&k); 
	int i=0,j=0;
	for(;i<=length(s);++i)
	{
		if(s[i]>='A'&&s[i]<='Z'){
			if(s[i]>='A'&&s[i]<='R')
				s[i]=s[i]+k-1;
			else
				s[i]=s[i]-27+k;
		}
	} 
	while(s[j]!='\0')
	{
		c=s[j];
		s[j]=s[j+1];
		s[j+1]=c;
		j+=2;
	} 
	printf("%s",s);
}
