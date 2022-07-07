//鸣人和佐助  深搜剪枝  by Guo Wei 
#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <queue>
using namespace std;
int M,N,T;
char a[210][210];
struct Pos
{
	int r,c;
	Pos(int rr,int cc):r(rr),c(cc) { };
	Pos() {}
};
queue<Pos> q;
int used[210][210];
int midSteps[210][210][20];  //midSteps[r][c][ck]是走到 (r,c)，还有ck个查克拉时的最优路径长度 
//到达此状态时路径不同，用查克拉的地方也不一样，但一定是都用在从起点到 (r,c)的路上了 
//假设一条路从起点到 (r,c,ck)部分是A (A不够优）,从(r,c)到终点部分是 B,则按dfs的走法，A ,B必定无交点
//那么如果能以比A更优的路径C 到达了(r,c,ck)，则一定可以从(r,c,ck)走到终点 --- 直接走B就可以了(如果B和C无交点） 
//如果B和C有交点(m,n)，那么直接经过（m,n)就能到终点了，都不用经过(r,c,ck)。而且这种走法肯定比 A+B更优。
//总之，只要有比A更优路径到达（r,c,ck),那么 A的走法就可以被否定！ 
Pos s,e; 
int minSteps;
int steps;
struct Dir 
{
	int dr,dc;
};
Dir dir[4] = {{0,1},{0,-1},{1,0},{-1,0}};
void ChangeDir ( int dr,int dc) //加上这个，时间从180ms -> 100ms或60ms ，不要这个也能过 
{ //根据起点到目标的差，改变搜索方向 
	if( dr > 0 && dc > 0 ) {
		dir[0].dr = 1;
		dir[0].dc = 0;
		dir[1].dr = 0;
		dir[1].dc = 1;
		dir[2].dr = -1;
		dir[2].dc = 0;
		dir[3].dr = 0;
		dir[3].dc = -1;
	}
	else if( dr > 0 && dc < 0) {
		dir[0].dr = 1;
		dir[0].dc = 0;
		dir[1].dr = 0;
		dir[1].dc = -1;
		dir[2].dr = -1;
		dir[2].dc = 0;
		dir[3].dr = 0;
		dir[3].dc = 1;
	}
	else if( dr < 0 && dc > 0) {
		dir[0].dr = -1;
		dir[0].dc = 0;
		dir[1].dr = 0;
		dir[1].dc = 1;
		dir[2].dr = 1;
		dir[2].dc = 0;
		dir[3].dr = 0;
		dir[3].dc = -1;
	}
	else {
		dir[0].dr = -1;
		dir[0].dc = 0;
		dir[1].dr = 0;
		dir[1].dc = -1;
		dir[2].dr = 1;
		dir[2].dc = 0;
		dir[3].dr = 0;
		dir[3].dc = 1;
	}
}
void Dfs(int r,int c,int ck)
{
	if( used[r][c] )
		return;
	used[r][c] = 1;	
	++ steps;
	if ( r == e.r && c == e.c) {
		minSteps = min(minSteps,steps);
		goto ToReturn;
	}
	if( steps + abs(r-e.r)+abs(c-e.c) >= minSteps ) 
		goto ToReturn;
	if ( steps >= midSteps[r][c][ck]) //改成 > 都超时 
		goto ToReturn;
	midSteps[r][c][ck] = steps;
	ChangeDir(e.r-r,e.c-c);
	int newR,newC;
	for( int i = 0;i < 4; ++i) {
		newR = r + dir[i].dr;
		newC = c + dir[i].dc;
		if( a[newR][newC] == '*' && !used[newR][newC])
			Dfs(newR,newC,ck);
		else if( a[newR][newC] == '#' && !used[newR][newC] && ck > 0 ) 
			Dfs(newR,newC,ck-1);
	}
ToReturn:	
	used[r][c] = 0;
	--steps;
	return ;
}
int main()
{
	cin >> M >> N >> T;
	memset(used,0xff,sizeof(used)); //把周围一圈都设上不能走的标记 
	for( int i = 1;i <= M; ++i)
		for(int j = 1; j <= N; ++j ) {
			cin >> a[i][j];
			if( a[i][j] == '@' ) 
				s = Pos(i,j);
			else if( a[i][j] == '+') {
				a[i][j] = '*';
				e = Pos(i,j);
			}
			used[i][j] = 0;
		}
	for( int i = 0;i < 210; ++i)
		for(int j = 0; j < 210; ++j )
			for(int k = 0;k < 20; ++k)
				midSteps[i][j][k] = 0xfffffff;

	minSteps = 0xfffffff;
	steps = 0;
	int dr = e.r - s.r;
	int dc = e.c - s.c;
	ChangeDir(dr,dc);	
	Dfs(s.r,s.c,T);
	if( minSteps != 0xfffffff)
		cout << minSteps-1;
	else
		cout << -1 ;
	return 0;
}


