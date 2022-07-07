//file: float_precision.c
#include "stdio.h"
test_float_cal()
{
  float a,b,c;   int d;
  b=3.3;   c=1.1;
  a=b/c;
  d=b/c;
  printf("a=%f,d=%d",a,d);
  if (3.0==a)
    printf("\nFloat a=3.3/1.1==3.0");
}

test_double_cal()
{
  double a,b,c;   int d;
  b=3.3;   c=1.1;
  a=b/c;
  d=b/c;
  printf("\n\na=%f,d=%d",a,d);
  if (3.0!=a)
   printf("\nDouble a=3.3/1.1 != 3.0");
}

main()
{
  test_float_cal();
  test_double_cal();
}
