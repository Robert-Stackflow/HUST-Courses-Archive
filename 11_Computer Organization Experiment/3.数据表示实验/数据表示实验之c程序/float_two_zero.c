//file: float_two_zero.c
#include "stdio.h"

union
{
 char c[4];           //联合体，多变量共享存储空间
 float f;
 int i;
} t1,t2;

int main()
{
  t1.i=0X80000000;   //直接机器码赋值，如解释为浮点数为负零
  t2.i=0X00000000;   //直接机器码赋值，如解释为浮点数为正零
  if (t1.f==t2.f)
   printf("float data is equal\n");
  if (t1.i!=t2.i)
   printf("int data is not equal\n");
}
