#include <stdio.h>
#include <stdlib.h>

int main()
{
    char c,numchar,numline;
    numchar=0;
    numline=0;
    printf("输入若干行文本，行首输入Ctrl+z结束。\n");
    while (c=getchar()!=EOF)
    {
        numchar++;
        if(c=getchar()=='\n')
            numline++;
    }
    printf("字符数：%d,",numchar);
    printf("行数：%d\n",numline);
    return 0;
}
