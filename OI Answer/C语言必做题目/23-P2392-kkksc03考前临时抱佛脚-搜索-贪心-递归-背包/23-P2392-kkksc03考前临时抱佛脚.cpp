#include<stdio.h>
#define N 4
#define max(m,n) (((m)>(n))?(m):(n))
int main(void)
{
	int work[5],sum=0,dp[100][1500]={0},ans=0;
	for(int i=0;i<N;i++)scanf("%d",&work[i]);
	int time[5][61];
	for(int i=0;i<N;i++)
	{
		sum=0;
		for(int j=0;j<work[i];j++)
		{
			scanf("%d",&time[i][j]);
			sum+=time[i][j];
		}//����ÿ�Ŀÿ�������õ�ʱ�䲢������������ʱ��
		if(work[i]==1) ans+=time[i][0];//�������һ���⣬���׵�
		else if(work[i]==2) ans+=max(time[i][0],time[i][1]);
		//������������⣬�𰸼�Ϊ�ϴ��ʱ��ֵ
		else
		{//������뱳���㷨����Ʒ����work[i]����Ʒ�ļ�ֵ����ʱ���������������ͬ��
		for (int p=1;p<=work[i];++p)//work[i]ָʾ�ÿ�Ŀ��Ŀ����Ŀ
		{
        for (int q=1;q<=sum/2;++q)
		{ //��������Ҳ����ʱ��͵�һ��
            if(q>=time[i][p-1])//q��ʾ��ǰ�ı�������
            //���q���ڵ��ڵ�ǰ��Ŀ�����ʱ����ô��Ʒ��Ϊp�ı�����������
            //����p�Ͳ�����p���������ȡ���ֵ
            dp[p][q]=max(dp[p-1][q],dp[p-1][q-time[i][p-1]]+time[i][p-1]);
            else//���qС�ڵ�ǰ��Ŀ�����ʱ�䣬��p�޷�������Ψһ
            dp[p][q]=dp[p-1][q];
        }
    	}
		ans+=max(sum-dp[work[i]][sum/2],dp[work[i]][sum/2]);
		//�ÿ�Ŀ����ʱ��Ϊ���������ʱ�����ֵ
		}
//		printf("--%d--\n",ans);
	}
	printf("%d",ans);
}
