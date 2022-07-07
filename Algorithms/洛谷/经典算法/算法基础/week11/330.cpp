//blg330 by Guo Wei  Radar Installation 贪心 


/*

x轴是海岸线，x轴上方是海洋。海洋中有n（1<=n<=1000)个岛屿，可以看作点。

给定每个岛屿的坐标（x,y)，x,y 都是整数。

当一个雷达（可以看作点）到岛屿的距离不超过d(整数），则认为该雷达覆盖了该岛屿。

雷达只能放在x轴上。问至少需要多少个雷达才可以覆盖全部岛屿。


1) 对每个岛屿P,可以算出，覆盖它的雷达，必须位于x轴上的区间[Ps,Pe]。
2) 如果有雷达位于某个x轴区间 [a,b]，称该雷达覆盖此区间。问题转换为，要在x轴上放几个雷达，才能覆盖全部区间[P1s,P1e],[P2s,P2e]....[Pns,Pne]


重要结论：如果可以找到一个雷达同时覆盖多个区间，那么把这多个区间按起点x坐标从小到大排序 ，则最后一个区间(起点最靠右的）k的起点，就能覆盖所有区间

证明：如果它不能覆盖某个区间x,那么它必然位于1） x起点的左边，或者2）x终点的右边。
情况1） 和 k的起点是最靠右的矛盾
情况2) 如果发生，则不可能找到一个点同时覆盖x和k，也和前提矛盾 

有了这个结论，就可以只挑区间的起点来放置雷达了。

1） 将所有区间按照起点从小到大排序，并编号0 - (n-1)
2） 依次考察每个区间的起点，看要不要在那里放雷达。开始，所有区间都没被覆盖，所以目前编号最小的被覆盖的区间的编号 firstNoConverd = 0
3)  考察一个区间i的起点xi的时候，要看从 firstNoCovered到 区间i-1中是否存在某个区间c,不会被xi覆盖。如果没有，则不在xi放雷达，接着往下看。如果有，那么c的终点肯定在xi的左边，因此不可能用同一个雷达
覆盖 c 和i。即能覆盖c的点，已经不可能覆盖i和i后面的区间了。此时，为了覆盖c，必须放一个雷达了，放在 区间 i-1的左端点即可覆盖所有从
firstNoCovered到 i-1的区间。因为当初考察 i-1的左端点z时候，并没有发现z漏覆盖了从 firstNoCovered 到 i-2 之间的任何一个区间
。放完雷达后，将 firstNoCovered改为i，再做下去。 


复杂度O(n^2)

证明：

替换法。考虑不用此算法获得的最佳雷达摆放放案。将其所有雷达按坐标从小到大排序得到 x1,x2....

用此算法得到的雷达坐标则为 y1,y2....


先证明x1可以用y1替换

用S(x)表示贪心法中区间x的起点，假设y1 = S(i)


若x1 < y1，则用y1替换x1没问题，因y1覆盖了区间0到i,x1覆盖的区间更少
若x1 > y1，则分两种情况讨论x1：
	1) x1 < S(i+1) 因x1不能覆盖 i+1及以后区间，且i及以前的区间已经都被y1覆盖，所以将x1用 y1替换，不会有损失。
	2) x1 >= S(i+1)
           贪心法中，在区间i起点放雷达，是因为如果不放而在S(i+1)放雷达，则该雷达不能覆盖i及其前面的某个区间C。
           若x1>=S(i+1),则x1也不能覆盖C。xi(i>1)更加不能。因此 x1 >= S(i+1) 是不可能的。

类似地证明，假设xi可以被yi替换，则 xi+1也可以被yi+1替换。


*/
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
const double eps = 1e-6;


int n,d;
struct Seg
{
	double x1,x2;
	bool operator < (const Seg & s)
	{
		return x1 - s.x1 < -eps;
	}
};

Seg segs[1100];
int main()
{
	int t = 0;
	while(cin >> n >> d ) {
		if ( n == 0)
			break;
		++t;
		bool bad = false;
		for(int i = 0;i < n; ++i) {
			int x,y;
			cin >> x >> y;
			if ( y > d ) {
				bad = true;
				continue;
			}
			segs[i].x1 = x - sqrt( d*d - y*y);
			segs[i].x2 = x + sqrt( d*d - y*y);
		}
		//上面算出每个岛屿所需雷达的分布区间 
		if(bad) {
			cout << "Case " << t << ": -1" << endl;
			continue;
		}
		sort(segs,segs+n); //区间按起点排序 
		int firstNoCovered = 0; 
		int total = 1;
		for(int i = 0;i < n; ++i) {  //对每个起点 
			for(int k = firstNoCovered; k < i; ++k ) {
				if( segs[k].x2 < segs[i].x1 ) {
					++total;
					firstNoCovered = i;	
					break;
				}
			}
		}
		cout << "Case " << t << ":" << " " << total << endl;
	}
}

