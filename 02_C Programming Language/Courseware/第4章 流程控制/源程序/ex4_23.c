/**
【例4.23】 输入10个整数，输出其中正数的个数及平均值。
 */

#include <stdio.h>

int main(void)
{
    int a, i, k, x;

    printf("input 10 numbers:\n");
    for (a=i=k=0; i<10; ++i) {
        scanf("%d", &x);
        if (x <= 0)
            continue;  /* 对负数不作处理 */
        a += x;        /* 计算正数的和，存入a */
        ++k;          /* 正数的个数 */
    }
    if (k)
        printf("numbers=%d，average=%f\n", k, 1.0 * a / k);

    return 0;
}