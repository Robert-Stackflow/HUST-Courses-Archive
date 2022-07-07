#include<stdio.h>
/*统计输入正文的字符数和行数。*/
int main(void)
{
	int c,nc,nl;
	printf("Input a text end of ctrl+z:\n");  /* 提示语 */
	nc=nl=0;
	while((c=getchar())!=EOF)
	{
		++nc; /* 字符数自增1，可以用nc++代替 */
		if(c=='\n')  ++nl; /* 行数自增1，可以用nl++代替 */
	}
	printf("nc=%d,nl=%d\n",nc,nl);
	return 0;
}
