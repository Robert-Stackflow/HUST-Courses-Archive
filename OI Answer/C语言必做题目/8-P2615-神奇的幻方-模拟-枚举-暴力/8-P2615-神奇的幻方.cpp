#include<stdio.h>
//下面的方法纯粹套用公式，按公式直接码即可 
int main(void)
{
	int N,a[40][40]={0},P,Q;
	scanf("%d",&N);
	a[0][N/2]=1;
	P=0,Q=N/2;
	for(int i=2;i<=N*N;i++)
	{
		if(P==0&&Q!=N-1) {a[N-1][Q+1]=i;P=N-1,Q=Q+1;}
		else if(P!=0&&Q==N-1) {a[P-1][0]=i;P=P-1;Q=0;}
		else if(P==0&&Q==N-1) {a[P+1][Q]=i;P=P+1;Q=Q;}
		else
		{
			if(a[P-1][Q+1]==0) {a[P-1][Q+1]=i;P=P-1;Q=Q+1;}
			else {a[P+1][Q]=i;P=P+1;Q=Q;}
		}
	}
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)printf("%d ",a[i][j]);
		printf("\n");
	}
	return 0;
}

//下面的是利用数学计算的完美做法 
int n,a[40][40],x,y;
int main(){
	scanf("%d",&n);
	x=1,y=(n+1)/2;
	for(int i=1;i<=n*n;i++){
		a[x][y]=i;
		if(!a[(x-2+n)%n+1][y%n+1]) x=(x-2+n)%n+1,y=y%n+1;
		else x=x%n+1;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			printf("%d ",a[i][j]);
		}
		printf("\n");
	}
} 
