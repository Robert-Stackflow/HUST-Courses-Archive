/**
����4.16�� ��n!��n���ն����롣
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