#include<stdio.h>
#include<stdlib.h>
typedef struct s{
	int height;
	int force;
	struct s *next;
}list;
void create(list **headp,int number);
void sort(list *head);
int main(void)
{
	int n,s,a,b,hm,max,ans=0;
	scanf("%d%d%d%d",&n,&s,&a,&b);
	hm=a+b;
	list*head=NULL;
	create(&head,n);
	sort(head);
	list*p=head;
	while(p)
	{
		if(s<=0) break;
		if(p->height<=hm&&((s-(p->force))>=0)) {s-=p->force;++ans;} 
		p=p->next;
	}
	printf("%d",ans);
}
void create(list **headp,int number)
{	list *loc_head=NULL,*tail;
	int height0,force0;
	scanf("%d%d",&height0,&force0);
	loc_head=(list*)malloc(sizeof(list));
	loc_head->force=force0;
	loc_head->height=height0;
		tail=loc_head; 
		for(int i=1;i<number;i++){
			scanf("%d%d",&height0,&force0);
			tail->next=(list*)malloc(sizeof(list));
			tail=tail->next;
			tail->force=force0;
			tail->height=height0;
		}
		tail->next=NULL; 
	*headp=loc_head; 
}

void sort(list *head)
{	list *p1=head,*p2;
	int len=0,i,j,t;
	while(p1){len++; p1=p1->next;}
	for(i=0,p1=head;i<len-1;i++,p1=p1->next)
		for(j=i+1,p2=p1->next;j<len;j++,p2=p2->next)
		{
			if((p1->force>p2->force)||((p1->force==p2->force)&&(p1->height>p2->height)))
			{
				t=p1->force; p1->force=p2->force; p2->force=t;
				t=p1->height;p1->height=p2->height;p2->height=t;
		}
		}
}
