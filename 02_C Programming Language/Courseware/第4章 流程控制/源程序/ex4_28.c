/**
【例4.28】 用筛法构造2~100之间的素数表，并输出该素数中的素数。
 */

#include <stdio.h>

int main()
{
    int i, j, a[100];

    for (a[0]=a[1]=0,i=2; i<100; i++)  /* 数组初始化，先假定2~99都是素数 */
        a[i] = 1;     /* 数组下标值是被测数，用1标记素数 */
    for (i=2; i<50; i++)  /* 从2开始，“筛掉”每个素数的倍数 */
        if (a[i]) {    /* 如果a[i]值为1，则i为素数 */
            for (j=i*i; j<100; j+=i)  /* 从i倍的i开始“筛”,因为之前的倍数已被“筛掉” */
                a[j] = 0;   /* 元素值为0表示该元素下标值不是素数 */
        }
    for (i=2,j=0; i<100; i++)  /* 输出2~100间的素数表 */
        if (a[i]) {  /* “筛”过之后，值为1的元素对应下标为素数 */
            printf("%4d", i);
            if (++j == 8) {  /* 为了输出整齐，每行输出8个素数 */
                j = 0;
                printf("\n");
            }
        }

    return 0;
}