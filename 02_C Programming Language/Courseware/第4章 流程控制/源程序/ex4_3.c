/* ����4.3�� ������������������С�����˳��������������� */

#include <stdio.h>

int main(void)
{
    int a, b;

    printf("input a, b:\n");
    scanf("%d%d", &a, &b);
    {
        int t;

        if (a > b) {
            t = a; a = b; b = t;
        }
    }
    printf("a=%d, b=%d\n", a, b);

    return 0;
}