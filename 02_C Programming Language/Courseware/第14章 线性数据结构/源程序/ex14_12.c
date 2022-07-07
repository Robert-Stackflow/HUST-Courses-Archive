#include "stdio.h"
#include "stdlib.h"
struct s_list{ 
	int data; /* ������ */
	struct s_list *next; /* ָ���� */ 
} ;
void create_list_v1(struct s_list **headp,int *p);
/*����ѡ�񷨶���������*/
void sort_lists(struct s_list *head);
void sort_lists(struct s_list *head)
{	struct s_list *p1=head,*p2;
	int len=0,i,j,t;
	while(p1){ len++; p1=p1->next; }/* ��������ĳ��� */
	for(i=0,p1=head;i<len-1;i++,p1=p1->next)
		for(j=i+1,p2=p1->next;j<len;j++,p2=p2->next)
			if(p1->data > p2->data){
				t=p1->data; p1->data=p2->data; p2->data=t; /* ���������� */
			}
}
/*����ð�ݷ�����������*/
/*
for(i=0,p1=head;i<len-1;i++,p1=p1->next)
		for(j=0,p2=head;j<len-i-1;j++,p2=p2->next)
			if(p2->data>p2->next->data){//��ǰ��������ֵ�Ⱥ�̽������ֵ��
				t=p2->data; p2->data=p2->next->data; p2->next->data=t;//����
			}
*/
int main(void)
{	struct s_list *head=NULL,*p;
	int s[]={11,21,3,12,51,16,7,2,0}; /* 0Ϊ������� */
		create_list_v1(&head,s); /* �������� */
		sort_lists(head); /* �������� */
		p=head; /* ����ָ��ָ����ͷ */
		while(p){ printf("%d\t",p->data); p=p->next; } /*����ָ��ָ����һ���*/
		printf("\n"); return 0;
}

void create_list_v1(struct s_list **headp,int *p)
{	struct s_list * loc_head=NULL,*tail;
	if(p[0]==0) ;/* �൱��*p==0 */
	else { /* loc_headָ��̬����ĵ�һ����� */
		loc_head=(struct s_list *)malloc(sizeof(struct s_list));
		loc_head->data=*p++; /* ��������ֵ */
		tail=loc_head; /* tailָ���һ����� */
		while(*p){ /* tail��ָ����ָ����ָ��̬�����Ľ�� */
			tail->next=(struct s_list *)malloc(sizeof(struct s_list));
			tail=tail->next; /* tailָ���´����Ľ�� */
			tail->data=*p++; /* ���´����Ľ���������ֵ */
		}
		tail->next=NULL; /* ��ָ����NULLֵ */
	}
	*headp=loc_head; /* ʹͷָ��headpָ���´��������� */
}
