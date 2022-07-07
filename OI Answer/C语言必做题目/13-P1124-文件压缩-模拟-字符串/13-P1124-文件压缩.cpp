#include<stdio.h>
#include<string.h>
char scan[10001],sort[10001],res[10001];
int check[26]={0},n,pos;
void fun(void);
int main(void)
{
	int i=0,j=0;
	scanf("%d",&n);
	scanf("%s%d",scan,&pos);
	fun();
//	printf("%s\n",sort);
	res[i++]=scan[pos-1];
	res[i++]=sort[pos-1];
	for(j=0;j<n;j++)
		if(sort[pos-1]==scan[j])break;
	res[i++]=sort[j];
	for(int k=0;k<n;k++)
	{
	for(j=0;j<n;j++)
		if(res[i-1]==scan[j])break;
	res[i++]=sort[j];
	}
	for(int i=0;i<n;i++) putchar(res[i]);
}
void fun()
{
	int count=0;
	for(int i=0;i<n;i++)
		++check[scan[i]-'a'];
	for(int i=0;i<26;i++)
		for(int j=0;j<check[i];j++)
		sort[count++]=i+'a';
}
