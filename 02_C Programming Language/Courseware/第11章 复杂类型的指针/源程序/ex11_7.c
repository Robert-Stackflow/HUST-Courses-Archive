#include "stdio.h"
int a1(int);
int a2(int);
int main(void)/*fpa����2��Ԫ�صĺ���ָ�����飬ÿ��Ԫ��ָ��*/
{	int i,(*fpa[2])(int);/*�ĺ�����һ�������βΣ���������ֵ*/
	fpa[0]=a1;/*��1�����±�Ϊ0��Ԫ��ָ��a1����*/
	fpa[1]=a2;/*��2�����±�Ϊ1��Ԫ��ָ��a2����*/
	for(i=0;i<2;i++)
		printf("%d\n",fpa[i]((i+1)*5));/*���ε���fpa[0]��fpa[1]��ָ����*/
	return 0;
}
int a1(int x){
	printf("in function a1,x=%d\n",x);
	return 2*x;
}
int a2(int y){
	printf("in function a2,y=%d\n",y);
	return 2*y;
}
