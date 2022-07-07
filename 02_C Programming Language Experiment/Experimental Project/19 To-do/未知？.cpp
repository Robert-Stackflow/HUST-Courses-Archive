#include<stdio.h>
int main()
{
    int b=0,s,c=1,a=1;
    while(c<100){
    printf("%d\n",c);
    s=c;
    for(s=c;s/2!=0;s=s/2)
    {
        b=b+(s%2)*a;
        a=a*10;
    }
    b=b+a;
    printf("%d\n",b);
    c=c+1;
    }
    return 0;
}
