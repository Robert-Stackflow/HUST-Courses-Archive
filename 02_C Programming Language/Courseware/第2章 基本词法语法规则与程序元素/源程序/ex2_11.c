#include<stdio.h>
/*ͳ���������ĵ��ַ�����������*/
int main(void)
{
	int c,nc,nl;
	printf("Input a text end of ctrl+z:\n");  /* ��ʾ�� */
	nc=nl=0;
	while((c=getchar())!=EOF)
	{
		++nc; /* �ַ�������1��������nc++���� */
		if(c=='\n')  ++nl; /* ��������1��������nl++���� */
	}
	printf("nc=%d,nl=%d\n",nc,nl);
	return 0;
}
