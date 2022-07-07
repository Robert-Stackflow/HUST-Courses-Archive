/* 有n(2<=n<=25)个湖从左到右一字排开。从第i个湖走到第i+1个湖要耗时t[i]个时间片（每个时间片5分钟）。
Jhon有h(1<=h<=16)个小时可以用在这些湖钓鱼（包括湖间行走时间）。在每个湖待的时间必须是整数个整数个时间片或0。
就算钓不着鱼了，也可以在湖边呆着。
对于湖i，John在那里的第一个时间片可以钓到鱼f[i]条，且后续的每个时间片，能钓到的鱼数量都比上一个时间片少d[i]。
注意John只能从第一个湖出发，从左往右走，不能回头。最后John要停在哪里都可以。问John最多能钓多少条鱼。
要输出钓鱼方案，即在每个湖各呆多长时间。如果有多种方案，则优先选择在第一个湖呆时间最长的。如果还有多种，则优先
选择在第二个湖呆的时间最长的.....

难点：

1) 走路时间可多可少，不知道到底该花多长时间纯钓鱼才最好(可能有好湖在很右边）。

解决：

枚举最终停下来的湖，将方案分成n类。每类方案的走路时间就是确定的。在每类方案里找最优解，然后再优中选优。



在确定停下来的湖是 x 的情况下，假定纯钓鱼时间是k个时间片。

用三元组(F,i,j) (1<=i<=x, 1 <= j <= k) 表示湖i的第j个时间片能够钓的鱼的数目是F

将所有的(F,i,j)(共x*k个）按F值从大到小排序，选前k个，就构成了最佳钓鱼方案




*/


//blg44  1042:Gone Fishing  难贪心  + 优先队列 
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <queue>
#include <vector>
#include <cstdlib>
#include <cstdio> 
#include <cstring>
using namespace std;
const int maxL = 30;
int f[maxL];
int d[maxL];
int t[maxL];
int maxFishes = -1;
int lakeTime[maxL];
int bestLakeTime[maxL];
struct Lake {
	int No;
	int f;
	bool operator<(const Lake & l) const
	{
		if( f == l.f) 
			return No > l.No;
		return f < l.f;
	}
};
int main()
{
	int n,h;
	while(cin  >> n) {
		if( n == 0)
			break;
		maxFishes = -1;
		cin >> h;
		for(int i = 1;i <= n; ++i)
			cin >> f[i];
		for(int i = 1;i <= n; ++i)
			cin >> d[i];
		for(int i = 1;i < n; ++i)
			cin >> t[i];
		int end;
		for( end = 1; end <= n ;++ end) { //枚举结束的湖，这样就能在固定工作时间的情况下考虑问题 
			int total = 0;
			memset(lakeTime,0,sizeof(lakeTime));
			int workTime = h * 60 / 5;
			for(int i = 1;i < end; ++i) 
				workTime -=  t[i];
			priority_queue<Lake> pq;
			for(int i = 1; i <= end; ++i)
				pq.push(Lake{i,f[i]}); 
			for(int t = 0; t < workTime; ++t) {
				Lake lk = pq.top();
				pq.pop();
				total += lk.f;
				++lakeTime[lk.No];
				if( lk.f >= d[lk.No])
					lk.f -= d[lk.No];
				else
					lk.f = 0;
				pq.push(lk);
			}
			if ( total > maxFishes ) {
				maxFishes = total;
				memcpy(bestLakeTime,lakeTime,sizeof(lakeTime));
			}
			else if( total == maxFishes) {
				for(int i = 1;i <= n; ++i) {  
					if( lakeTime[i] > bestLakeTime[i]) {
						memcpy(bestLakeTime,lakeTime,sizeof(lakeTime));
						break;
					}
					else if( lakeTime[i] < bestLakeTime[i])  
						break;
				}							
			}
		}
		for(int i = 1; i <= n; ++i)
			if( i != n)
				cout << bestLakeTime[i] * 5 << ", ";
			else
				cout << bestLakeTime[i] * 5 <<endl;
		cout << "Number of fish expected: " << maxFishes << endl << endl;
	}
	return 0;
}