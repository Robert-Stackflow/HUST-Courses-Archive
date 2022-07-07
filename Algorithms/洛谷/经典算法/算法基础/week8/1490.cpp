//POJ2488 A Knight's Journey  ���� By Guo Wei 
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
{//�� (r,c)��������ʱ�Ѿ�����step�������ܷ�ɹ� 
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
	visited[r][c] = false; //���ݣ�ȡ����һ�����߷���ʹ������������ʱ�����ƻص����� 
	return false;
}
int main()
{
	int t;
	cin >> t;
	for( int tt = 1; tt <= t; ++ tt ) {
		cout << "Scenario #" << tt << ":" << endl;
		cin >> p >> q; // p num, q alph// q��p�� 
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

