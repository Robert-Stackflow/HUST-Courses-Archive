/*
bl8469 特殊密码锁
By Guo Wei 
*/
#include <cstdio> 
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
//枚举第一个按钮是否按下的两种情况即可。对于指定的一种情况，后面的事情都是确定的 
int oriLock;
int lock;
int destLock;
inline void SetBit(int & n,int i,int v)
{
	if(v) 
		n |= (1 << i);
	else
		n &= ~(1 << i);
}
inline void FlipBit(int & n,int i)
{
	n ^= (1 << i);
}
inline int GetBit(int n,int i)
{
	return (n >> i) & 1;
}
int main()
{

	char line[40];
	destLock = lock = oriLock = 0;
	cin >> line;
	int N = strlen(line);
	for(int i = 0; i < N; ++i)
		SetBit(oriLock,i, line[i] - '0');
	cin >> line;
	for(int i = 0; line[i]; ++i)
		SetBit(destLock,i, line[i] - '0');
	int minTimes = 1 << 30;
	for(int p = 0; p < 2; ++p) { //p代表最左边按钮 
		lock = oriLock;
		int times = 0;
		int curButton = p;
		for(int i = 0; i < N; ++i) {
			if(curButton) {
				++ times;
				if( i > 0)
					FlipBit(lock,i-1);
				FlipBit(lock,i);
				if( i < N-1)
					FlipBit(lock,i+1);
			}
			if( GetBit(lock,i) != GetBit(destLock,i))  
				curButton = 1;
			else 
				curButton = 0;
		}
		if( lock == destLock) 
			minTimes = min(minTimes ,times);
	}
	if( minTimes == 1 << 30)
		cout << "impossible" << endl;
	else
		cout << minTimes << endl;
	return 0;
}
