/* 例3.5 在键盘上任意输入一个字符，若输入的字符是小写字母，则输出该小写字母对应的大写字母，否则直接输出该字符。 */

#include <stdio.h>

int main(void)
{
    char c;

    putchar(((c=getchar())>='a'&&c<='z') ? c-'a'+'A' : c);

    return 0;
}