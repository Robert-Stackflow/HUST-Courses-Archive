#include <stdio.h>
#include <stdlib.h>
int strLength(char s[])
{
    int i=0;
    while (s[i]!='\0')
        ++i;
        return i;
}
int strReverse(char s[])
{
    int i,j;
    for (i=0,j=strLength(s);i<j;i++,j--)
    {
        char t;
        t=s[i];
        s[i]=s[j];
        s[j]=t;
    return s;
    }
}

int main()
{
   char s[1000],t[1000];
   scanf("%s",s);
   printf("%d\n",strLength(s));
   strReverse(s);
   printf("%s",s);
   return 0;
}
