#include "stdio.h"
#define N 3
struct GOODS {
	    long code;               /* 货物编码 */
	    char name[20];           /* 名称 */
	    float price;             /* 价格 */
};
void input(struct GOODS *p,int n);
void sort(struct GOODS *p,int n);
void display(struct GOODS *p,int n);
int main(void)
{	struct GOODS meat[N];
	input(meat,N);         /* 结构数组名作为实参 */
	display(&meat[0],N);   /* 结构数组打头元素的地址作为实参 */
	sort(meat,N);
	display(meat,N);
	return 0;
}
void input(struct GOODS *p,int n)  /* 输入结构数组各元素的成员的值 */
{	int i;
	float tmp;
	for(i=0;i<n;i++){
		scanf("%ld",&p[i].code);
		scanf("%s",(p+i)->name);
		scanf("%f",&tmp);
		(*(p+i)).price=tmp;
	}
}
void sort(struct GOODS *p,int n)   /* 对价格排序 */
{	int i,j;
	struct GOODS t;
	for(i=0;i<n-1;i++)
		for(j=i+1;j<n;j++)
			if((p+i)->price<(p+j)->price){
				t=*(p+i); *(p+i)=*(p+j); *(p+j)=t;
			}
}
void display(struct GOODS *p,int n)  /* 显示结构数组元素的成员的值 */
{	int i;
	for(i=0;i<n;i++){
		printf("%ld\t",(*(p+i)).code);
		printf("%s\t",(p+i)->name);
		printf("%f\n",p[i].price);
	}
}