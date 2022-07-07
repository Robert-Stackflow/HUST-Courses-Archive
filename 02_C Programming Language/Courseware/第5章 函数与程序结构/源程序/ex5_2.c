/************************************************************************************
简要描述：输入一个整数，判断整数它是否素数
*************************************************************************************/
#include <stdio.h>
/****************************************************************
函数名称：IsPrime
函数功能：判断整数是否素数
函数参数：第1个参数n为int，表示待判断的整数
函数返回值：如果n是素数，则返回1；如果n不是素数，则返回0。
****************************************************************/
int  IsPrime(int n)
{
	  int  k,limit;

	  if (n==2)
	       return 1;
	  if (!(n % 2))
	       return 0;
	  limit=n/2 ;
	  for (k=3;k<=limit;k+=2)
	      if (!(n % k))
	           return 0;
      return 1;
}
int main()
{
    int x;
    printf("input a integer:");
    scanf("%d",&x);
    if(IsPrime(x))
         printf("%d is a prime.\n",x);
    else
         printf("%d is not a prime.\n",x);
    return 0;
}
