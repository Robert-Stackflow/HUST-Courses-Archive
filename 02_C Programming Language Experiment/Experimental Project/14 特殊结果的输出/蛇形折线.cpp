#include<stdio.h>
#define eps 10e-6
int main()
{
    long long int a,b,c,i,j;
    double x;
    while(scanf("%lld%lld",&a,&b)!=EOF)
    {
        if(a<b)
            printf("-1");
        if(a==b)
            printf("%lld",b);
        if(a>b)
        {
            c=a+b;
            for(i=2; ; i=i+2)
            { 
                   x=(double)c/i;
                j=i;
                if(x<b)
                break;
            }
            x=x*j/(j-2);
            printf("%lf\n",x);
        }
    }
}
