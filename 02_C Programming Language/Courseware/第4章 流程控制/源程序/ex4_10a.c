/**
³ÌÐò4.10a£º
 */

#include <stdio.h>

int main(void)
{
    char c;

    printf("input a text end of ctrl+z:\n");
    while ((c=getchar()) != EOF )
        putchar(c);

    return 0;
}