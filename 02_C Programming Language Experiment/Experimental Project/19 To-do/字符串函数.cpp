#include<stdio.h> 
#include<string.h>
//将某字符串自第n个字符后的字符拷贝至中间字符串中，并将原字符串的自n之后的字符删除 
void codel(char t[],char mid[],int n)
{
	int i=0,k=n;
	for(;t[k]!='\0';i++,k++)
		mid[i]=t[k];
	mid[i]='\0';
	t[n]='\0';
}
//将字符串s拼接到字符串t后 
void strcate(char t[],char s[])
{
	int i=0,j=0,k=-1;
	while(t[i++]);
	i--;
	while((t[i++]=s[j++])!='\0'); 
}
//将字符串s插入到t的前n个字符后 
void strnins(char t[],char s[],int n)
{
	char mid[100];
	codel(t,mid,n);
	strcate(t,s);
	strcate(t,mid);
}
int strlen(char s[]) 
{
	int i=0;
	while(s[i++]!='\0');
	return i;
}
//查找某字符串中是否有欲找字符，并返回出现次数 
int strfound(char s[],char c)
{
	int count=0;
	for(int i=0;i<strlen(s);i++)
	{
		if(c==s[i])
			count++;
	}
	if(count==0)
	printf("该字符串中无该字符！"); 
	else
	return count; 
} 
