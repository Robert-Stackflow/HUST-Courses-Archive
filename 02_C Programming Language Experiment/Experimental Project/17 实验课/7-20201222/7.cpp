#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*样例输入
1
4 
U202012345 Jack 99 100 80 96   
U202054321 Rose 89 94 85 100
U202056789 Tom 12 34 56 78
U202098765 Jerry 98 76 54 32
2
3
U202054321 1 66
4
5
*/
/*1 1 U123456789 Elio 34 56 78 90 2 3 U123456789 2 99 1 3 U987654321 Gray 0 0 0 0 
U000000000 Black 100 100 100 100 U202073456 Red 45 34 67 99 5*/
typedef struct s_list
{
	char num[20];
	char name[10];
	int score[4];
	int sum;
	float average;
	struct s_list *next;
}list; 
void create_list(list **headp,int number);
void AddToTail(list ** pHead);
void sort_lists(list **headp,int number); 
int main(void)
{
	list *head=NULL,*p,*before;
	int number,flag=1,check_count=0,check_new,count=1;
	char check_num[20];
	while(flag!=5)
{
	scanf("%d",&flag);
	if(flag==1)
	{
	scanf("%d",&number);
	if(count!=1)
	{
	for(int i=0;i<number;i++)
		AddToTail(&head);	
	}
	else	create_list(&head,number);
	p=head;
	while(p)
		{
			p->sum=p->score[0]+p->score[1]+p->score[2]+p->score[3];
			p->average=(float)((p->sum)/4.0);
			p=p->next;		
		}
    sort_lists(&head,number);//传递头指针的地址和输入数据的个数 
	count++;
	}
	if(flag==2)
	{
        p=head;
		while(p){
		printf("%s %s ",p->num,p->name);
		for(int i=0;i<4;i++)
		{
			printf("%d",p->score[i]);
			if(i<3)	printf(" ");
		}
		printf("\n"); 
		p=p->next;
	}
	} 
	if(flag==3)
	{
		scanf("%s%d%d",check_num,&check_count,&check_new);
		p=head;
		while(p)
		{ 
		if(strcmp(p->num,check_num)==0)
		{
			p->score[check_count-1]=check_new;
			break;
		}
		else p=p->next;
		}
		p=head;
		while(p)
		{
			p->sum=p->score[0]+p->score[1]+p->score[2]+p->score[3];
			p->average=(float)((p->sum)/4.0);
			p=p->next;			
		}
	}
	if(flag==4)
	{
		p=head;
		while(p)
		printf("%s %s %.2f\n",p->num,p->name,p->average),p=p->next;	
	}
	if(flag==5)
	{
		p=head;
		while(p)
			printf("%s %s %d %.2f\n",p->num,p->name,p->sum,p->average),p=p->next;
		return 0;	
	}
}		
}

void create_list(list **headp,int number)
{	list *loc_head=NULL,*tail;
	char num0[20];
	char name0[10];
	int score0[4];//English,math,physics,C 
	scanf("%s%s%d%d%d%d",num0,name0,&score0[0],&score0[1],&score0[2],&score0[3]);
		loc_head=(list *)malloc(sizeof(struct s_list));
		strcpy(loc_head->num,num0);
		strcpy(loc_head->name,name0);
		for(int i=0;i<4;i++)
			loc_head->score[i]=score0[i];
		tail=loc_head; 
		for(int i=1;i<number;i++){
			scanf("%s%s%d%d%d%d",num0,name0,&score0[0],&score0[1],&score0[2],&score0[3]);
			tail->next=(list *)malloc(sizeof(struct s_list));
			tail=tail->next; 
			strcpy(tail->num,num0);
			strcpy(tail->name,name0);
			for(int i=0;i<4;i++)
			tail->score[i]=score0[i];
		}
		tail->next=NULL; 
	*headp=loc_head; 
}


void AddToTail(list **pHead)
{
	list * pNew=(list *)malloc(sizeof(struct s_list));
	char num0[20];
	char name0[10];
	int score0[4];//English,math,physics,C 
	scanf("%s%s%d%d%d%d",num0,name0,&score0[0],&score0[1],&score0[2],&score0[3]);
	strcpy(pNew->num,num0);
			strcpy(pNew->name,name0);
	for(int i=0;i<4;i++)
			pNew->score[i]=score0[i];
	pNew->next=NULL;
	if(*pHead==NULL)
		*pHead=pNew;
	else
	{
		list *pNode=*pHead;
		while(pNode->next != NULL)
			pNode=pNode->next;
		pNode->next=pNew;
	}
}

void sort_lists(list **headp,int number)
{	struct s_list *prior1,*prior2,*p1,*p2,*t;
	int i=0;
	p1=*headp;//此处用先单独处理链头的方法交换指针域 
	if(number==1) return;//当仅有一个输入信息时，无需排序，结束函数 
	else
	{
	for(p2=p1->next,prior2=p1;p2!=NULL;prior2=p2,p2=p2->next)
		if(p1->sum>p2->sum){
			prior2->next=p1; t=p1->next;
			p1->next=p2->next; (*headp)=p2;
			p2->next=t; p1=p2;
		}
	for(prior1=*headp,p1=prior1->next;p1->next!=NULL;prior1=p1,p1=p1->next)
		for(p2=p1->next,prior2=p1;p2!=NULL;prior2=p2,p2=p2->next)
			if(p1->sum>p2->sum){
				t=p2->next; prior1->next=p2;
				prior2->next=p1; p2->next=p1->next;
				p1->next=t; p1=p2;
	}	
	}
	
}
