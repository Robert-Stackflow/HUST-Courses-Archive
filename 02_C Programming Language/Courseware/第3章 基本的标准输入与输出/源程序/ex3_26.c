/* ��3.26���ת��˵���ڸ�ʽ�����е����þ����� */

#include <stdio.h>

int main(void)
{
    short x1;
    char x2;

    printf("input a integer and a character:\n");
    scanf("%hd", &x1);
    scanf("%*c %c", &x2);
    printf("x1=%d, x2=%c\n", x1, x2);

    return 0;
}