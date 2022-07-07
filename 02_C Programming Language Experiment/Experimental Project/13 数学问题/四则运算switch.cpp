#include<stdio.h>
int main()
{
    int x, y;
    float z;
    char b,c;
    scanf("%d%d%c%c",&x,&y,&b,&c);
    switch (c)
	{
    case '+':
        z=(float)(x+y);
        break;
    case '-':
        z=(float)(x-y);
        break;
    case '*':
        z=(float)(x*y);
        break;
    case '/':
        z=(float)(x/y);
        break;
    }
    printf("%.1f",z);
    return 0;
}
