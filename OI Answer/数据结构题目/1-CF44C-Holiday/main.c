/*********************************************************************
    程序名:Holidays
    作者:徐瑞达
    日期: 2021-07-09 11:52
    说明:扫数组，计算浇花次数
*********************************************************************/
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    int n, m;
    scanf("%d%d", &n, &m);
    int flag[105]={0};
    int day[105][2]={0};
    for (int i = 0; i < m; i++)
    {
        scanf("%d%d", &day[i][0], &day[i][1]);
        for (int p = day[i][0]; p <= day[i][1]; p++)
            flag[p]++;
    }
    for (int i = 1; i <= n; i++)
        if (flag[i] != 1)
        {
            printf("%d %d", i, flag[i]);
            return 0;
        }
    printf("OK");
    return 0;
}