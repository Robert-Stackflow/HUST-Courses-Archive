#include <stdio.h>
#include <stdlib.h>

int main()
{
    int count,max,x,t;
    printf("������һ����������");
    scanf("%d",&x);
    count=max=0;
    while (x){
        t=x%10;
        if(t==0)
        count++;
        if  (t>max)
        max=t;
        x=x/10;
    }
    printf("������%d���㣬���������%d\n",count,max);
    return 0;
}
