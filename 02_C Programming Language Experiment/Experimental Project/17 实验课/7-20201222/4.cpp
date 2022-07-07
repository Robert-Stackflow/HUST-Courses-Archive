#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct s_list
{
	char c;
	struct s_list *next;
}list; 
list*create_list();
list *reverseList(list *head);
list *reverseList2(list *head);
//int isPalindrome(list *head1);
int main(void)
{
	list *head=NULL,*p;
	int flag=0;
	head=create_list();
	p=head;
	while(p)
	{
		printf("%c",p->c);
		p=p->next;
	}
	printf("\n");
//	flag=isPalindrome(head);
	if(flag) printf("true");
	else printf("false");
	return 0;
}

list*create_list()
{	
	list *loc_head=NULL;
	char c='a'; 
	c=getchar(); 
	if(c=='\n')  return NULL; //����\n��ʾ�����ַ�������
	else 
	{ 
	loc_head=(list *)malloc(sizeof(list)); 
	loc_head->c=c; 
	loc_head->next=create_list(); 
	return loc_head;
	}
}
//���庯����ת���� 
list *reverseList(list *head){
    list *p1,*p2,*p3;
    p1=head;
    p2=p1->next;
    while(p2){
        p3=p2->next;
        p2->next=p1;
        p1=p2;
        p2=p3;
    }
    head->next=NULL;
    head=p1;
    return head;
}
//���庯���ָ����� 
list *reverseList2(list *head){
    list *p,*q;
    p=head->next;
    while(p->next!=NULL){
        q=p->next;
        p->next=q->next;
        q->next=head->next;
        head->next=q;
    }
    p->next=head;
    head=p->next->next;
    p->next->next=NULL;
    return head;
}
//int isPalindrome(list *head1)
//{
//    int flag=1;
//    list *p1=head1,*p2=head1;
//    //�ҵ��м�ڵ� 
//    while(p2->next!=NULL&&p2->next->next!=NULL){
//        p1=p1->next;
//        p2=p2->next->next;
//    }
//    //p1���м�ڵ㣬p2�Ǻ�벿�ֵĿ�ͷ 
//    p2=p1->next;
//    //�м�ڵ���NULL,��ֹ��ѭ�� 
//    p1->next=NULL;
//    //��벿�ַ�ת 
//    list *p3=reverseList(p2);
//    list *p4=p3;
//    list *pHead=head1;
//    //�ж��Ƿ���� 
//    while(pHead->next!=NULL&&p3->next!=NULL){
//        if(pHead->c!=p3->c){
//            //cout<<pHead->c<<"-"<<p3->c<<endl;
//            flag=0;
//        }
//        pHead=pHead->next;
//        p3=p3->next;
//    }
//    //��벿���ٷ�ת����
//    list *q=reverseList(p4);
//    //���м�ڵ���� 
//    p1->next=q;
//    return flag;
//}

