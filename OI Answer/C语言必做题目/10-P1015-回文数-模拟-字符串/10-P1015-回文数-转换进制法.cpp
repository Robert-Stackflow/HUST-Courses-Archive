#include<stdio.h>
#include<math.h>
//˵�����÷���������ϵ�AC�ʺܵͣ�������25%���Ǵ�����©����
//��������ڵĸ���©��������Ҫ�жϵ�������ַ������֮����Ƿ�Ϊ���Ĵ�
//��������ת��Ϊʮ�����������ʮ�������ǲ��ǻ�����
//Ҫ���������ı��ʣ����Ҫ�õ�������Ƶĸ߾��ȼӷ����� 
//������ڲ�����16 adfd����ȷ��ΪSTEP=2��
//������ڲ�����16 AC27����ȷ��ΪSTEP=6��
//���÷������������������Ի�����������Ϊ3 
int change(int n);
int transform(int base,char*str);
int judge(int n);
int main(void)
{
	int n,m,flag=0;
	char str[100];
	scanf("%d%s",&n,str);
	m=transform(n,str);//���ַ���ת��Ϊ��Ӧ��ʮ��������
	printf("%d",m); 
	for(int i=0;i<30;i++)
	{
		if(judge(m)) {printf("STEP=%d",i);return 0;}
		m+=change(m);
	}
	printf("Impossible!");
}

int change(int n)
{
	int n1=0;
	for(int i=0;;i++)
	{
		n1=n1*10+n%10;
		n/=10;
		if(n==0) break;
	} 
	return n1;
}//��һ�����ַ�ת 
int judge(int n)
{
	int flag=0;
	if(change(n)==n) flag=1;
	return flag;			
}//�ж��Ƿ�Ϊ������ 
int transform(int base,char*str)
{
	int j=0,num=0;
	for(;str[j]!='\0';j++)
	{
		if(str[j]>='0'&&str[j]<='9') num=num*base+str[j]-'0';
		if(str[j]>='a'&&str[j]<='f') num=num*base+str[j]-'a'+10;
		if(str[j]>='A'&&str[j]<='F') num=num*base+str[j]-'A'+10;
	}
	return num;
}
