/**
����4.20�� ����һ����ʽ��ģ������������ļӡ������ˡ����������㡣�ٶ�����ʱ����������������ȼ���Ҳ����������Բ����()�����ǰ�����������ֵ��Ⱥ�˳��ִ�����㡣���磬
����10.8+0.13*100
������Ϊ1093.000000
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
        else {  /*  ����Ϊ0�������������  */
            printf("divisor is zero��input divisor again!\n");
            goto iny;
        }
        break;
    default:  /*  ������Ƿ�������������ʽ  */
        printf("illegal operator��input arithmetic expression again!\n");
        goto inx;
    }  /*  end of switch  */
    }  /*  end of while  */
    printf("%lf\n", x);

    return 0;
}