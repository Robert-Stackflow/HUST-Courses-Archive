#include "stdio.h"
#include "ctype.h"
#define NUMBER 100
int getint(int *pn); /* 声明函数原型*/
int getint(int *pn) /*定义getint函数*/
{
	  int c,sign;
	  while(isspace(c=getchar()))       /* 跳过前导空格 */ 
		;
	  if(!isdigit(c) && c!=EOF && c!= '+' && c!= '-') {
		/* 若输入为非数字、非EOF、也不是+、-号，显示出错并且返回 */
		printf("input error!\n");
		return 0;
	  }
	  sign = (c=='-') ?-1:1;          /* 处理符号 */
	  if(c=='+' || c=='-')
		  c=getchar();                  /* 跳过+、-号 */
	  for(*pn=0;isdigit(c);c=getchar())
		  *pn=10 * *pn+(c-'0');       /* 将数字串转换为对应整数 */
	  *pn *= sign;                      /* 处理整数的符号 */
	  return c; /* 返回的c值一定不是数字字符 */
}
int main(void)
{
	  int a[NUMBER],i,j,k;
	  printf("input integers ends with Enter\n");
	  for(i=0;i< NUMBER && (k=getint(&a[i]))!= '\n';) /*getint返回值赋给k,*/
		  if(k) i++; /* 并且只要数组没越界且k值不是换行符，继续循环 */
	  for(j=0;j<=i;j++)
		  printf("%8d",a[j]); /* 输出转换后的数 */
	  printf("\n");
	  return 0;
}
