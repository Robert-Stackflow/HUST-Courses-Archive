#include<stdio.h>
#include<stdlib.h>
#define LIST_INIT_SIZE 20
#define LISTINCREMENT 10
typedef int ElemType;
typedef struct
{ 	ElemType *elem;
    int length;
    int listsize;
}SqList;
int insert(SqList &L,ElemType x);
int main()
{
    SqList L;
    ElemType x;
    int i;
    L.elem=(ElemType *)malloc(sizeof(ElemType)*LIST_INIT_SIZE);
    L.length=0;
    L.listsize=LIST_INIT_SIZE;
    scanf("%d",&x);
    while (x)
    {
        L.elem[L.length++]=x;
        scanf("%d",&x);
    }
    scanf("%d",&x);
    insert(L,x);
    for(i=0;i<L.length;i++)
        printf("%8d",L.elem[i]);
    if (L.length>L.listsize) printf("\n程序未处理溢出");
	return 0;
}
int insert(SqList &L,ElemType x)
{
	ElemType *newbase;
	if(L.length==0){L.elem[0]=x;L.length++;return 1;}
	if(L.length>=L.listsize)
	{
		newbase=(ElemType *)realloc(L.elem,(L.listsize+LISTINCREMENT)*sizeof(ElemType));
		if(!newbase) return -2;
		L.elem=newbase;
		L.listsize+=LISTINCREMENT;
	}
	int i=0;
	ElemType *p=&(L.elem[L.length-1]),*q=&(L.elem[i]);
	for(;x>*q;i++){q=&(L.elem[i]);}
	for(;p>=q;--p){*(p+1)=*p;}
	*q=x;
	L.length++;
	return 1;
}

