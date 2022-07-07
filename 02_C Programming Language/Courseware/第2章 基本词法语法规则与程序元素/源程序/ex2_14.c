#include<stdio.h>
int main(void)
{
	char c;   /* 用于存放当前输入的字符 */
    int x;    /* 用于存放转换的整数 */
    for(x=0,c=getchar();c>='0'&&c<='9';c=getchar())  /* 遇非数字符结束循环 */
		x=10*x+c-'0';    /* c-'0'：将数字字符转换成对应的一位整数 */
	printf("x=%d\n",x);  /* 输出 */
	return 0;
}
