/* ��3.5 �ڼ�������������һ���ַ�����������ַ���Сд��ĸ���������Сд��ĸ��Ӧ�Ĵ�д��ĸ������ֱ��������ַ��� */

#include <stdio.h>

int main(void)
{
    char c;

    putchar(((c=getchar())>='a'&&c<='z') ? c-'a'+'A' : c);

    return 0;
}