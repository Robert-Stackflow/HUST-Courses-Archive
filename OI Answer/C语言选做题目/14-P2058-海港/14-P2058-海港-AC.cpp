#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
int n,mid,ans=0,t,k;
typedef struct all
{
    int time,country;
}list;
int main(void)
{
	queue<all>q;
	cin>>n;
	int num[200005]={0};
	for(int i=1;i<=n;i++)
    {
        cin>>t>>k;
        for(int j=1;j<=k;j++)
        {
			cin>>mid;
			q.push(all({t,mid}));
            num[mid]++;
            if(num[mid]==1)ans++;
        }
        while(q.back().time>=q.front().time+86400)
        {
        	if(--num[q.front().country]==0)	ans--;
        	q.pop();
		}
		cout<<ans<<endl;
    }
    return 0;
}
