#include<stdio.h>
#include<stdlib.h>
typedef int ElemType;
typedef struct node
{ 	ElemType data;
	struct node *next;
}NODE,*LinkList;
void TriLinkList(LinkList A,LinkList B,LinkList C);
int main()
{
    LinkList L[3],p;
    ElemType x;
    int i;
    for(i=0;i<3;i++)
    {
    	L[i]=p=(NODE *)malloc(sizeof(NODE));
    	scanf("%d",&x);
    	while (x)
    	{
				p->next=(NODE *)malloc(sizeof(NODE));
				p=p->next;
				p->data=x;
				scanf("%d",&x);
    	}
      p->next=NULL;
    }
    TriLinkList(L[0],L[1],L[2]);
    for(p=L[0]->next;p;p=p->next)
        printf(" %d",p->data);
	return 0;
}
void TriLinkList(LinkList A,LinkList B,LinkList C)
{
	LinkList pa=A->next,pb=B->next,pc=C->next,prior=A;
    while(pa!=NULL&&pb!=NULL&&pc!=NULL)
    {
        while(pb!=NULL&&pc!=NULL&&pb->data!=pc->data)
        {
            if(pb->data<pc->data) pb=pb->next;
            else pc=pc->next;
        }
        if(pb!=NULL&&pc!=NULL&&pb->data==pc->data)
        {
        while(pa!=NULL&&pa->data<pb->data)
		{
		prior=pa;
		pa=pa->next;
		}
        if(pa!=NULL&&pa->data==pb->data)
        {
        prior->next=pa->next;
        pa=prior->next;
        }
        pb=pb->next;
        pc=pc->next;
		}
	}
}
