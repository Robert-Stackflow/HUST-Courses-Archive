/**
【例4.4】 学生考试成绩按以下标准分为四个等级（x为学生考试分数）：
	分数范围				英文等级名
	90≤x≤100			excellent（优）
	80≤x＜90			good（良）
	60≤x＜80			middle（中）
	x＜60				bad（差）
输入某学生的考试分数，输出该学生考试成绩的英文等级。
 */
#include <stdio.h>

int main(void)
{
    float x;

    printf("input the score x( 0 <= x <= 100):\n");
    scanf("%f", &x);
    if ( x > 100 || x < 0)
        printf("input error!\n");
    else if ( x >= 90)
        printf("excellent! \n");
    else if ( x >= 80)
        printf("good! \n");
    else if ( x >= 60)
        printf("middle! \n");
    else printf("bad! \n");

    return 0;
}