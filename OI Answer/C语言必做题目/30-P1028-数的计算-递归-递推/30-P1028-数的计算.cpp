#include<stdio.h>
#include<math.h>
#define N 10001
int n,step[N];
int main(void)
{
	scanf("%d",&n);
	for(int i=0;i<n;i++){
        for(int j=0;j<i/2.0;j++)
            step[i]+=step[j];
        step[i]++;
    }
    printf("%d",step[n-1]);
}
