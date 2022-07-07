//POJ1321 �������� ���� By Guo Wei 
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
int n,k;
char board[10][10];
int total;
int chessPos[10];
int Dfs(int r,int x)  //ע�⣬���ܲ��ü��仯�ݹ飬��Ϊ�������޺�Ч�� 
{//�ӵ�r�п�ʼ�ڣ����� x������δ�� 
	if( x == 0) 
		return 1;
	if( n - r < x ) //�϶��ڲ����� 
		return 0;
	int total = 0;	
	for( int j = 0; j < n; ++ j ) { //Ҫ�ڵ�r�а� 
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
	total += Dfs(r+1,x); //���ڵ�r�а� 
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
