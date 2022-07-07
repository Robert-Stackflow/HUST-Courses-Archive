#include<stdio.h>
#include<string.h>
int abs(int n)
{
    if(n<0)return -n;
    else return n;
}
int main(void)
{
    int n;
    scanf("%d",&n);
    int bf[105];
    for(int i=n;i>=0;i--)
    scanf("%d",&bf[i]);
    for(int i=n;i>=0;i--)
    {
        if(bf[i]<0)
        {
            printf("-");
            if(abs(bf[i])!=1||i==0)printf("%d",abs(bf[i]));
            if(i==1)    printf("x");
            else if(i!=0) printf("x^%d",i);
        }
        else if(bf[i]==0) continue;
        else
        {
            if(i!=n)    printf("+");
            if(abs(bf[i])!=1||i==0)printf("%d",abs(bf[i]));
            if(i==1)    printf("x");
            else if(i!=0) printf("x^%d",i);
        }
    }
}
