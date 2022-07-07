#include<stdio.h>
#include<string.h>
#define cr str[i]
#define be str[i-1]
#define af str[i+1]
#define sh be+j+add
#define pf re[i+differ]
//下面分析下坑点和分层思路：
//坑点：
//1、"-"可能出现在第一个或最后一个，同时可能连续出现，用判断特殊处理
//2、如果x-y中x为数字而y为字母，应选择不展开！（与题目中提及的特殊情况不重叠）
//分层：
//1、是符号还是"-",同时加上对"-"的特殊处理
//2、x与y的关系，分<=、>、x+1=y
//3、x与y同时字母还是数字
//4、以p1、p3、p2的层次循环即可
int main(void)
{
	int p1,p2,p3,differ=0;
	char str[100],re[6500];
	scanf("%d%d%d%s",&p1,&p2,&p3,str);
	for(int i=0;i<strlen(str)+1;i++)
	{
		if(cr=='\0') {pf='\0';break;}
		if(cr=='-'&&af>be&&(be>='0'&&af<='9'||be>='a'&&af<='z'))
		{
			int flag=0,add=0;
			if(be<='z'&&be>='a') flag=1;
			if(p1!=3)
			{
			if(p1==1) add=0;
			else  {if(flag==0)add=0;else add=-32;}
			if(p3==1)
			{
			for(int j=1;(j+be)<af;j++)
			{
			for(int k=0;k<p2;k++)
			{pf=sh;differ++;} 
			}
			}
			else
			{
			for(int j=af-be-1;j>0;j--)
			{
			for(int k=0;k<p2;k++)
			{pf=sh;differ++;} 
			}
			}
			differ--;
			}
			else{
			for(int j=1;(j+be)<af;j++)
			{
			for(int k=0;k<p2;k++)
			{pf='*';differ++;} 
			}
			differ--;
			}
			}	
		else	pf=cr;
	}
	printf("%s",re);
}
