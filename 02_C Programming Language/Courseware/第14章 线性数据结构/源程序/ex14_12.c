#include "stdio.h"
#include "stdlib.h"
struct s_list{ 
	int data; /* 数据域 */
	struct s_list *next; /* 指针域 */ 
} ;
void create_list_v1(struct s_list **headp,int *p);
/*采用选择法对链表排序*/
void sort_lists(struct s_list *head);
void sort_lists(struct s_list *head)
{	struct s_list *p1=head,*p2;
	int len=0,i,j,t;
	while(p1){ len++; p1=p1->next; }/* 计算链表的长度 */
	for(i=0,p1=head;i<len-1;i++,p1=p1->next)
		for(j=i+1,p2=p1->next;j<len;j++,p2=p2->next)
			if(p1->data > p2->data){
				t=p1->data; p1->data=p2->data; p2->data=t; /* 交换数据域 */
			}
}
/*采用冒泡法对链表排序*/
/*
for(i=0,p1=head;i<len-1;i++,p1=p1->next)
		for(j=0,p2=head;j<len-i-1;j++,p2=p2->next)
			if(p2->data>p2->next->data){//当前结点的数据值比后继结点数据值大
				t=p2->data; p2->data=p2->next->data; p2->next->data=t;//交换
			}
*/
int main(void)
{	struct s_list *head=NULL,*p;
	int s[]={11,21,3,12,51,16,7,2,0}; /* 0为结束标记 */
		create_list_v1(&head,s); /* 创建链表 */
		sort_lists(head); /* 链表排序 */
		p=head; /* 遍历指针指向链头 */
		while(p){ printf("%d\t",p->data); p=p->next; } /*遍历指针指向下一结点*/
		printf("\n"); return 0;
}

void create_list_v1(struct s_list **headp,int *p)
{	struct s_list * loc_head=NULL,*tail;
	if(p[0]==0) ;/* 相当于*p==0 */
	else { /* loc_head指向动态分配的第一个结点 */
		loc_head=(struct s_list *)malloc(sizeof(struct s_list));
		loc_head->data=*p++; /* 对数据域赋值 */
		tail=loc_head; /* tail指向第一个结点 */
		while(*p){ /* tail所指结点的指针域指向动态创建的结点 */
			tail->next=(struct s_list *)malloc(sizeof(struct s_list));
			tail=tail->next; /* tail指向新创建的结点 */
			tail->data=*p++; /* 向新创建的结点的数据域赋值 */
		}
		tail->next=NULL; /* 对指针域赋NULL值 */
	}
	*headp=loc_head; /* 使头指针headp指向新创建的链表 */
}
