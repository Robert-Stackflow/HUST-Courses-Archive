#include<stdio.h> 
//�ж��ַ����Ƿ��Ϊ���ֵĺ��� 
int Tel(char num[])
{
	int i=0;
	for(;;i++)
	{
	if(num[i]>='0'&&num[i]<='9')
	return 1;
	else 
	return 0; 
	}
}
//�����ַ����ĳ��ȵĺ��� 
int length(char num[])
{
	int i=0;
	while(num[i]!='\0')
	++i;
	return i; 
}
int main(void)
{
	int j=0;
	char c;
	char num[1000];
	while(scanf("%s",num)!=EOF)
	{
	if (Tel(num))
	{
		if(length(num)==11)
		{
			if (num[0]!='1')
				printf("��1λ���Ϸ���\n");
			else{
				if(num[1]!='3'&&num[1]!='4'&&num[1]!='5'&&num[1]!='7'&&num[1]!='8')
					printf("��2λ���Ϸ���\n");
				else
					printf("���ֻ��źϷ���\n"); 
				} 
		}
		else
			printf("���Ȳ��Ϸ���\n");
	}
	else
		printf("�������˷������ַ���\n");
	} 
	return 0;
}
