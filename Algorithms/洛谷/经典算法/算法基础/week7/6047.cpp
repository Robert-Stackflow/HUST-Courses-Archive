//by Guo Wei 
#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iomanip>
using namespace std;
const int INFI = 0xfffffff;
int W,H,M;
int minMax[30][30][410]; 
int Dfs(int w,int h,int m) //切m刀 
{
	if( w * h < m+1)
		return INFI;
	if( m == 0)
		return w * h;
	if( minMax[w][h][m] != -1)
		return minMax[w][h][m];
	int mx = 0;	
	mx = INFI;
	for( int i = 1; i <= w -1; ++i ) { //枚举第一刀的竖着切的各种切法
		for( int k = 0; k <= m-1; ++ k ) { //枚举左半边接下来被切成k+1块的各种切法 
			int m1 = Dfs(i,h,k);
			int m2 = Dfs(w-i,h,m-1-k);
			mx = min(mx,max(m1,m2));	
		}
	}
	for( int i = 1; i <= h -1; ++i ) {  //枚举第一刀的横着切的各种切法
		int m1,m2;
		for( int k = 0; k <= m-1; ++ k ) { //枚举上半边接下来被切成k+1块的各种切法 
			m1 = Dfs(w,i,k);
			m2 = Dfs(w,h-i,m-1-k);
			mx = min(mx,max(m1,m2));
		}
	}
	minMax[w][h][m] = mx;
	return mx;
}
int main()
{
	while(true) {
		cin >> W >> H >> M;
		if( W == 0 && H == 0)
			break;
		memset(minMax,0xff,sizeof(minMax));
		cout << Dfs(W,H,M-1) << endl;
	}
	return 0;
}
