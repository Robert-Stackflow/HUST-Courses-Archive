#include<stdio.h>
#include<math.h>
int n,k;
int isprime(int n)
{
	for(int i=2;i<=sqrt(n);i++)
		if(n%i==0)return0;
	return 1;
}//�ж��Ƿ�Ϊ���� 
int create(int a,int k,int prior,int *num)
{//aָʾ��ǰ�������ʼֵ����������ظ�
//kָʾʣ�����Ҫ��ȡ����
//priorΪǰ���ۼӵĺ�
//numΪ���������
	int res=0;
	if(!k)	return isprime(prior);
	//�����Ҫ��ȡ�����ѹ��㣬�򷵻��ۼӺ��Ƿ�Ϊ����
	for(int i=a;i<n;i++)
		res+=create(i+1,k-1,prior+num[i],num);
		//�ݹ���һ�����̣��ѵ�ǰ�ĳ�ʼֵ��һ������ȡ������һ
		//ͬʱ�����ѵõ����ۼӺ�
	return res;
	//���õݹ�����ȫ��ϣ��ڹ������𽥰�K�������
	//��ѡȡ��������Ϊ0ʱ��ֱ�ӷ���ǰ����ۼӺ��Ƿ�Ϊ����
}
int main(void)
{
	scanf("%d%d",&n,&k);
	int num[n];
	for(int i=0;i<n;i++)scanf("%d",&num[i]);
	//��������
	printf("%d",create(0,k,0,num));
}
