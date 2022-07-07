//By Guo Wei
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cmath>
using namespace std;
int L,N,M;
int D[50010];
bool Valid(int d)
{
	int removed = 0;
	int last = 0;
	for(int i = 0; i < N; ++i) {
		if( D[i] - last < d ) {
			++ removed; // È¥µô D[i];
			if( removed > M )
				return false; 
		}
		else 
			last = D[i];
	}
	if( L - last < d )
		++ removed;
	if( removed > M )
		return false;
	return true;
}
int main()
{
	cin >> L >> N >> M;
	int s = 1000000100, e;
	int last = 0;
	for(int i = 0;i < N; ++i) {
		cin >> D[i];
		s = min(s,D[i]-last);
		last = D[i];
	}
	s = min(s,L-D[N-1]);
	e = L;
	int lastValid = 0;
	while(s <= e) {
		int mid = s + (e-s)/2;
		if( Valid(mid)) {
			lastValid = mid;
			s = mid + 1;
		}
		else 
			e = mid - 1;
	}
	cout << lastValid ;
	return 0;
}
