/**
【例4.17】 把输入的整数按反方向输出。例如，输入的数是12345，要求输出结果是54321。
 */

#include <stdio.h>

int main(void)
{
    int x;

    printf("input an integer:\n");
    scanf("%d", &x);
    do
        putchar(x % 10 + '0');
    while ((x/=10) != 0);
    printf("\n");

    return 0;
}