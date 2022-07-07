//By Guo Wei
#include <iostream>
#include <cstring>
using namespace std;
const int M = 52;
int waysNK[M][M][M]; // waysNK[i][j][k] 用 <= i的k个数，凑出和为j 
int waysND[M][M];
int waysNO[M][M];


int WaysNK(int i,int j,int k) {
	if( j == 0 && k == 0)
		return 1;
	if( k == 0)
		return 0;
	if( j == 0)
		return 0;
	if( i == 0)
		return 0;
	if( waysNK[i][j][k] != -1)
		return waysNK[i][j][k];
	int result = WaysNK(i-1,j,k);
	if( j >= i) 
		result += WaysNK(i,j-i,k-1);
	waysNK[i][j][k] = result;
	return result;
		
}
int WaysND(int i,int j)
{
	if( j == 0)
		return 1;
	if( i == 0)
		return 0;
	if( waysND[i][j] != -1)
		return waysND[i][j];
	int result = WaysND(i-1,j);
	if( i <= j)
		result += WaysND(i-1,j-i);
	waysND[i][j] = result;
	return result;
}
int WaysNO(int i,int j)
{
	if( j == 0)
		return 1;
	if( i == 0)
		return 0;
	if(waysNO[i][j] != -1)
		return waysNO[i][j];
	int result = WaysNO(i-1,j);
	if( i %2 && i <= j)
		result += WaysNO(i,j-i);
	waysNO[i][j] = result;
	return result; 
}

int main()
{
	int n,k;
	memset(waysNK,0xff,sizeof(waysNK));
	memset(waysND,0xff,sizeof(waysND));
	memset(waysNO,0xff,sizeof(waysNO));
	while(cin >> n >> k) {
		cout << WaysNK(n,n,k) <<endl;
		cout << WaysND(n,n) << endl;
		cout << WaysNO(n,n) <<endl;
	}

	return 0;
}


