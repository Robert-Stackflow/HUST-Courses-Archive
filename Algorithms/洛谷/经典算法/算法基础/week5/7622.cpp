#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int a[100010];
int b[100010];
void Merge(int a[],int s,int m, int e,int tmp[])
//从大到小合并[s,m], [m+1,e] 
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
//从大到小合并[s,m], [m+1,e] 
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
		result += MergeSort(a,s,m,tmp); //分别求两边的逆序数 
		result += MergeSort(a,m+1,e,tmp);
		result += Count(a,s,m,e); //然后再o(n)算左边和右边造成的逆序数 。此时要求左边和右边都是从大到小有序的，才能在o(n)时间内算出结果 
		Merge(a,s,m,e,tmp); //从大到小合并，确保排序 
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
