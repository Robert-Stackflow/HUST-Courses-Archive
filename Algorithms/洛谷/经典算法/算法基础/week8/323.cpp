//POJ1321 棋盘问题 深搜 By Guo Wei 
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
int n,k;
char board[10][10];
int total;
int chessPos[10];
int Dfs(int r,int x)  //注意，不能采用记忆化递归，因为不满足无后效性 
{//从第r行开始摆，还有 x个棋子未摆 
	if( x == 0) 
		return 1;
	if( n - r < x ) //肯定摆不下了 
		return 0;
	int total = 0;	
	for( int j = 0; j < n; ++ j ) { //要在第r行摆 
		if(  board[r][j] == '#' ) {
			int i;
			for( i = 0; i < r; ++ i ) 
				if( chessPos[i] == j ) 
					break;
			if( i == r ) {
				chessPos[r] = j	;
				total += Dfs(i+1,x-1);
			}
		}
	}
	chessPos[r] = -1;
	total += Dfs(r+1,x); //不在第r行摆 
	return total;
}
int main()
{
	while( true) {
		cin >> n >> k;
		if( n == -1 )
			break;
		total = 0;
		memset(chessPos,0xff,sizeof(chessPos));
		for( int i = 0;i < n; ++i)
			for(int j = 0; j < n; ++j ) 
				cin >> board[i][j];
		cout << Dfs(0,k) << endl;
	}
	return 0;
}
