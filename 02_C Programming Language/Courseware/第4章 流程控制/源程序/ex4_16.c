/**
°æ¿˝4.16°ø «Ûn!£¨n¥”÷’∂À ‰»Î°£
 */

#include <stdio.h>

int main(void)
{
    int n, i;
    unsigned long fac;

    printf("input n:\n");
    scanf("%d", &n);
    for (fac=1,i=1; i<=n; i++)
        fac *= i;
    printf("%d!=%lu\n", n, fac);

    return 0;
}