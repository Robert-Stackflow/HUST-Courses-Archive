#include<stdio.h>
int main(void)
{
	char ISBN[15];
	scanf("%s",ISBN);
	int number=0,j=1;
	for(int i=0;i<12;i++)
	{
		if(ISBN[i]=='-') continue;
		else number+=(ISBN[i]-'0')*(j++);
	}
//	����һ���ֵĴ�����Խ����Ż�
//	�����ַ�����mod[12]="0123456789X"��ʵ��
//	if(mod[t%11]==ISBN[12]) printf("Right");
//  	else{
//      ISBN[12]=mod[t%11];
//      puts(ISBN);
//  	}
	int check=number%11;
	if(check==10)
	{
	if(ISBN[12]=='X') printf("Right");
	else{
		ISBN[12]='X';
		printf("%s",ISBN);
	}	
	}
	else
	{
	if(ISBN[12]==check+'0') printf("Right");
	else{
		ISBN[12]=check+'0';
		printf("%s",ISBN);
	}
	}
}
//���͵��ַ���ģ������ 
