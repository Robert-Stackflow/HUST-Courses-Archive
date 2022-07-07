/* 例3.26虚读转换说明在格式输入中的作用举例。 */

#include <stdio.h>

int main(void)
{
    short x1;
    char x2;

    printf("input a integer and a character:\n");
    scanf("%hd", &x1);
    scanf("%*c %c", &x2);
    printf("x1=%d, x2=%c\n", x1, x2);

    return 0;
}