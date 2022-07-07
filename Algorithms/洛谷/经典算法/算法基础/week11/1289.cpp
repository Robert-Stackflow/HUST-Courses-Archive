//blg1289 by guo wei  Tian Ji -- The Horse Racing ̰�� 


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

/*��һ������1)��Ϊ����������һ���죬������
	2) ���������ͬʱ����Ϊ������������һ���죬������ ****����ʵ����Ӧ����������ȥ�ͶԷ������ȡ���������������ȫ��ͬ����� 
	3)  û���ǵ����ʣ��������һ�������� 
	5)  ����������ʱ����Ϊ�Լ���β��һ���ȶԷ���ͷ����

����Ĺؼ��ǣ�ͷ��һ���죬��β��Ҳһ���죬�����Լ�β��ԶԷ�ͷ��֤�����滻����

�������ŷ�������β��ҵ�������������µ�����������棬�Է���ͷ��a���Ե����ҵ���x

��ô�ҿ���ά�������Ծֲ��䣬���ҵ�β�� z��a, x�ԶԷ���β��b  (z=b)

��a>x  ����任��a����Ӯ�ģ����ҷ�ԭ�������x >= b���任��Ľ���������
��a=x,  ��任�� a��z, x ��b��
    ��a>z,�� x > b (��z=x) �����ǳ�ƽ��û�б�ø���
    ��a = z����x=b,���ǳ�ƽ��Ҳû�б�ø��� 


	