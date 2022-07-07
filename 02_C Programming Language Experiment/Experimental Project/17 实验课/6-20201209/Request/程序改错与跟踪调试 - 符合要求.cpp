#include<stdio.h>
#include<string.h>
void strcate (char [ ],char[ ]);
void strdelc (char [],char);
int main (void)
{
	char a[100],b[100];
	char d,c;
	scanf("%s%s",a,b);
	scanf("%c%c",&d,&c);
	strcate(a,b); printf("%s\n",a);
	strdelc(a,c); printf("%s",a);
	return 0;
}

void strcate(char t[],char s[])
{
	int i=0,j=0,k=-1;
	while(t[i++]);
	i--;
	while((t[i++]=s[j++])!='\0'); 
}
	
void strdelc(char s[],char c)
{
	int j,k;
	for(j=k=0;s[j]!='\0';j++)
 	if(s[j]!=c) s[k++]=s[j];
 	s[k]='\0';
}

	

