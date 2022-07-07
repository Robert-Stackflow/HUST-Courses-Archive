/**
【例4.5】 用switch语句重新实现例4.4。
 */

#include <stdio.h>

int main(void)
{
    float x;

    printf("input the score x( 0 <= x <= 100):\n");
    scanf("%f", &x);
    if ( x > 100 || x < 0)
        printf("input error!\n");
    else 
        switch ((int)(x / 10))
        {
        case 10: printf(" excellent! \n"); break;
        case 9:	 printf(" excellent! \n"); break;
        case 8:  printf(" good! \n"); break;
        case 7:  printf(" middle! \n"); break;
        case 6:  printf(" middle! \n"); break;
        case 5:  printf(" bad! \n"); break;
        case 4:  printf(" bad! \n"); break;
        case 3:  printf(" bad! \n"); break;
        case 2:  printf(" bad! \n"); break;
        case 1:  printf(" bad! \n"); break;
        case 0:  printf(" bad! \n"); break;
        }

    return 0;
}
/*
	程序中表达式(int)(x / 10)里(int)是类型强制运算符，可将表达式x / 10的类型强制转换为int（截去小数部分，而不是四舍五入）。另外，程序中的switch语句可以简化为：
	switch ((int)(x / 10))
	{
	case 10:
	case 9:	 printf(" excellent! \n"); break;
	case 8:  printf(" good! \n"); break;
	case 7: 
	case 6:  printf(" middle! \n"); break;
	case 5:
	case 4:
	case 3:
	case 2:
	case 1:
	case 0:  printf(" bad! \n"); break;
	}
 */