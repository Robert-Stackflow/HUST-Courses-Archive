#include<stdio.h>
#include<string.h>
#define cr str[i]
#define be str[i-1]
#define af str[i+1]
#define sh be+j+add
#define pf re[i+differ]
//��������¿ӵ�ͷֲ�˼·��
//�ӵ㣺
//1��"-"���ܳ����ڵ�һ�������һ����ͬʱ�����������֣����ж����⴦��
//2�����x-y��xΪ���ֶ�yΪ��ĸ��Ӧѡ��չ����������Ŀ���ἰ������������ص���
//�ֲ㣺
//1���Ƿ��Ż���"-",ͬʱ���϶�"-"�����⴦��
//2��x��y�Ĺ�ϵ����<=��>��x+1=y
//3��x��yͬʱ��ĸ��������
//4����p1��p3��p2�Ĳ��ѭ������
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
