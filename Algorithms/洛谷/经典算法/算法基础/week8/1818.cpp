//∞Ÿ¡∑  ∫Ï”Î∫⁄ By Guo Wei
#include <iostream>
#include <cstring>
using namespace std;
char maze[30][30];
int visited[30][30];
int area = 0;
int W,H;
void dfs(int r,int c)
{
	if( r < 0|| c < 0 || r >= H || c >= W )
		return;
	if( maze[r][c] == '#' || visited[r][c])
		return;
	++area;
	visited[r][c] = 1;
	dfs(r+1,c);
	dfs(r-1,c);
	dfs(r,c+1);
	dfs(r,c-1);
	
}
int main()
{
	while(1) {
		cin >> W >> H;
		if( W == 0 && H == 0)
			break;
		memset(visited,0,sizeof(visited));
		area = 0;
		int sr,sc;
		for(int i = 0;i < H; ++i)
			for(int j = 0; j < W; ++j) {
				cin >> maze[i][j];
				if( maze[i][j] == '@') {
					sr = i;
					sc = j;
				}
			}
		dfs(sr,sc);
		cout << area << endl;
	}
}
