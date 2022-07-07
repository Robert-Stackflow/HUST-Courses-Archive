#include "stdio.h"
#include "string.h"
#include<stdlib.h>
typedef struct c_node{
    char data;
    struct c_node *next;
} C_NODE;
void createLinkList(C_NODE **headp, char s[]) ;
void judgePalindrome(C_NODE *head);
int main()
{
	char s[1000],*pc=s;
	int len=0;
	C_NODE *head,*p;
	scanf("%[^\n]",s);
	createLinkList(&head,s);
//	p=head;
//	while(p)
//	{
//		printf("%c",p->data);
//		p=p->next;
//	}
	for(p=head;p;p=p->next) len++;
	if (len!=strlen(s)) { printf("�������Ȳ���ȷ");return 1;}
	else for(p=head;p;p=p->next)
        if (p->data!=*pc++) { printf("�������д�����");return 1;}
	judgePalindrome(head);
	return 1;
}

/*void createLinkC_NODE(C_NODE **headp, char s[]) 
�����ַ���s���쵥�����õ�һ���Ե������ʾ���ַ������������㶨����Ҳ�༭����
void judgePalindrome(C_NODE *head) �ж���headΪͷָ��ĵ������ʾ���ַ����Ƿ�Ϊ���ģ�
������ʾtrue��������ʾfalse��
*******************************/
char position(C_NODE **pHead,int n)
{
	C_NODE *p=*pHead;
	int count1=0;
	while(p)
	{
		count1++;
		if(count1==n) return p->data;
		p=p->next;
	}
}
void createLinkList(C_NODE **headp, char s[]) 
{
	*headp=NULL;
	for(int i=0;i<strlen(s);i++)
	{
	C_NODE *pNew=(C_NODE *)malloc(sizeof(C_NODE));
	C_NODE *loc_head=*headp;
	pNew->data=s[i];
	pNew->next=NULL;
	if(*headp==NULL)
		*headp=pNew;
	else
	{
		C_NODE *loc_head=*headp;
		while(loc_head->next)
			loc_head=loc_head->next;
		loc_head->next=pNew;
	}
	}
}

void judgePalindrome(C_NODE *head)
{
	C_NODE *p=head;
	int count=0,flag=1;
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
}

