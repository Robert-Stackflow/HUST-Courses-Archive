#include <stdio.h>
#include <math.h>
int main()
{
    int sign=1,n=1;
    double sum=0.0,t=1.0,e;
    scanf("%lf",&e);
    while(fabs(t)>e)
    {
        sum=sum+t;
        sign*=-1;
        n+=2;
        t=1.0/n*sign;
    }
    sum=sum+t;
    printf("%lf",4*sum);
    return 0;
}

