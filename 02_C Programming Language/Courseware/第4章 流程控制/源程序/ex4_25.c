/**
����4.25�� ����s=11+22+33+...+nn��n���ն����롣
 */

#include <stdio.h>

int main(void)
{
    int i, j, n;
    long s, term;

    printf("input n:\n");
    scanf("%d", &n);
    for (s=0,i=1; i <= n; ++i) {
        term = 1;
        j = 1;
        do
            term *= i;
        while (++j <= i);

        s += term;
    } 	/*  end of for  */
    printf("s=%ld\n", s);

    return 0;
}