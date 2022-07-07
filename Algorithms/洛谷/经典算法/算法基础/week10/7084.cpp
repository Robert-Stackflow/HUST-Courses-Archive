//POJ3984 迷宫问题 广搜  by Guo Wei 
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
struct Pos 
{
	int r,c;
	int father;
	Pos(int rr=0,int cc=0,int ff=0):r(rr),c(cc),father(ff) { }
};

int maze[8][8];
Pos que[100];
int head,tail;
Pos dir[4] = {Pos(-1,0),Pos(1,0),Pos(0,-1),Pos(0,1)}; //移动方向 
int main()
{
	memset(maze,0xff,sizeof(maze)); 
	for( int i = 1;i <= 5; ++i)
		for (int j = 1; j <= 5; ++j )
			cin >> maze[i][j];
	head = 0; 
	tail = 1;
	que[0] = Pos(1,1,-1);
	
	while( head != tail ) {
		Pos ps = que[head];
		if( ps.r == 5 && ps.c == 5 ) {
			vector<Pos> vt;
			while(true) {
				vt.push_back(Pos(ps.r,ps.c,0));
				if( ps.father == -1 )
					break;
				ps = que[ps.father];
			};  
			for( int i = vt.size()-1; i >= 0; -- i )
				cout << "(" << vt[i].r -1 << ", " << vt[i].c-1 << ")" << endl;
			return 0;					
		}
		
 		
		
		else {
			int r = ps.r, c = ps.c;	
			for( int i = 0;i < 4; ++i)
				if(! maze[r+dir[i].r][c+dir[i].c]) {
					que[tail++] = Pos(r+dir[i].r,c+dir[i].c,head);
					maze[r+dir[i].r][c+dir[i].c] = 1;
				}
			++head;
		}
	}
	return 0;
}
