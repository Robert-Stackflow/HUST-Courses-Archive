#include "stdio.h"
void delete_c(char s[],char c);
int main(void)
{
	char s[]="yvovuv vavrvev svtvuvdvevnvtvsv.";
	delete_c(s,'v');
	printf("%s\n",s);
	return 0;
}
void delete_c(char s[],char c)
{	int j=0,k=0;
	while(s[j]!= '\0'){/*��s���е�ÿ���ַ�*/
		if(s[j]!=c) /*�������Ҫɾ���ַ�*/
			s[k++]=s[j];/*���Ʒ�ɾ�ַ�*/
		j++;/*�ܹ�����Ҫɾ���ַ�*/
	}
	s[k]= '\0';/*�����´�*/
}
