#include<stdio.h>
#include<stdlib.h>
/*
7 3
1000 90
3239 88
2390 95
7231 84
1005 95
1001 88
1006 88
*/
typedef struct score{
	int num;
	int score;
	struct score *next;
}list;
void create_list(list **headp,int number);
void sort_lists(list *head);
int main(void)
{
	int n,m,shall,should,count=1,limit;
	list*head=NULL;
	scanf("%d%d",&n,&m);
	create_list(&head,n);
	shall=m*1.5;
	sort_lists(head);
	list*p=head;
	printf("\n------------------------\n");
	while(p)
	{
		printf("%d %d\n",p->num,p->score);
		p=p->next;
	}
	printf("\n------------------------\n");
	p=head;
	while(p)
	{
		if(count>shall) break;
		limit=p->score;
		p=p->next;
		count++;
	}
	count=0;
	while(p)
	{
		if(p->score==limit) count++;
		else break;
		p=p->next;
	}
	should=shall+count;
	printf("%d %d\n",limit,should);
	p=head;
	count=1;
	while(p)
	{
		if(count>should) break;
		printf("%d %d\n",p->num,p->score);
		p=p->next;
		count++;
	}
}
void create_list(list **headp,int number)
{	list *loc_head=NULL,*tail;
	int score0,num0;
	scanf("%d%d",&num0,&score0);
	loc_head=(list*)malloc(sizeof(list));
	loc_head->score=score0;
	loc_head->num=num0;
		tail=loc_head; 
		for(int i=1;i<number;i++){
			scanf("%d%d",&num0,&score0);
			tail->next=(list*)malloc(sizeof(list));
			tail=tail->next;
			tail->score=score0;
			tail->num=num0;
		}
		tail->next=NULL; 
	*headp=loc_head; 
}

void sort_lists(list *head)
{	list *p1=head,*p2;
	int len=0,i,j,t;
	while(p1){len++; p1=p1->next;}
	for(i=0,p1=head;i<len-1;i++,p1=p1->next)
		for(j=i+1,p2=p1->next;j<len;j++,p2=p2->next)
		{
			if((p1->score<p2->score)||((p1->score==p2->score)&&(p1->num>p2->num)))
			{
				t=p1->score; p1->score=p2->score; p2->score=t;
				t=p1->num;p1->num=p2->num;p2->num=t;
		}
		}
}
