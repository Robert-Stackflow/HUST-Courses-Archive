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
typedef struct {
    int pos;
    TElemType data;
} DEF;
status JudgeBiTree(BiTree T);
status CreateBiTree(BiTree &T,DEF definition[])
{
    int i=0,j;
    static BiTNode *p[100];
    while (j=definition[i].pos)
    {
         p[j]=(BiTNode *)malloc(sizeof(BiTNode));
       p[j]->data=definition[i].data;
       p[j]->lchild=NULL;
       p[j]->rchild=NULL;
       if (j!=1)
            if (j%2)   p[j/2]->rchild=p[j];
           else      p[j/2]->lchild=p[j];
       i++;
    }
    T=p[1];
    return OK;
}
int main()
{
DEF definition[100];
BiTree T;
int ans,i=0;
do {
    scanf("%d%d%s",&definition[i].pos,&definition[i].data.key,definition[i].data.others);
} while (definition[i++].pos);
CreateBiTree(T,definition);
if (JudgeBiTree(T))
       printf("YES");
else    printf("NO");
return 1;
}
status JudgeBiTree(BiTree T)
{
	BiTNode *st[100];
	KeyType order[100];
    int top=0,count=0,j=0;
	do
	{
    while(T)
    {
	if(top==100) exit(OVERFLOW);
	st[top++]=T;
	T=T->lchild;
    }
    if (top)
    {
	T=st[--top];
    order[count++]=T->data.key;
    T=T->rchild;
    }
    }while(top||T);
    for(j=0;j<count;j++)
		for(int k=j+1;k<count;k++)
			if(order[k]<=order[j]) return 0;
	return 1;
}
