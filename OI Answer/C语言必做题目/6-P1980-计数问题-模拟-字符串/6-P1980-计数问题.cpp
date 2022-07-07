#include<stdio.h>
#include<string.h>
//正解之将所有数转化为字符存入数组中，但此法对于过大的数据不友好
//--尚待修正-- 
int itoa_new(int i,int mid,int 10) 
int main(void)
{
	int n,x,count=0;
	char mid[7];
	scanf("%d%d",&n,&x);
	for(int i=1;i<=n;i++)
	{
	itoa_new(i,mid,10);
	for(int i=0;i<=strlen(mid);i++)
		if(mid[i]==x+'0') ++count;
	}	
	printf("%d",count);
}
//正解之遍历每一个数 
int main()
{
	int n,x,mid,count=0;
	scanf("%d%d",&n,&x);
	for(int i=1;i<=n;i++)
	{
		int j=i;
		while(j!=0)
		{
			mid=j%10;j/=10;
			if(mid==x) count++;
		}
	}
	printf("%d",count);
	return 0;
}
//正解之利用数学方法
int main(){
    int n,x,m=1,ans=0;
    scanf("%d%d",&n,&x);
    while(m<=n){
        int a=n/(m*10),b=n/m%10,c=n%m; //a,b,c为n的三部分，求哪一位x的个数，b就为那一位数，a为b左边的数，c为b右边的数，如求1~728中十位7的个数，则a=7，b=2，c=8
        if(x){
            if(b>x) ans+=(a+1)*m; //如果b>x，说明有(a+1)*m个x（如求1~728中个位7的个数，则为（72+1）*1=73）
            if(b==x) ans+=a*m+c+1; //如果b=x，说明有a*m+c+1个x（如求1~728中百位7的个数，则为0*100+28+1=29）
            if(b<x) ans+=a*m; //如果b<x，说明有a*m个x（如求1~728中十位7的个数，则为7*10个）
        }
        else{ //x=0的情况和x！=0的情况有所不同
            if(b) ans+=a*m;
            else ans+=(a-1)*m+c+1;
        }
        m*=10;
    }
    printf("%d\n",ans);
    return 0;
}
//以下是正解一利用C++算法库函数的解法
//#include <bits/stdc++.h>
//using namespace std;
//int main() {
//   int n, x;
//   cin >> n >> x;
//   stringstream ss;
//   for (n++; --n; ss << n);     //把1-n的值都存放到字符串流中
//   string s = ss.str();
//   cout << count(s.begin(), s.end(), x + '0') << endl;    //运用count函数直接出结果，简简单单
//} 
