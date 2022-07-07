/*********************************************************************
    程序名:分数的计算
    作者:徐瑞达
    日期: 2021-07-09 11:52
    说明:利用差分数组实现算法优化
*********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define min(x, y) ((x) < (y) ? (x) : (y))
int main(void)
{
    int n, p, res = 205;
    scanf("%d%d", &n, &p);
    int *score = (int *)malloc(sizeof(int) * (n + 1));
    int *minus = (int *)malloc(sizeof(int) * (n + 1));
    score[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &score[i]);
        minus[i] = score[i] - score[i - 1];
    }

    for (int i = 1; i <= p; i++)
    {
        int left, right, addition;
        scanf("%d%d%d", &left, &right, &addition);
        minus[left] += addition;
        minus[right+1] -= addition;
    }
    for (int i = 1; i <= n;i++)
    {
        score[i] = score[i - 1] + minus[i];
        res = min(res, score[i]);
    }
    printf("%d", res);
    return 0;
}