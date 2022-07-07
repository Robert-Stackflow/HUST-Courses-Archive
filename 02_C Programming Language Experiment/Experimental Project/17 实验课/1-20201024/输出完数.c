#include <stdio.h>
#include <stdlib.h>
int Isperfect(int x){
    int y,sum;
    for(sum=0,y=1;y<=x/2;y++)
    {
        if(!(x%y))
            sum+=y;
    }
    if(sum==x)
        return 1;
    return 0;
}
int main()
{
    int a;
    printf("1000以内的完数有：");
    for (a=1;a<=1000;a++)
    {
        if(Isperfect(a))
            printf("%8d",a);
    }
    return 0;
}
