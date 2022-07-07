/* 可变参数的用法 */
#include <stdio.h>
#include <stdarg.h>

double  average(int, ...);                /* 函数原型 */

int  main(void)
{
    double  a = 1.5, b = 2.6, c = 3.7, d = 4.8;
    printf ("a=%.1f,b=%.1f,c=%.1f,d=%.1f\n", a, b, c, d);
    printf ("The average of a and b is %.2f \n", average(2, a, b));
    printf ("The average of a、b and c is %.2f \n", average(3, a, b, c));
    printf ("The average of a,b,c and d is %.2f \n", average(4, a, b, c, d));
    return 0;
}

double average(int i, ...)
{
    double sum = 0.0;
    int k;
    va_list ap;

    va_start(ap, i);
    for (k=1; k<=i; k++)
        sum += va_arg(ap, double);
    va_end(ap);
    return (sum/i);
}
