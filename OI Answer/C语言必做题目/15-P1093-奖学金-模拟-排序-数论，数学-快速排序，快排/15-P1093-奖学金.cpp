#include<stdio.h>
#include<stdlib.h>
typedef struct score{
	int num;
	int score[3];
	int sum;
	struct score *next;
}list;
void create_list(list **headp,int number);
void sort_lists(list *head);
int main(void)
{
	list *head=NULL,*p;
	int n;
	scanf("%d",&n);
	create_list(&head,n);
	p=head;
	while(p)
	{
		p->sum=p->score[0]+p->score[1]+p->score[2];
		p=p->next;	
	}
	sort_lists(head);
	p=head;
	int count=0;
	while(p)
	{	
		if(count>4) break;
		printf("%d %d\n",p->num,p->sum );
		p=p->next ;
		count++;
	}
}

void create_list(list **headp,int number)
{	list *loc_head=NULL,*tail;
	int score0[3],k=1;
	scanf("%d%d%d",&score0[0],&score0[1],&score0[2]);
	loc_head=(list*)malloc(sizeof(list));
	for(int i=0;i<3;i++)	loc_head->score[i]=score0[i];
	loc_head->num=k++;
		tail=loc_head; 
		for(int i=1;i<number;i++){
			scanf("%d%d%d",&score0[0],&score0[1],&score0[2]);
			tail->next=(list*)malloc(sizeof(list));
			tail=tail->next;
			for(int i=0;i<3;i++)	tail->score[i]=score0[i];
			tail->num=k++;
		}
		tail->next=NULL; 
	*headp=loc_head; 
}

void sort_lists(list *head)
{	list *p1=head,*p2;
	int len=0,i,j;
	int t;
	while(p1){len++; p1=p1->next;}
	for(i=0,p1=head;i<len-1;i++,p1=p1->next)
		for(j=i+1,p2=p1->next;j<len;j++,p2=p2->next)
		{
			if(p1->sum<p2->sum)
			{
				t=p1->sum; p1->sum=p2->sum; p2->sum=t;
				t=p1->num;p1->num=p2->num;p2->num=t;
				for(int k=0;k<3;k++)
					t=p1->score[k],p1->score[k]=p2->score[k],p2->score[k]=t;
			}
			else if(p1->sum==p2->sum)
			{
				if(p1->score[0]<p2->score[0]||((p1->score[0]==p2->score[0])&&(p1->num>p2->num)))
				{
				t=p1->sum;p1->sum=p2->sum; p2->sum=t;
				t=p1->num;p1->num=p2->num;p2->num=t;
				for(int k=0;k<3;k++)
					t=p1->score[k],p1->score[k]=p2->score[k],p2->score[k]=t;
				}
			}
		} 	
}
