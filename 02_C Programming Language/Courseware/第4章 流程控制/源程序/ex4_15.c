/**
����4.15�� ����һ����������0Ϊ�����������������һ��ֵ��
 */

#include <stdio.h>

int main(void)
{
    int x, max;

    printf("input a group integer end of 0��\n");
    scanf("%d", &x);
    max = x;
    for( ; x != 0; ) {
        scanf("%d", &x);
        if (max < x)
            max = x;
    }
    printf("max=%d\n", max);

    return 0;
}