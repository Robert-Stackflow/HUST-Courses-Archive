//POJ2488 A Knight's Journey  深搜 By Guo Wei 
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
int visited[30][30];
struct Pos
{
	int r,c;
};
Pos path[30] ;
Pos dir[8] = {{ -2,-1},{-2,1},{-1,-2},{-1,2},
			  {1,-2},{1,2} ,{ 2,-1},{2,1} };
int p,q;
bool Dfs(int r, int c,int step)
{//从 (r,c)出发，此时已经走了step步，看能否成功 
	if( step == p * q )
		return true;
	if( r < 0 || r >= q || c < 0 || c >= p )
		return false;	
	if( visited[r][c] )
		return false;
	visited[r][c] = 1;
	path[step].r = r;
	path[step].c = c;
	for( int i = 0;i < 8; ++ i ) {
		if ( Dfs( r + dir[i].r,c + dir[i].c, 
		step + 1 ))
			return true;
	}
	visited[r][c] = false; //回溯，取消这一步的走法，使得走其他步的时候，能绕回到这里 
	return false;
}
int main()
{
	int t;
	cin >> t;
	for( int tt = 1; tt <= t; ++ tt ) {
		cout << "Scenario #" << tt << ":" << endl;
		cin >> p >> q; // p num, q alph// q行p列 
		memset(visited,0,sizeof(visited));
		int i;
		for(  i = 0; i < q; ++i )
			for( int j = 0; j < p; ++ j ) {
				if (Dfs(i,j,0)) {
					i = q + 10;
					for( int k = 0; k < p * q; ++ k)
						cout << char (path[k].r + 'A')
						 << (path[k].c + 1) ;
					break;
				}
			}
		if( i == q ) 
			cout << "impossible";
		cout << endl << endl;
	}
}

