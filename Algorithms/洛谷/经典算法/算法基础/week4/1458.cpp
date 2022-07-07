//By Guo Wei
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <cstdio>
using namespace std;
int N,C;
int x[100010];
bool Valid(int d)
{
	int last = x[0];
	int settled = 1;
	for(int i = 1; i < N; ++i ) {
		if( x[i] - last >= d ) {
			++ settled ;
			last = x[i];
			if( settled >= C)
				return true;
		}
	}
	return false;
}
int main()
{
	scanf("%d%d",&N,&C);
	for(int i = 0;i < N; ++i)
		scanf("%d",&x[i]);
	sort(x,x+N);
	int L = 1;
	int R = x[N-1] / C + 1;
	
	int lastValid = 0;
	while(L <= R) {
		int mid = L + (R-L)/2;
		if (Valid(mid)) {
			lastValid = mid;
			L = mid + 1; 
		} 
		else 
			R = mid -1;
	}
	printf("%d", lastValid );
	
	return 0;
}
