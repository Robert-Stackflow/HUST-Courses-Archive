#include<stdio.h>
#include<string.h>
//����֮��������ת��Ϊ�ַ����������У����˷����ڹ�������ݲ��Ѻ�
//--�д�����-- 
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
//����֮����ÿһ���� 
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
//����֮������ѧ����
int main(){
    int n,x,m=1,ans=0;
    scanf("%d%d",&n,&x);
    while(m<=n){
        int a=n/(m*10),b=n/m%10,c=n%m; //a,b,cΪn�������֣�����һλx�ĸ�����b��Ϊ��һλ����aΪb��ߵ�����cΪb�ұߵ���������1~728��ʮλ7�ĸ�������a=7��b=2��c=8
        if(x){
            if(b>x) ans+=(a+1)*m; //���b>x��˵����(a+1)*m��x������1~728�и�λ7�ĸ�������Ϊ��72+1��*1=73��
            if(b==x) ans+=a*m+c+1; //���b=x��˵����a*m+c+1��x������1~728�а�λ7�ĸ�������Ϊ0*100+28+1=29��
            if(b<x) ans+=a*m; //���b<x��˵����a*m��x������1~728��ʮλ7�ĸ�������Ϊ7*10����
        }
        else{ //x=0�������x��=0�����������ͬ
            if(b) ans+=a*m;
            else ans+=(a-1)*m+c+1;
        }
        m*=10;
    }
    printf("%d\n",ans);
    return 0;
}
//����������һ����C++�㷨�⺯���Ľⷨ
//#include <bits/stdc++.h>
//using namespace std;
//int main() {
//   int n, x;
//   cin >> n >> x;
//   stringstream ss;
//   for (n++; --n; ss << n);     //��1-n��ֵ����ŵ��ַ�������
//   string s = ss.str();
//   cout << count(s.begin(), s.end(), x + '0') << endl;    //����count����ֱ�ӳ��������򵥵�
//} 
