#include<stdio.h>
int DaffodilNumber (int x) 
{
	int j,i,k;
		j=x/100;
		i=(x-j*100)/10;
		k=x%10;
		if (x==j*j*j+i*i*i+k*k*k)
			return 1;
		else return 0;
}
int main(void)
{
	int Num;
	printf("请输入一个三位数：");
	scanf("%d",&Num);
	if(DaffodilNumber (Num))
		printf("这是一个水仙花数！");
	else
		printf("这不是一个水仙花数！"); 
	return 0;
} 
