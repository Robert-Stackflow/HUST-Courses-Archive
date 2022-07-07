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
	if (len!=strlen(s)) { printf("单链表长度不正确");return 1;}
	else for(p=head;p;p=p->next)
        if (p->data!=*pc++) { printf("单链表有错误结点");return 1;}
	judgePalindrome(head);
	return 1;
}

/*void createLinkC_NODE(C_NODE **headp, char s[]) 
根据字符串s构造单链表，得到一个以单链表表示的字符串，单链表结点定义见右侧编辑器。
void judgePalindrome(C_NODE *head) 判断以head为头指针的单链表表示的字符串是否为回文，
是则显示true，否则显示false。
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

