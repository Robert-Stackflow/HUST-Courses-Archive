// By Guo Wei
#include <iostream>
#include <algorithm>
using namespace std;
int k;
int a[30];
int len[30]; // len[i]是以a[i]为终点的最长不上升子序列的长度 
int main()
{
	cin >> k;
	for(int i = 0;i < k; ++i) {
		cin >> a[i];
		len[i] = 1;
	}
	for(int i = 1;i < k; ++i) {
		for(int j = 0; j < i; ++j ) {
			if( a[j] >= a[i])
				len[i] = max(len[i],len[j] + 1);
		}
	}
	cout << * max_element(len,len + k) << endl;
	return 0;
}