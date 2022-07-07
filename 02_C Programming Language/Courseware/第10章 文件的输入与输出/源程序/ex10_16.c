#include "stdio.h"
int main(void)
{	FILE *fp;
	char a[100]="xxxxxx",*p;
	int i=0;
	fp=tmpfile(); /* fp 指向创建的临时文件 */
	p=tmpnam(a); /* p指向tmpnam产生的文件名字符串 */
	while(i<=20)
		putchar(p[i++]);
	putchar('\n');
	fclose(fp);
	return 0;
}

