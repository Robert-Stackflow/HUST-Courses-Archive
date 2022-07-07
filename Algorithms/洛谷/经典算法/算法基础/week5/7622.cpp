#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int a[100010];
int b[100010];
void Merge(int a[],int s,int m, int e,int tmp[])
//�Ӵ�С�ϲ�[s,m], [m+1,e] 
{
	int pb = 0;
	int p1 = s,p2 = m+1;
	while( p1 <= m && p2 <= e) {
		if( a[p1] > a[p2]) 
			tmp[pb++] = a[p1++];
		else 
			tmp[pb++] = a[p2++];
	}
	while( p1 <= m) 
		tmp[pb++] = a[p1++];	
	while( p2 <= e)
		tmp[pb++] = a[p2++];
	for(int i = 0;i < e-s+1; ++i)
		a[s+i] = tmp[i];
}

long long Count(int a[],int s,int m, int e)
//�Ӵ�С�ϲ�[s,m], [m+1,e] 
{
	long long result = 0;
	int p1 = s,p2 = m+1;
	while( p1 <= m && p2 <= e) {
		if( a[p1] > a[p2]) {
			result += e-p2+1;
			++p1;
		}
		else 
			++p2;
	}
	return result;
}

long long MergeSort(int a[],int s,int e,int  tmp[])
{
	long long result = 0;
	if( s < e) {
		int m = s + (e-s)/2;
		result += MergeSort(a,s,m,tmp); //�ֱ������ߵ������� 
		result += MergeSort(a,m+1,e,tmp);
		result += Count(a,s,m,e); //Ȼ����o(n)����ߺ��ұ���ɵ������� ����ʱҪ����ߺ��ұ߶��ǴӴ�С����ģ�������o(n)ʱ���������� 
		Merge(a,s,m,e,tmp); //�Ӵ�С�ϲ���ȷ������ 
	}
	return result;
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i = 0;i < n; ++i)
		scanf("%d",&a[i]);
	printf("%lld",MergeSort(a,0,n-1,b));
	return 0;
}
