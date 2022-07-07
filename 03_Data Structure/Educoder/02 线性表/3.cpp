#include<stdio.h>
#include<stdlib.h>
#define LIST_INIT_SIZE 5000
#define LISTINCREMENT 10
typedef int ElemType;
typedef struct
{ 	ElemType *elem;
    int length;
	int listsize;
}SqList;
int TriSqList(SqList &A,SqList B,SqList C);
int main()
{
    SqList L[3];
    ElemType x;
    int i;
    for(i=0;i<3;i++)
    {
    	L[i].elem=(ElemType *)malloc(sizeof(ElemType)*LIST_INIT_SIZE);
    	L[i].length=0;
    	L[i].listsize=LIST_INIT_SIZE;
    	scanf("%d",&x);
    	while (x)
    	{
        	L[i].elem[L[i].length++]=x;
        	scanf("%d",&x);
    	}
    }
    TriSqList(L[0],L[1],L[2]);
    for(i=0;i<L[0].length;i++)
        printf(" %d",L[0].elem[i]);
	return 0;
}
int TriSqList(SqList &A,SqList B,SqList C)
{
    int pa=0,pb=0,pc=0,i;
    while(pa<A.length&&pb<B.length&&pc<C.length)
    {
        while(pb<B.length&&pc<C.length&&B.elem[pb]!=C.elem[pc])
        {
            if(B.elem[pb]<C.elem[pc]) pb++;
            else pc++;
        }
        if(B.elem[pb]==C.elem[pc])
        {
        while(pa<A.length&&A.elem[pa]<B.elem[pb]) pa++;
        if(pa<A.length&&A.elem[pa]==B.elem[pb])
        {
        for(i=pa;i<A.length-1;++i) A.elem[i]=A.elem[i+1];
        A.length--;
        }
        else
        {
            pb++;
            pc++;
        }
		}
	}
}

