//By Guo Wei
#include <iostream>
#include <string>
#include <cstring>
using namespace std;
struct BigInt
{

	int num[110];
	int len;
	BigInt operator+(const BigInt & n) { //����+��ʹ�� a + b�� a,b���� BigInt������ʱ���ܳ���
		int ml = max(len,n.len);
		int carry = 0; //��λ 
		BigInt result;
		for(int i = 0;i < ml; ++i) {
			result.num[i] = num[i] + n.num[i] + carry;
			if( result.num[i] >= 10) 	{
				carry = 1;
				result.num[i] -= 10;
			}
			else
				carry = 0;
		}
		if ( carry == 1) {
			result.len = ml + 1;
			result.num[ml] = 1;
		}
		else 
			result.len = ml;
		return result;
	}
	bool operator<(const BigInt & n) {
		if( len > n.len )
			return false;
		else if( len < n.len)
			return true;
		else {
			for(int i = len -1; i >= 0; -- i) {
				if( num[i] < n.num[i])
					return true;
				else if( num[i] > n.num[i])
					return false;
			}
			return false;
		}
	}
	BigInt() {
		len = 1;
		memset(num,0,sizeof(num));
	}
	BigInt(const char * n,int L) { //�ɳ���ΪL��char���鹹���������n�����Ԫ��ȡֵ��Χ�� 1-9�� 
		memset(num,0,sizeof(num));
		len = L;
		for(int i = 0; n[i]; ++i)
			num[len-i-1] = n[i] - '0';
	}
};
ostream & operator <<(ostream & o,const BigInt & n) 
{
	
	for(int i = n.len - 1;i >= 0; --i)
		o << n.num[i];
	return o;
}
const int MAXN  = 60;
char a[MAXN];
BigInt Num[MAXN][MAXN];//Num[i][j]��ʾ�ӵ�i�����ֵ���j�����������ɵ����� 
BigInt V[MAXN][MAXN]; //V[i][j]��ʾi���Ӻŷŵ�ǰj�������м䣬���ܵõ�����ѱ��ʽ��ֵ�� 
int main()
{
	int m,n;
	BigInt inf; //����� 
	inf.num[MAXN-2] = 1;
	inf.len = MAXN-1;

	while(cin >> m ) {
		cin >> a+1;
		n = strlen(a+1);
		for(int i = 1;i <= n; ++i) 
			for(int j = i;j<= n; ++j) {
				Num[i][j] = BigInt(a+i,j-i+1);  
			}
		for(int j = 1; j <= n; ++j)  {
			V[0][j] = BigInt(a+1,j);
		}
		
		for(int i = 1;i <= m; ++i) {
			for(int j = 1; j <= n; ++j) {
				if( j - 1 < i) 
					V[i][j] = inf;
				else {
					BigInt tmpMin = inf;
					for(int k = i; k < j; ++k) {
						BigInt tmp = V[i-1][k] + Num[k+1][j]; 
						if (tmp < tmpMin)
							tmpMin = tmp;
					}
					V[i][j] = tmpMin;
				}
			}
		}
		cout << V[m][n] << endl;
	}
	return 0;
}

