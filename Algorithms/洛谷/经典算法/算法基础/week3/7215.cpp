#include <iostream>
using namespace std;
int ways(int n,int i)
{
	if( n == 0)
		return 1;
	if( i == 0)
		return 0;
	if( i <= n)
		return ways(n-i,i) + ways(n,i-1);  //��i�Ͳ���i�������i�����ظ�ʹ��
	else
		return ways(n,i-1);	
	
}
int main()
{
	int n;
	while(cin >> n) 
		cout << ways(n,n) << endl;
}
