//������p�ĸ��ֽ���Ϊ����ĵ��ֽڣ���q�ĵ��ֽ���Ϊ����ĸ��ֽ� 
#include<stdio.h> 
int main(void)
{
	int p,q,s;
	scanf("%d%d",&p,&q);
	s=((p>>8)&255)|(q<<8);
	printf("%d",s);
	return 0;
}
