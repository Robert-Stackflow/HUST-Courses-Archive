/* 例3.6  使用puts函数在第一行输出“Hello,”，在第二行输出“World!”。 */

/* 程序3.6.1 */
#include <stdio.h>
int main(void)
{
    char s[20] = "Hello,";
    char *pc = "World!";

    puts(s);
    puts(pc);

    return 0;
}

/* 程序3.6.2 */
/*
#include <stdio.h>

int main(void)
{
    puts("Hello,\nWorld!");

    return 0;
}
*/