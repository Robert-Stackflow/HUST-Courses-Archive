//blg1289 by guo wei  Tian Ji -- The Horse Racing 贪心 


#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
int tian[1100];
int king[1100];
int main()
{
	int n;
	while(cin >> n) {
		if( n == 0)
			break;
		for(int i = 0;i < n; ++i)
			cin >> tian[i];
		for(int i = 0;i < n; ++i)
			cin >> king[i];
		sort(tian,tian+n,greater<int>());
		sort(king,king+n,greater<int>());
		int tianHead = 0;
		int kingHead = 0;
		int tianTail = n-1;
		int kingTail = n-1;
		int total = 0;
		while(tianHead <= tianTail ) {
			if ( tian[tianHead] > king[kingHead]) {
				++tianHead;
				++kingHead;
				total += 200;
			}
			else if( tian[tianHead] < king[kingHead]) {
				++kingHead;
				-- tianTail;
				total -= 200;
			}
			else {
				if (tianTail == tianHead) 
					break;
				if( tian[tianTail] > king[kingTail]) {
					-- tianTail;
					-- kingTail;
					total += 200;
				}
				else {
					if ( tian[tianTail] < king[kingHead])  
						total -= 200;  
					--tianTail;
					++kingHead;  
				}
			}
		}
		cout << total << endl;
	}
}

/*第一个错误：1)认为最快的两个马一样快，就碰掉
	2) 在最快马相同时，认为最慢的两个马一样快，就碰掉 ****。其实还是应该拿最慢马去和对方最快马比。考虑两个序列完全相同的情况 
	3)  没考虑到最后剩下两个马一样快的情况 
	5)  在最快马等速时，认为自己的尾马一定比对方的头马慢

问题的关键是，头马一样快，且尾马也一样快，则用自己尾马对对方头马。证明：替换法。

假设最优法是两个尾马兑掉，在这种情况下的最佳做法里面，对方的头马a，对的是我的马x

那么我可以维持其它对局不变，用我的尾马 z对a, x对对方的尾马b  (z=b)

若a>x  ，则变换后，a还是赢的，但我方原来输掉的x >= b，变换后的结果不会更差
若a=x,  则变换后， a对z, x 对b。
    若a>z,则 x > b (因z=x) ，还是扯平，没有变得更差
    若a = z，则x=b,还是扯平，也没有变得更差 


	