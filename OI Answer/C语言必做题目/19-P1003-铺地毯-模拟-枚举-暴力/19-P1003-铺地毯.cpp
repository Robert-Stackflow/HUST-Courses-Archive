#include<stdio.h>
typedef struct area{
	int a,b,x,y;
}list;
int main(void)
{
	int i,n,check[2],count=-1;
	list s[10001];
	scanf("%d",&n);
	for(i=0;i<n;i++)
		scanf("%d%d%d%d",&s[i].a,&s[i].b,&s[i].x,&s[i].y);
	//�������½������볤�Ϳ� 
	scanf("%d%d",&check[0],&check[1]);
	for(i=0;i<n;i++)
		if((check[0]<=(s[i].a+s[i].x)&&check[0]>=s[i].a)&&(check[1]<=(s[i].b+s[i].y)&&check[1]>=s[i].b)) count=i+1;
		//�жϵ�ǰ���Ƿ��ڸõ�̺��Χ�� 
	printf("%d",count);
}

