#include<stdio.h>
#include<string.h>
char scan[10001],sort[10001],res[10001];
int check[26]={0},n,pos,count;
void fun(void);
int main(void)
{
	int i=0,j=0;
	scanf("%d",&n);
	count=n;
	scanf("%s%d",scan,&pos);
	fun();
//	printf("%s\n",sort);
	for(int i=0;i<n;i++)
		if(sort[i]==scan[pos-1])
		{
			pos=i;
			break;
		}
	//�ҵ������ַ���������ĸ��Ӧ���ֵ��ַ����е���ĸ 
	while(count>=0)
	{
		res[count--]=scan[pos]; 
		sort[pos]='*';//���������ַ�����ֹ�ظ����� 
		for(int i=n-1;i>=0;i--)
		if(sort[i]==scan[pos]){pos=i;break;}
	}
	printf("%s",res+1);
	return  0; 
}
void fun()//��������ַ��������ֵ�˳�������������sort�� 
{
	int count=0;
	for(int i=0;i<n;i++)
		++check[scan[i]-'a'];
	for(int i=0;i<26;i++)
		for(int j=0;j<check[i];j++)
		sort[count++]=i+'a';
}
