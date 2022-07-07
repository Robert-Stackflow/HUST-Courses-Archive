#include<stdio.h>
long long m,p1,s1,s2,long_,hu_,sod[100005],check=5e18,ans;
long long abs(long long x,long long y);
int main(void)
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%lld",&sod[i]);
    scanf("%lld%lld%lld%lld",&m,&p1,&s1,&s2);
    sod[p1]+=s1;
    for(int i=1;i<m;i++)long_+=(m-i)*sod[i];
    for(int i=n;i>m;i--)hu_+=(i-m)*sod[i];
    long long _long=long_,_hu=hu_;
    for(int i=1;i<=n;i++)
    {
        _long=long_,_hu=hu_;
        if(i<m) _long+=(m-i)*s2;
        else    _hu+=(i-m)*s2;
        long long mid=abs(_long,_hu);
        if(check>mid)   {ans=i;check=mid;}
    }
    printf("%lld",ans);
}
long long abs(long long x,long long y)
{
    if(x>=y)return x-y;
    return y-x;
}
