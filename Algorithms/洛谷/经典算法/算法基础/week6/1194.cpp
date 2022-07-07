//By Guo Wei
#include <iostream>
#include <string>
#include <cstring>
using namespace std;
char a[300],b[300],c[700];
int La,Lb,Lc;
char valid[210][210][410];
bool Valid(int as,int bs,int cs)
{	
	if( cs == Lc  ) {
		if( as == La && bs == Lb)
			return true;
		else
			return false;
	}
	if( valid[as][bs][cs] != -1 )
		return valid[as][bs][cs];
	bool b1 = false,b2 = false;
	if( a[as] == c[cs])
		b1 = Valid(as+1,bs,cs+1);
	if( b[bs] == c[cs])
		b2 = Valid(as,bs+1,cs+1);
	valid[as][bs][cs] = 	b1 || b2;
	return b1 || b2;
	
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i = 0;i < n; ++i) {
		scanf("%s%s%s",a,b,c);
		La = strlen(a);
		Lb = strlen(b);
		Lc = strlen(c);
		//memset(valid,0xff,sizeof(valid));  //不能用这个，用这个就是 n^3的了 
		for(int cs = 0; cs <= Lc; ++cs)
			for(int as = 0; as <= La; ++ as) {
				int bs = cs - as; //因为bs必须是 cs-as才有意义，所以不用让bs从0走到Lb，要是那样就搞成n^3的了 
				valid[as][bs][cs] = -1;
			}
		if(Valid(0,0,0))
			printf("Data set %d: yes\n",i+1);
		else	
			printf("Data set %d: no\n",i+1);
	}
	return 0;
}