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
	if(c=='\n')  return NULL; //输入\n表示输入字符串结束
	else 
	{ 
	loc_head=(list *)malloc(sizeof(list)); 
	loc_head->c=c; 
	loc_head->next=create_list(); 
	return loc_head;
	}
}
//定义函数反转链表 
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
//定义函数恢复链表 
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
//    //找到中间节点 
//    while(p2->next!=NULL&&p2->next->next!=NULL){
//        p1=p1->next;
//        p2=p2->next->next;
//    }
//    //p1是中间节点，p2是后半部分的开头 
//    p2=p1->next;
//    //中间节点后接NULL,防止死循环 
//    p1->next=NULL;
//    //后半部分反转 
//    list *p3=reverseList(p2);
//    list *p4=p3;
//    list *pHead=head1;
//    //判断是否回文 
//    while(pHead->next!=NULL&&p3->next!=NULL){
//        if(pHead->c!=p3->c){
//            //cout<<pHead->c<<"-"<<p3->c<<endl;
//            flag=0;
//        }
//        pHead=pHead->next;
//        p3=p3->next;
//    }
//    //后半部分再反转回来
//    list *q=reverseList(p4);
//    //从中间节点接上 
//    p1->next=q;
//    return flag;
//}

