/**
����4.17�� ���������������������������磬���������12345��Ҫ����������54321��
 */

#include <stdio.h>

int main(void)
{
    int x;

    printf("input an integer:\n");
    scanf("%d", &x);
    do
        putchar(x % 10 + '0');
    while ((x/=10) != 0);
    printf("\n");

    return 0;
}