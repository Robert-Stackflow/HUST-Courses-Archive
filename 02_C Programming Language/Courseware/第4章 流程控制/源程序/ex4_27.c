/**
【例4.27】 下列乘法算式中，每个汉字代表1个0~9的数字，不同的汉字代表不同的数字。
    赛软件 * 比赛  =  软件比拼
试编程确定使得整个算式成立的数字组合，如有多种情况，请给出所有可能的答案。
 */

#include <stdio.h>

int main()
{
    int a, b, c, d, e;

    for (a=0; a<10; a++)        /* 第一层循环执行10次 */
        for (b=0; b<10; b++) {
            if (b-a==0)
                continue;      /* 第二层循环执行9次，里层循环执行次数依次递减 */
            for (c=0; c<10; c++) {
                if ((c-b)*(c-a) == 0)
                    continue;  /* (c-b)*(c-a) == 0等价于(c-b)==0 || (c-a)==0，下同 */
                for (d=0; d<10; d++) {
                    if ((d-c)*(d-b)*(d-a) == 0)
                        continue;
                    for (e=0; e<10; e++) {
                        if ((e-d)*(e-c)*(e-b)*(e-a) == 0)
                            continue;
                        if ((a*100+b*10+c) * (d*10+a) == b*1000+c*100+d*10+e)
                            printf("%d%d%d * %d%d = %d%d%d%d\n", a, b, c, d, a, b, c, d,e);
                    }
                }
            }
        }

    return 0;
}