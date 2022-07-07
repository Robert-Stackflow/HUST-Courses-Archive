# include<stdio.h>
# include<string.h>
#include<stdlib.h>
//#define N 4
/*输入样例：
abfg
chgi
cajp
bklg
*/
void strsort(char*s[],int size)
{//此时s[]是指针数组，而后定义的temp也是指针，故可以赋值 
	char *temp;
	int i,j;
	//冒泡法排序 
	for(i=0;i<size-1;i++)
	{
		for(j=0;j<size-i-1;j++)
		{
			if(strcmp(s[j],s[j+1])>0)
			{
				//交换地址来交换对应的字符串 
				temp=s[j];
				s[j]=s[j+1];
				s[j+1]=temp;
			}
		}
	}
}
int main(void)
{
	int i,N;
	char c;
	scanf("%d",&N);
	c=getchar();
	char *s[N],t[50];
	//定义指针数组s 
	for(i=0;i<N;i++)
	{
		gets(t);//输入字符串t 
//		printf("第%d个字符串的长度为:%d\n",i+1,strlen(t));
		s[i]=(char *)malloc(strlen(t)+1);
		//s存储的是指针（输入的字符串地址） 
		//mannoc申请动态内存
		//（char *）把指针强制转换为char类型指针。 
		strcpy(s[i],t);
		//s存储的是指针，*s代表其存储的内容（地址）
		//&s[i]代表其地址，s[i]指向一个地址 
		//s[i]存储存储的地址，*s[i]代表其存储的地址对应的内容 
	}
	strsort(s,N);
	printf("\n");
	for(i=0;i<N;i++)	puts(s[i]);
	//puts函数原型为（const *s)  
	return 0;
 } 
