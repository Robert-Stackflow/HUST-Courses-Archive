/**
����4.23�� ����10��������������������ĸ�����ƽ��ֵ��
 */

#include <stdio.h>

int main(void)
{
    int a, i, k, x;

    printf("input 10 numbers:\n");
    for (a=i=k=0; i<10; ++i) {
        scanf("%d", &x);
        if (x <= 0)
            continue;  /* �Ը����������� */
        a += x;        /* ���������ĺͣ�����a */
        ++k;          /* �����ĸ��� */
    }
    if (k)
        printf("numbers=%d��average=%f\n", k, 1.0 * a / k);

    return 0;
}