#include <stdio.h>
#include <stdlib.h>

int main()
{
    char c;
    scanf("%c",&c);
    if((c>='0' && c<='9') || (c>='a'&&c<='f') || (c>='A'&&c<='F'))
    {
        if(c>='0' && c<='9')
        printf("%d\n",c-'0');
        if(c>='a' && c<='f')
        printf("%d\n",c-'a'+10);
        if(c>='A' && c<='F')
        printf("%d\n",c-'A'+10);
    }
    else
    printf("%d\n",c);
    return 0;
}
