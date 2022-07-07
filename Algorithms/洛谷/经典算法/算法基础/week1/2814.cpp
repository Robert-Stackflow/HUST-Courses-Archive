//BL2814 拨钟问题  by Guo Wei
#include <iostream>
#include <bitset>
#include <algorithm>
#include <functional>
#include <cstring>
using namespace std;
int oriClocks[9];
int clocks[9];
const char * moves[9] = { "ABDE","ABC","BCEF","ADG","BDEFH","CFI","DEGH","GHI","EFHI" };
int moveTimes[9] = {0};
int result[9];
int minTimes = 1 << 30;
void Enum(int n) 
{
	if( n >= 9 ) {
		memcpy(clocks,oriClocks,sizeof(clocks));
		int totalTimes = 0;
		for( int i = 0;i < 9 ; ++ i ) { //依次进行9种移动
			if( moveTimes[i] ) { 
				for( int k = 0; moves[i][k]; ++k) {
					clocks[moves[i][k]-'A'] = (clocks[moves[i][k]-'A'] + moveTimes[i]) % 4;
					totalTimes += moveTimes[i];
				}
			}
		}
		int i;
		for( i = 0;i < 9; ++i )
			if( clocks[i])
				break;
		if( i == 9) {
			if( minTimes > totalTimes) {
				minTimes = totalTimes;
				memcpy(result,moveTimes,sizeof(result)); 
			} 
		}
		return ;
	}
	for( int i = 0;i < 4; ++ i ) {
		moveTimes[n] = i;
		Enum(n+1);
	}
	return ;
} 
int main()
{
	for( int i = 0;i < 9 ; ++i )
		cin >> oriClocks[i];
	Enum(0);
	for( int i = 0; i < 9; ++i )
		for( int k = 0; k < result[i] ; ++ k ) 
			cout << i+1 << " ";
	return 0;
}
