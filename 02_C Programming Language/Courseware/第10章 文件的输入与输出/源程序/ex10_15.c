#include "stdio.h"
int main(void)
{	FILE *fp;
	char a[100]="xxxxxx",*buf=a; /* ����aΪ�����趨����������bufָ�� */
	int i='a';
	fp = fopen("c:\\abc.dat","w+");
	setvbuf(fp,buf,_IOFBF,60); /* Ҳ���ã�setbuf(fp,buf); */
	while(i<='z')
		fputc(i++,fp); /* ��abc��xyzд��fp��ָ�ļ��Ļ����� */
	i=0;
	while(i<=26)
		putchar(a[i++]); /* ������a�����������ж� */
	putchar('\n');
	fflush(fp); /* ����������ǿ�ƴ��� */
	fclose(fp);
  return 0;
}
