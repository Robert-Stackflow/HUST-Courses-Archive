/**
【例4.15】 输入一批整数，以0为结束。输出其中最大的一个值。
 */

#include <stdio.h>

int main(void)
{
    int x, max;

    printf("input a group integer end of 0：\n");
    scanf("%d", &x);
    max = x;
    for( ; x != 0; ) {
        scanf("%d", &x);
        if (max < x)
            max = x;
    }
    printf("max=%d\n", max);

    return 0;
}