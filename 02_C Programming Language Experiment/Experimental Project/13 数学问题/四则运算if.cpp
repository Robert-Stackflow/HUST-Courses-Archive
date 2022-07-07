#include<stdio.h>
int main()
{
    int x, y;
    float z;
    char b,c;
    scanf("%d%d%c%c",&x,&y,&b,&c);
   	if (c=='+')
        z=(float)(x+y);
    if (c=='-')
        z=(float)(x-y);
    if (c=='*')
        z=(float)(x*y);
    if (c=='/')  
        z=(float)(x/y); 
    printf("%.1f",z);
    return 0;
}
