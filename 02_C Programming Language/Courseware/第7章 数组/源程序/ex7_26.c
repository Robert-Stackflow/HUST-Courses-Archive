#include "stdio.h"
int BinarySearch(int a[],int x,int n);
int main(void)
{
	int x[]={1,3,5,7,9,11,13,15,17,19},index;
	index=BinarySearch(x,11,10);/*���ö��ֲ��Һ���*/
	if(index!=-1)
		printf("find %d!\n",x[index]);
	else
		printf("not find!\n");
	return 0;
}
int BinarySearch(int a[],int x,int n)/*������ֲ��Һ���*/
{	int front=0,back=n-1,middle;
	while(front<=back) {
		middle=(front+back)/2;   /* �����м䵥Ԫ���±� */
		if(x<a[middle])
			back=middle-1;	/* �޸�ǰ�벿�ֵ����Ԫ�ص��±�Ϊmiddle-1*/
		else if(x>a[middle])
			front=middle+1; /* �޸ĺ�벿�ֵ���ǰ��Ԫ�ص��±�Ϊmiddle+1 */
		else
			return (middle); /* �ҵ������ظ������ڵ�Ԫ���±� */
	}
	return -1;               /* û���ҵ�������-1 */
}
