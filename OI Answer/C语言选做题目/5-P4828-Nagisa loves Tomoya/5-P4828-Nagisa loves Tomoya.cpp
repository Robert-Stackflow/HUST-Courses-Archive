#include<stdio.h>
#define sign 998244353
int main(void)
{
    long long n,q,x,y,ans=0;
    scanf("%lld",&n);
    long long num[1000000];
    for(int i=1;i<=n;i++) scanf("%lld",&num[i]);
    scanf("%lld",&q);
    long long add[2010][2010];
    add[0][0]=1;
    for(int i=1;i<2010;i++)
    {
        add[i][0]=1;
        for(int j=1;j<2010;j++)
            add[i][j]=(add[i-1][j]+add[i-1][j-1])%sign;
    }
    for(int i=1;i<=q;i++)
    {
        ans=0;
        scanf("%lld%lld",&x,&y);
        for(int j=0;j<=x;j++)
        {
            ans=(ans+num[y]*add[x][j])%sign;
            if(n==y)    y=1;
            else        y++;
        }
        printf("%lld\n",ans%sign);
    }
}
