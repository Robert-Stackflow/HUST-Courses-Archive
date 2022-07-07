//file: float_div_by_zero.c
#include "stdio.h"
main()
{
  float a=0.0, b;
  a=a/0;  b=-sqrt(-1);
  printf ("a=%f b=%f",a,b);       //输出值是什么意思？
  return;
}
