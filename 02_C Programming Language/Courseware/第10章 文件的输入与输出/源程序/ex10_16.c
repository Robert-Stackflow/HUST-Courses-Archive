#include "stdio.h"
int main(void)
{	FILE *fp;
	char a[100]="xxxxxx",*p;
	int i=0;
	fp=tmpfile(); /* fp ָ�򴴽�����ʱ�ļ� */
	p=tmpnam(a); /* pָ��tmpnam�������ļ����ַ��� */
	while(i<=20)
		putchar(p[i++]);
	putchar('\n');
	fclose(fp);
	return 0;
}

