/************************************************************************************
简要描述：	求两个复数的乘积。
*************************************************************************************/
#include<stdio.h>
#include<complex.h>
int main(void)
{
       double _Complex  a, b, c;
       printf("The size of a is %d\n", sizeof(a) );
       a=2+3*I;
       b=4+5*I;
       c=a*b;
       printf("c=%f+%f*I\n", creal(c), cimag(c));
       return 0;
}
