//���˺�����  ���Ѽ�֦  by Guo Wei 
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
int midSteps[210][210][20];  //midSteps[r][c][ck]���ߵ� (r,c)������ck�������ʱ������·������ 
//�����״̬ʱ·����ͬ���ò�����ĵط�Ҳ��һ������һ���Ƕ����ڴ���㵽 (r,c)��·���� 
//����һ��·����㵽 (r,c,ck)������A (A�����ţ�,��(r,c)���յ㲿���� B,��dfs���߷���A ,B�ض��޽���
//��ô������Ա�A���ŵ�·��C ������(r,c,ck)����һ�����Դ�(r,c,ck)�ߵ��յ� --- ֱ����B�Ϳ�����(���B��C�޽��㣩 
//���B��C�н���(m,n)����ôֱ�Ӿ�����m,n)���ܵ��յ��ˣ������þ���(r,c,ck)�����������߷��϶��� A+B���š�
//��֮��ֻҪ�б�A����·�����r,c,ck),��ô A���߷��Ϳ��Ա��񶨣� 
Pos s,e; 
int minSteps;
int steps;
struct Dir 
{
	int dr,dc;
};
Dir dir[4] = {{0,1},{0,-1},{1,0},{-1,0}};
void ChangeDir ( int dr,int dc) //���������ʱ���180ms -> 100ms��60ms ����Ҫ���Ҳ�ܹ� 
{ //������㵽Ŀ��Ĳ�ı��������� 
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
	if ( steps >= midSteps[r][c][ck]) //�ĳ� > ����ʱ 
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
	memset(used,0xff,sizeof(used)); //����ΧһȦ�����ϲ����ߵı�� 
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


