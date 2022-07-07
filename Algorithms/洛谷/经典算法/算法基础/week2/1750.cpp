#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
using namespace std;
const int M = 8;
char str[M];
char permutation[M];
bool used[M] = {0};
int L = 0;
void Permutation(int n)
{	
	if( n == L ) {
		permutation[L] = 0;
		cout << permutation << endl;
		return ;
	}
	for(int i = 0;i < L; ++i) {
		if( !used[i]) {
			used[i] = true;
			permutation[n] = str[i];
			Permutation(n+1);
			used[i] = false;
		}
	}
}
int main()
{
	cin >> str;
	L = strlen(str);
	sort(str,str+L);
	Permutation(0);
	return 0;	
}