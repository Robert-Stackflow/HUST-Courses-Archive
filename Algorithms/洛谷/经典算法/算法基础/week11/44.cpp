/* ��n(2<=n<=25)����������һ���ſ����ӵ�i�����ߵ���i+1����Ҫ��ʱt[i]��ʱ��Ƭ��ÿ��ʱ��Ƭ5���ӣ���
Jhon��h(1<=h<=16)��Сʱ����������Щ�����㣨������������ʱ�䣩����ÿ��������ʱ�������������������ʱ��Ƭ��0��
������������ˣ�Ҳ�����ں��ߴ��š�
���ں�i��John������ĵ�һ��ʱ��Ƭ���Ե�����f[i]�����Һ�����ÿ��ʱ��Ƭ���ܵ�����������������һ��ʱ��Ƭ��d[i]��
ע��Johnֻ�ܴӵ�һ�������������������ߣ����ܻ�ͷ�����JohnҪͣ�����ﶼ���ԡ���John����ܵ��������㡣
Ҫ������㷽��������ÿ���������೤ʱ�䡣����ж��ַ�����������ѡ���ڵ�һ������ʱ����ġ�������ж��֣�������
ѡ���ڵڶ���������ʱ�����.....

�ѵ㣺

1) ��·ʱ��ɶ���٣���֪�����׸û��೤ʱ�䴿��������(�����кú��ں��ұߣ���

�����

ö������ͣ�����ĺ����������ֳ�n�ࡣÿ�෽������·ʱ�����ȷ���ġ���ÿ�෽���������Ž⣬Ȼ��������ѡ�š�



��ȷ��ͣ�����ĺ��� x ������£��ٶ�������ʱ����k��ʱ��Ƭ��

����Ԫ��(F,i,j) (1<=i<=x, 1 <= j <= k) ��ʾ��i�ĵ�j��ʱ��Ƭ�ܹ����������Ŀ��F

�����е�(F,i,j)(��x*k������Fֵ�Ӵ�С����ѡǰk�����͹�������ѵ��㷽��




*/


//blg44  1042:Gone Fishing  ��̰��  + ���ȶ��� 
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
		for( end = 1; end <= n ;++ end) { //ö�ٽ����ĺ������������ڹ̶�����ʱ�������¿������� 
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