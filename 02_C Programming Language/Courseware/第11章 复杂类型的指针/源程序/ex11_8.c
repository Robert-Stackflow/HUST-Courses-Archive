#include "stdio.h"
int (*(*(*f[2])())[2])(int,int);
int (*(*(f1()))[2])(int,int);
int (*(*(f2()))[2])(int,int);
int (*pf[2][2])(int,int);
int add(int,int);
int sub(int,int);
int mul(int,int);
int div(int,int);
int main(void)
{
	  f[0]=f1; /* 对函数指针f[0]赋值 */
	  f[1]=f2; /* 对函数指针f[1]赋值 */
	  (*((*f[0]())[0]))(20,10); /* 等价于add（20,10） */
	  (*((*f[0]())[1]))(20,10); /* 等价于sub（20,10） */
	  (*((*f[1]())[0]))(20,10); /* 等价于mul（20,10） */
	  (*((*f[1]())[1]))(20,10); /* 等价于div（20,10） */
	  return 0;
}
int (*(*(f1()))[2])(int,int)
{
	  pf[0][0]=add; /* 对函数指针pf[0][0]赋值 */
	  pf[0][1]=sub; /* 对函数指针pf[0][1]赋值 */
	  printf("function f1 is called!\n");
	  return pf;
}
int (*(*(f2()))[2])(int,int)
{
	  pf[1][0]=mul; /* 对函数指针pf[1][0]赋值 */
	  pf[1][1]=div; /* 对函数指针pf[1][1]赋值 */
	  printf("function f2 is called!\n");
	  return pf+1;
}
int add(int x,int y)
{
	  printf("%d+%d=%d\n",x,y,x+y);
	  return (x+y);
}
int sub(int x,int y)
{
	  printf("%d-%d=%d\n",x,y,x-y);
	  return (x-y);
}
int mul(int x,int y)
{
	  printf("%d*%d=%d\n",x,y,x*y);
	  return (x*y);
}
int div(int x,int y)
{
	  if(y!=0){
		  printf("%d/%d=%d\n",x,y,x/y);
		  return (x/y);
	  }
	  else{
		  printf("divide by zero! return zero!\n");
		  return (0);
	  }
}
