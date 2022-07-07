/* 例3.4 getchar函数执行流程分析。 */

#include <stdio.h>

int main(void)
{
    char ch1, ch2, ch3;

    ch1 = getchar(); 
    ch2 = getchar(); 
    ch3 = getchar();
    printf("\n%c%c%c", ch1, ch2, ch3);
    printf("\n%d  %d  %d", ch1, ch2, ch3);

    return 0;
}