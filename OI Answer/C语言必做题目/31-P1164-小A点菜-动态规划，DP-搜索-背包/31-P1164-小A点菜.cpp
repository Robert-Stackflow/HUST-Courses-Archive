#include<stdio.h>
#define max(m,n) (((m)>(n))?(m):(n))
int n,m,dp[105][10005],menu[105];
//dp����洢����ѡ����p�����ҽ�Ǯ����Ϊq�ķ�����
int main(void)
{
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++) scanf("%d",&menu[i]);
	for (int p=1;p<=n;++p)
	{
        for (int q=1;q<=m;++q)
		{  
            if(q>menu[p-1])	dp[p][q]=dp[p-1][q]+dp[p-1][q-menu[p-1]];
            //�����ǰ�����������ڼ۸���ô����ѡ�Ͳ�ѡ����ѡ��
            //�취�����͵��ڳ�����˵İ취���벻������˵İ취��֮��
            else if(q==menu[p-1])	dp[p][q]=dp[p-1][q]+1;
			//�����������ǡ�õ��ڼ۸���ô��ֻ��һ��ѡ��
			//��ʱ����������ð�������������е���dp[p][0]=0�����Ҫ���Ϊ1
            else	dp[p][q]=dp[p-1][q];
			//����ֻ�ܲ�ѡ���취������ֻ�ܳ�Ϯ��ǰi-1���˵İ취����
        }
	}
	printf("%d",dp[n][m]);
}
//�㷨�Ľ�֮��ά���
#include<stdio.h>
int n,m,a[N],f[10010];
int main()
{

	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	f[0]=1;
	for(int i=1;i<=n;i++)
	    for(int j=m;j>=a[i];j--)
	    	f[j]=f[j]+f[j-a[i]];
	printf("%d",f[m]);
	return 0;
}

