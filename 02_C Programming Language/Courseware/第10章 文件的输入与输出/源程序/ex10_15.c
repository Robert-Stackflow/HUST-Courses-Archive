#include "stdio.h"
int main(void)
{	FILE *fp;
	char a[100]="xxxxxx",*buf=a; /* 数组a为程序设定缓冲区，由buf指向 */
	int i='a';
	fp = fopen("c:\\abc.dat","w+");
	setvbuf(fp,buf,_IOFBF,60); /* 也可用：setbuf(fp,buf); */
	while(i<='z')
		fputc(i++,fp); /* 将abc…xyz写入fp所指文件的缓冲区 */
	i=0;
	while(i<=26)
		putchar(a[i++]); /* 从数组a，即缓冲区中读 */
	putchar('\n');
	fflush(fp); /* 缓冲区数据强制存盘 */
	fclose(fp);
  return 0;
}
