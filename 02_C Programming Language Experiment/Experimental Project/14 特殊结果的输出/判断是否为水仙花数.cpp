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
	printf("������һ����λ����");
	scanf("%d",&Num);
	if(DaffodilNumber (Num))
		printf("����һ��ˮ�ɻ�����");
	else
		printf("�ⲻ��һ��ˮ�ɻ�����"); 
	return 0;
} 
