#include<stdlib.h>
#include<stdio.h>
#include<string.h>
int  mystrlen(char *s)
{
    if (*s==0)
    {
        return 0;
    }
    else
    {
        return 1 + mystrlen(s + 1);
    }
}

int main(void)
{
	char s[100];
	int strlenth = 0;
	scanf("%s", &s);
	strlenth = mystrlen(s);
	printf("%d", strlenth);
	return 0;
}
