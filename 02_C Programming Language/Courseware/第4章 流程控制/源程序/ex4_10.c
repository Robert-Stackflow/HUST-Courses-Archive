/**
����4.10�� �����Ա�׼�����ļ������ĸ��Ƶ���׼����ļ���ÿ������͸���һ���ַ���
 */

#include <stdio.h>

int main(void)
{
    char c;

    printf("input a text end of ctrl + z:\n");
    c = getchar();
    while (c != EOF) {
        putchar(c);
        c = getchar();
    }

    return 0;
}