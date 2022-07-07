/* 【例4.3】 输入两个整数，按从小到大的顺序输出这两个数。 */

#include <stdio.h>

int main(void)
{
    int a, b;

    printf("input a, b:\n");
    scanf("%d%d", &a, &b);
    {
        int t;

        if (a > b) {
            t = a; a = b; b = t;
        }
    }
    printf("a=%d, b=%d\n", a, b);

    return 0;
}