/* ��3.6  ʹ��puts�����ڵ�һ�������Hello,�����ڵڶ��������World!���� */

/* ����3.6.1 */
#include <stdio.h>
int main(void)
{
    char s[20] = "Hello,";
    char *pc = "World!";

    puts(s);
    puts(pc);

    return 0;
}

/* ����3.6.2 */
/*
#include <stdio.h>

int main(void)
{
    puts("Hello,\nWorld!");

    return 0;
}
*/