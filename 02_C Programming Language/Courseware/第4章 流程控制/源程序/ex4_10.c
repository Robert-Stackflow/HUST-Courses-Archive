/**
【例4.10】 将来自标准输入文件的正文复制到标准输出文件，每次输入和复制一个字符。
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