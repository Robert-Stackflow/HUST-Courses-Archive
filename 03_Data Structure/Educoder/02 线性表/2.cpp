#include <stdio.h>
#include <stdlib.h>
typedef int ElemType;
typedef  struct  Dnode
{
    ElemType     data;
    struct  Dnode *prior,*next;
} *DuLinkList;
void adjust(DuLinkList L);
int main()
{
    DuLinkList L,p,tail;
    int n,i;
    L=tail=(DuLinkList)malloc(sizeof(struct Dnode));
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    {
        p=(DuLinkList)malloc(sizeof(struct Dnode));
        scanf("%d",&p->data);
        tail->next=p;
        p->prior=tail;
        tail=p;
    }
    L->prior=tail;
    tail->next=L;
    adjust(L);
    p=L->next;
    while(p!=L)
    {
        printf(" %d",p->data);
        p=p->next;
    }
}
void adjust(DuLinkList L)
{
	if(L->next!=L->prior)
	{
	DuLinkList p=L->next,q=L->next->next,tail=L->prior,op=L;
	while(q<=tail)
	{
	if(q==tail) break;
	p->next=q->next;
	q->next->prior=p;
	op->prior=q;
	q->next=op;
	op=q;
	if(p->next==tail) break;
	q=p->next->next;
	p=p->next;
	}
	op->prior=tail;
	tail->next=op;
	}
}
