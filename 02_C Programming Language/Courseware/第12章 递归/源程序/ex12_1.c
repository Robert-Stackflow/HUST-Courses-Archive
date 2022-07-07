/************************************************************************************
简要描述：用递归法计算n！
*************************************************************************************/
#include <stdio.h>
long factorial(int n);   /*  函数原型  */

int main()
{
     int  n;
     printf ("Input a integer n (n>=0) : ");
	 scanf("%d",&n);
	 if(n<0)
		 printf ("Input error: n cann't be negative\n");
	 else
		 printf ("%d! is %ld\n",n,factorial(n));
	 return 0;
}

/****************************************************************
函数名称：factorial
函数功能：递归法求一个整数的阶乘。
函数参数：参数n为int,表示要求阶乘的数。
函数返回值：n的阶乘值，类型为long。
****************************************************************/
long factorial(int n)
{
  if (n==0||n==1)           /*  递归结束条件 */
	  return 1;
  else 
	  return (n*factorial(n-1));  /* 递归调用 */
}

