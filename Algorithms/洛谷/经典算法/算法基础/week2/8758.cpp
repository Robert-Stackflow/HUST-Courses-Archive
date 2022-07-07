#include <iostream>
using namespace std;

int pos[32];
//8758
inline int GetBit(int n,int i)
{
	return (n >> i ) & 1;
}
void Print(int n) {
	bool first = true;
	for(int i = 15; i >= 0; --i) {
		
		if( GetBit(n,i)) {
			if(! first ) {
				cout << "+" ;
			}
			else 
				first = false;
			if( i == 0)
				cout << "2(0)" ;
			else if( i == 1)
			 	cout << "2";
			else {
				cout << "2(";
				Print(i);
				cout << ")";
			}
		}
	}
}
int main()
{
	int n;
	cin >> n; 
	Print(n);
	
	return 0;
}
