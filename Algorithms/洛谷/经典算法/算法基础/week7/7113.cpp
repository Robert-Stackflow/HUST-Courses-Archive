//by Guo Wei
#include <iostream>
#include <algorithm>
using namespace std;
int N,M;
struct Item {
	int w,d;
};
Item items[3500];
int F[13000];
int main()
{
	cin >> N >> M;
	for( int i = 1; i <= N; ++i )
		cin >>items[i].w >> items[i].d;
//F[i][j] = max( F[i-1][j-d(i)]+w[i], F[i-1][j])
//�߽磺
	for( int j = 0; j <= M; ++ j)
		if( items[1].w <= j )
			F[j] = items[1].d;
		else
			F[j] = 0;
	for( int i = 2; i <= N; ++ i ) {
		for( int j = M; j >= 0; -- j ) {
			if( items[i].w <= j ) 
				F[j] = max(F[j],F[j-items[i].w] + items[i].d);
		} 
	}
	cout << F[M]<< endl;
	return 0;
}

