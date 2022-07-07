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
int Dfs(int w,int h,int m) //��m�� 
{
	if( w * h < m+1)
		return INFI;
	if( m == 0)
		return w * h;
	if( minMax[w][h][m] != -1)
		return minMax[w][h][m];
	int mx = 0;	
	mx = INFI;
	for( int i = 1; i <= w -1; ++i ) { //ö�ٵ�һ���������еĸ����з�
		for( int k = 0; k <= m-1; ++ k ) { //ö�����߽��������г�k+1��ĸ����з� 
			int m1 = Dfs(i,h,k);
			int m2 = Dfs(w-i,h,m-1-k);
			mx = min(mx,max(m1,m2));	
		}
	}
	for( int i = 1; i <= h -1; ++i ) {  //ö�ٵ�һ���ĺ����еĸ����з�
		int m1,m2;
		for( int k = 0; k <= m-1; ++ k ) { //ö���ϰ�߽��������г�k+1��ĸ����з� 
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
