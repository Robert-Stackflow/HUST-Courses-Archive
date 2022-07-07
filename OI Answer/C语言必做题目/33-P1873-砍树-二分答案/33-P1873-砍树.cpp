#include<stdio.h>
#include<math.h>
#define ll long long
ll _max(ll*,ll);
int main(void)
{
	ll n,m,hs=0;
	scanf("%lld%lld",&n,&m);
	ll t[n];
	for(ll i=0;i<n;i++) scanf("%lld",&t[i]);
	ll min=0,max=_max(t,n),mid;
	while(min<=max)
	{
		hs=0;
		mid=(min+max)/2;
		for(int i=0;i<n;i++)
			if(t[i]>mid)
				hs+=(t[i]-mid);
		if(hs<m)	max=mid-1;
		else min=mid+1;
	}
	printf("%d",min-1);
}
ll _max(ll*a,ll count)
{
    ll max=0;
	for(ll i=0;i<count;i++)
		if(a[i]>max) max=a[i];
	return max;
}
