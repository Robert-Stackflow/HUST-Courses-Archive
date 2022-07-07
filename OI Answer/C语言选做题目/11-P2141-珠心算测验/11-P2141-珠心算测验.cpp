#include<stdio.h>
int main(void)
{
	int num[105],ans=0,n=0,num_all[20050]={0},check[20050]={0};
	scanf("%d",&n);
	for(int i=1;i<=n;i++) {scanf("%d",&num[i]);num_all[num[i]]=1;}
	for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++)
            check[num[i]+num[j]]++;
    for(int i=1;i<=20001;i++)
        if(check[i]&&num_all[i]) ans++;
    printf("%d",ans);
}
