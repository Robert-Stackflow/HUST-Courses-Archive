#include<stdio.h> 
int main(void)
{
	char s[1000];
	printf("������һ���ַ���\n");
	scanf("%s",s);
	int i=0,num=0;
	while(((s[i]>='0'&&s[i]<='9') ||(s[i]>='a'&&s[i]<='f')||(s[i]>='A'&&s[i]<='F'))&&(s[i]!='\0')){
		++num;
		++i;
		} 
	printf("���ַ����е�ʮ�������ַ���Ϊ%d",num);
	return 0;
}
