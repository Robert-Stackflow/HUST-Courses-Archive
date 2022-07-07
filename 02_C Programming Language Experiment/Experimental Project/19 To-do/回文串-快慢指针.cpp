#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct s_list
{
	char c;
	struct s_list *next;
}list; 
list*create_list();
int isPalindrome(list *head1); 
int main(void)
{
	list *head=NULL,*p;
	int flag=0;
	head=create_list();
	p=head;
//	while(p)
//	{
//		printf("%c",p->c);
//		p=p->next;
//	}
//	printf("\n");
	flag=isPalindrome(head);
	if(flag) printf("true");
	else printf("false");
	return 0;
}

list*create_list()
{	
	list *loc_head=NULL;
	char c='a'; 
	c=getchar(); 
	if(c=='\n')  return NULL; //输入\n表示输入字符串结束
	else 
	{ 
	loc_head=(list *)malloc(sizeof(list)); 
	loc_head->c=c; 
	loc_head->next=create_list(); 
	return loc_head;
	}
}

int isPalindrome(list *head){
	list *fast=head,*slow=head,*pre=head;
	while(fast!=NULL&&fast->next!=NULL){
            fast=fast->next->next;
            list *slowNext=slow->next;
            slow->next=pre;
            pre=slow;
            slow=slowNext;
        }
        if (fast!=NULL){
            slow=slow->next;
        }
        while (slow!=NULL) 
		{
        	if (pre->c!=slow->c)	return 0; 
            pre=pre->next;
            slow=slow->next;
        }
        return 1;
}

