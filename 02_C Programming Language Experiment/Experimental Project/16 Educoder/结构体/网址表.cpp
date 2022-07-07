#include<stdio.h>
#include<string.h>
/*
hkd 华中科技大学 http://www.hust.edu.cn
bd 百度搜索网站 http://www.baidu.com
gg 谷歌搜索网站 http://www.google.com
wy 网易邮箱登录 https://mail.163.com
*/
void sort(struct web *webs,int n);
struct web  /*  设计表示网址的结构  */
{
    /**********  Begin  **********/
	char shortname[10];
	char name[20];
	char url[50];
	/**********   End   **********/
};
#define N  4
      /*  网址表大小  */
int main()
{
	/**********  Begin  **********/
	struct web webs[N];
	char search[10];
	int flag=0;
	for(int i=0;i<N;i++)
		scanf("%s%s%s",webs[i].shortname,webs[i].name,webs[i].url);
	scanf("%s",search);
	sort(webs,N);
	printf("\n");
	for(int i=0;i<N;i++)
		printf("%s %s %s\n",webs[i].shortname,webs[i].name,webs[i].url);
	for(int i=0;i<N;i++)
		{if(strcmp(webs[i].shortname,search)==0)
			{printf("%s",webs[i].url);flag=1; } }
	if(flag==0)	printf("未找到搜寻的网址"); 
	/**********   End   **********/
	return 0; 
}
void sort(struct web *webs,int n)
{
	/**********  Begin  **********/
	int i,j;
	struct web temp;
	for(i=0;i<n-1;i++)
		for(j=i+1;j<n;j++)
			if(strcmp((webs+i)->shortname,(webs+j)->shortname)>0)
			{
				temp=*(webs+i);*(webs+i)=*(webs+j);*(webs+j)=temp;
			}
	/**********   End   **********/
}

