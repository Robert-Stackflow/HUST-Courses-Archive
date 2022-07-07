//BL6044 鸣人和佐助  状态加维的广搜  by Guo Wei 
//关键思路：状态比位置多一维，即处于该位置时的查克拉数目 
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
	int r,c,ck,steps; //状态：由位置和处于该位置时的查克拉数目组成 
	
	Pos(int rr,int cc,int s,int cck):r(rr),c(cc),ck(cck),steps(s) { };
	Pos() {}
};
queue<Pos> q;
int used[210][210][15]; //used[r][c][ck]表示位于 (r,c)且查克拉数目为 ck 这种状态是否已被扩展 
Pos s,e; 
struct Dir 
{
	int dr,dc;
} dir[4] = {{0,1},{0,-1},{1,0},{-1,0}};


int main()
{
	//freopen("c:\\tmp\\t.txt","r",stdin);
	cin >> M >> N >> T;
	Pos s,e; 
	memset(used,0xff,sizeof(used)); //把周围一圈都设上不能走的标记 
	for( int i = 1;i <= M; ++i)
		for(int j = 1; j <= N; ++j ) {
			cin >> a[i][j];
			if( a[i][j] == '@' ) 
				s = Pos(i,j,0,T);
			else if( a[i][j] == '+') {
				a[i][j] = '*';
				e = Pos(i,j,-1,-1);
			}
		for( int t = 0; t <= T; ++t )
			used[i][j][t] = 0;
	}
	used[s.r][s.c][T] = 1;
	q.push(s);
	while(!q.empty()) {
		Pos p = q.front();
		if( p.r == e.r && p.c == e.c) {
			cout << p.steps << endl;
			return 0;
		}
		q.pop();
		for( int i = 0;i < 4; ++i) {
			int newR = p.r + dir[i].dr;
			int newC = p.c + dir[i].dc;
			if( a[newR][newC] == '*' && ! used[newR][newC][p.ck]) {
					used[newR][newC][p.ck] = 1;
					q.push(Pos(newR,newC,p.steps+1,p.ck));
			}
			if( a[newR][newC] == '#' && p.ck>0 && !used[newR][newC][p.ck-1]) {
					used[newR][newC][p.ck-1] = 1;
					q.push(Pos(newR,newC,p.steps+1,p.ck-1));
			}
		}
	}
	cout << -1 ;
	return 0;
}


