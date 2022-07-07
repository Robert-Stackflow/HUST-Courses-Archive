#include<stdio.h> 
//声明函数 
void codel(char t[],char mid[],int n);
void strcate(char t[],char s[]);
void strnins(char t[],char s[],int n);

int main(void)
{
	char t[100],s[100];
	int n;
	scanf("%s%s%d",t,s,&n);
	strnins(t,s,n);
	printf("%s",t);
}

void codel(char t[],char mid[],int n)
{//将数组t自第n个字符后的字符复制到中间数组中，并将数组t的后半部分删除
	int i=0,k=n;
	for(;t[k]!='\0';i++,k++)
		mid[i]=t[k];
	mid[i]='\0';
	t[n]='\0';
}

void strcate(char t[],char s[])
{//将一个字符串拼接到另一个字符串后
	int i=0,j=0,k=-1;
	while(t[i++]);
	i--;
	while((t[i++]=s[j++])!='\0'); 
}

void strnins(char t[],char s[],int n)
{//调用以上两个函数，实现插入字符串功能，
	char mid[100];
	codel(t,mid,n);
	strcate(t,s);
	strcate(t,mid);
}
