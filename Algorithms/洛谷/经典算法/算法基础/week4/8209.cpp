//By Guo Wei
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cmath>
using namespace std;
int N,M ;
int cost[100100];
bool Valid(int c)
{
	int m = 1; //总月数 
	int curCost = 0; //本月花销 
	for(int i = 0;i < N; ++i) {
		if(cost[i] > c )
			return false; 
		if( curCost + cost[i] > c ) {
			curCost = cost[i];
			++m;
			if( m > M )
				return false;
		}
		else
			curCost += cost[i];
	}
	return true;
}
int main()
{
	cin >> N >> M;
	int L = 1 << 30,R = 0;
	for(int i = 0;i < N; ++i) {
		cin >> cost[i];
		L = min(L,cost[i]);
		R += cost[i];
	}
	int lastValid = 0;
	while( L <= R) {
		int mid = L + (R-L)/2;
		if(Valid(mid)) {
			lastValid = mid;
			R = mid - 1;
		}
		else 
			L = mid +1;
	}
	cout << lastValid ;
	return 0;
}