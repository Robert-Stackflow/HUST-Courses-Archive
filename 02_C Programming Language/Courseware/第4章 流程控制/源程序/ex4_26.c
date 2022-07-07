/**
【例4.26】 输入一个字母，在屏幕正中输出由这个字母决定其高度的字符"金字塔"。例如输入小写字母d，则输出下列左边图形，如果输入大写字母D，则输出右边图形。
 */

#include <stdio.h>
#include <ctype.h>

int main(void)
{
    char c, c1, c2, top;
    int i;

    printf("input a character:\n");
    top = isupper(c = getchar()) ? 'A' : (islower(c) ? 'a' : '\0');
    if (top) {
        for (c1=top; c1<=c; ++c1){
            for (i=1; i<=40-2*(c1-top); ++i)
                putchar(' ');
            for (c2=top; c2<=c1; ++c2)
                printf("%2c", c2);
            for (c2=c1–1; c2>=top; --c2)
                printf("%2c", c2);
            printf("\n");
        } 	/*  end of external for  */
    } 	/*  end of if  */

    return 0;
}