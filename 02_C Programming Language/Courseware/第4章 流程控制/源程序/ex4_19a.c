/**
³ÌÐò4.19a£º
 */

#include<stdio.h>

int main(void)
{
    int n, i, r;

    do {
        printf("input an integer(>=2)£º\n");
        scanf("%d", &n);
    } while(n < 2);

    for (i=2,r=1; r && i*i<=n; i++)
        r = n % i;
    if (r)
        printf("%d is a prime.\n", n);
    else
        printf("%d is not a prime.\n", n);

    return 0;
}