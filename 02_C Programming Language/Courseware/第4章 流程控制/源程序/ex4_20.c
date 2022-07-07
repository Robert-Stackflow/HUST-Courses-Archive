/**
【例4.20】 输入一个算式，模拟袖珍计算器的加、减、乘、除四则运算。假定计算时不考虑运算符的优先级，也不允许输入圆括号()，而是按照运算符出现的先后顺序执行运算。例如，
输入10.8+0.13*100
计算结果为1093.000000
 */

#include <stdio.h>

int main(void)
{
    double x, y;
    char op;

inx:
    printf("input arithmetic expression:\n");
    scanf("%lf", &x);
    while((op = getchar()) != '\n'){
iny:
    scanf("%lf", &y);
    switch(op){
    case '+':
        x += y;
        break;
    case '-':
        x -= y;
        break;
    case '*':
        x *= y;
        break;
    case '/':
        if (y)
            x /= y;
        else {  /*  除数为0，重新输入除数  */
            printf("divisor is zero，input divisor again!\n");
            goto iny;
        }
        break;
    default:  /*  运算符非法，重新输入算式  */
        printf("illegal operator，input arithmetic expression again!\n");
        goto inx;
    }  /*  end of switch  */
    }  /*  end of while  */
    printf("%lf\n", x);

    return 0;
}