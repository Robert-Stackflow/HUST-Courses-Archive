#include "stdio.h"
struct s_list{
	int data;
	struct s_list *next;
} node1={1,NULL};
int main(void)
{
	struct s_list node2,node3;
	struct s_list *head=NULL,*p;
	node2.data=2;
	node3.data=3;
	node2.next=node3.next=NULL;
	head=&node1; /* 头指针指向node1 */
	node1.next=&node2; /* node1指向了node2 */
	node2.next=&node3; /* node2指向了node3 */
	p=head; /* 遍历指针指向node1 */
	printf("%p\t%p\n",&head,head); 
	while(p){
		printf("%p\t%d\t%p\n",p,p->data,p->next);/* 输出 */
		p=p->next; /* 遍历指针指向下一个自引用结构 */
	}
	return 0;
}
