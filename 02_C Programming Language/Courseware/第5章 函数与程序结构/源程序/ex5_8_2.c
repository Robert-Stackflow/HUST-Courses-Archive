/************************************************************************************
 简要描述：伪随机数发生器的实现与使用,将程序放在两个文件中。
           这是第2个文件ex5_8_2.c: 使用伪随机数发生器,
		   只包含main函数.
*************************************************************************************/
#include<stdio.h>
void  srandom(void);             /* 函数原型 */
unsigned  random(void);          /* 函数原型 */
double  probability(void);       /* 函数原型 */
int  main(void)                 /* seed在main不可用 */
{
	  int  i;
	  srandom( );
	  for (i= 0;i<6;i++)  
	  {
		  printf ("%u\t",random());
	      printf ("%f\n",probability());
	  }
	  return  0;
}
