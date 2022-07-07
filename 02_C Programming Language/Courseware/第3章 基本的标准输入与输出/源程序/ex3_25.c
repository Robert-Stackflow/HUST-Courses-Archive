/* 例3.25 使用“*”进行虚读举例。 */

#include <stdio.h>

int main(void)
{
    int n1, n2, n3, n4, n5;

    scanf("%d %*d %d %*d %d %*d %d %*d %d", &n1, &n2, &n3, &n4, &n5);
    printf("%d %d %d %d %d", n1, n2, n3, n4, n5);

    return 0;
}