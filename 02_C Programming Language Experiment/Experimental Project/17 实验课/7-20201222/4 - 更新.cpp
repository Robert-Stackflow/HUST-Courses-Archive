#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct s_list
{
	char c;
	struct s_list *next;
}list; 
void AddToTail(list **pHead,char m);
char position(list **pHead,int n);
int main(void)
{
	list *head=NULL,*p;
	char c='a';
	char mid;
	int flag=1,count=0;
	p=head;
	while(c!='\n'&&c!='\0'&&c!=EOF) 
	{
		if((mid=getchar())=='\n') break;
		c=mid;
		AddToTail(&head,c);
	}
	p=head;
	while(p){
		printf("%c",p->c);
		p=p->next;
	}
	printf("\n");
	p=head;
	while(p) {count++;p=p->next;}
	for(int i=0;i<(count/2);i++)
	{
		if(position(&head,i+1)==position(&head,count-i)) continue;
		else {
			flag=0;
			break;
		}
	}
	if(flag) printf("true");
	else printf("false");
	return 0;
}

void AddToTail(list **pHead,char m)//在已有链表尾节点后添加新节点 
{
	list *pNew=(list *)malloc(sizeof(list));
	list *loc_head=*pHead;
	pNew->c=m;
	pNew->next=NULL;
	if(*pHead==NULL)
		*pHead=pNew;
	else
	{
		list *loc_head=*pHead;
		while(loc_head->next)
			loc_head=loc_head->next;
		loc_head->next=pNew;
	}
}

char position(list **pHead,int n)
{
	list *p=*pHead;
	int count1=0;
	while(p)
	{
		count1++;
		if(count1==n) return p->c;
		p=p->next;
	}
}
