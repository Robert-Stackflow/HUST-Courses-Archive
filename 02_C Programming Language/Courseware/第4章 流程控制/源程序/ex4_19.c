/**
【例4.19】 输入任意一个大于或等于2的整数n，判断该数是否为素数并输出相应结果。
 */

#include <stdio.h>
#include <math.h>

int main(void)
{
    int n, i, k, r;

    do {
        printf("input n:\n");
        scanf("%d", &n);
    } while (n < 2);
    if (n == 2)
        printf("2 is a prime\n");
    else if (n > 2) {
        i = 1;
        k = sqrt(n);
        do {
            ++i;
            r = n % i;
        } while (r && i <= k);
        if(r)
            printf("%d is a prime\n", n);
        else
            printf("%d isn’t a prime\n", n);
    } 	/*  end of else-if  */

    return 0;
}