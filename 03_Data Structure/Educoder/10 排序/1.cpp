#include "stdio.h"
#include "stdlib.h"
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define YES 1
#define NO 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int status;
typedef int KeyType;
typedef struct {
    KeyType  key;
    char others[20];
} TElemType; //二叉树结点类型定义
typedef struct BiTNode{  //二叉链表结点的定义
	TElemType  data;
	struct BiTNode *lchild,*rchild;
} BiTNode, *BiTree;
void sort(int a[],int n,int k);
int main()
{
int a[100], n, k,i;
scanf("%d%d",&n,&k);
for(i=0;i<n;i++)
    scanf("%d",&a[i]);
sort(a,n,k);
for(i=0;i<n;i++)
    printf("%d ",a[i]);

}
void sort(int a[],int n,int k)
{
    int count[k+1]={0};
    for(int i=0;i<n;i++) count[a[i]]++;
    int index=0;
    for (int i=0;i<k+1;i++)
	{
        while(count[i]>0)
		{
            a[index++]=i;
            count[i]--;
        }
    }
}
