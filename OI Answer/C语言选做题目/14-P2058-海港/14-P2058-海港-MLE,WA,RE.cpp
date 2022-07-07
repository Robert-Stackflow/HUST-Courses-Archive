#include<stdio.h>
typedef struct ship
{
    long long t;
    int k;
    int country[300005];
}list;
int compute(int*check);
int main(void)
{
	int n;
	scanf("%d",&n);
	list all[n+2];
	for(int i=1;i<=n;i++)
    {
        int p=i;
        int check[100002]={0};
        scanf("%lld%d",&all[i].t,&all[i].k);
        for(int j=1;j<=all[i].k;j++)    scanf("%d",&all[i].country[j]);
        for(;all[i].t-all[p].t<86400&&p>=1;p--);
        p++;
        for(int q=p;q<=i;q++)
            for(int j=1;j<=all[p].k;j++)
                check[all[q].country[j]]++;
        printf("%d\n",compute(check));
    }
}
int compute(int*check)
{
    int ans=0;
    for(int i=1;i<100000;i++)
        if(check[i]) ans++;
    return ans;
}
