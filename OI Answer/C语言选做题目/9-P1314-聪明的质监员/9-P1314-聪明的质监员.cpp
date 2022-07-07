#include<stdio.h>
#define ll long long
#define MAX 200020
#define max(x,y) (((x)>(y))?(x):(y))
#define min(x,y) (((x)<(y))?(x):(y))
ll n,m,l[MAX],r[MAX],check,maxn,w[MAX],v[MAX];
int judge(int check);
ll myabs(ll x);
ll s,sign,ans=1e16,minn=1e16;
int main(void)
{
    scanf("%lld%lld%lld",&n,&m,&s);
    for(int i=1;i<=n;i++)
    {
        scanf("%lld%lld",&w[i],&v[i]);
        maxn=max(maxn,w[i]);
        minn=min(minn,w[i]);
    }
    for(int i=1;i<=m;i++)
        scanf("%lld%lld",&l[i],&r[i]);
    int left=minn-1,right=maxn+2;
    while(left<=right)
    {
    check=(left+right)/2;
    if(judge(check)) left=check+1;
    else right=check-1;
    ans=min(ans,sign);
    }
    ans=min(ans,sign);
    printf("%lld",ans);
    return 0; 
}
int judge(int check)
{
    ll y_sum=0;
    sign=0;
    ll w_sum[MAX]={0},v_sum[MAX]={0};
    for(int i=1;i<=n;i++)
    {
        if(w[i]>=check)
        {
            w_sum[i]+=w_sum[i-1]+1;
            v_sum[i]+=v_sum[i-1]+v[i];
        }
        else
        {
            w_sum[i]+=w_sum[i-1];
            v_sum[i]+=v_sum[i-1];
        }
    }
    for(int i=1;i<=m;i++)
        y_sum+=(w_sum[r[i]]-w_sum[l[i]-1])*(v_sum[r[i]]-v_sum[l[i]-1]);
    sign=myabs(y_sum-s);
    if(y_sum>s) return 1;
    else return 0;
}
ll myabs(ll x)
{
    if(x>0) return x;
    else return -x;
}
