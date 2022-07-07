/*版本1: 先单独处理链头的方法*/
void sort_lists_by_pointer_v1(struct s_list **headp)
{	struct s_list *prior1,*prior2,*p1,*p2,*t;
	int i=0;
	p1=*headp;
	for(p2=p1->next,prior2=p1;p2!=NULL;prior2=p2,p2=p2->next)
		if(p1->data>p2->data){
			prior2->next=p1; t=p1->next;
			p1->next=p2->next; (*headp)=p2;
			p2->next=t; p1=p2;
		}
	for(prior1=*headp,p1=prior1->next;p1->next!=NULL;prior1=p1,p1=p1->next)
		for(p2=p1->next,prior2=p1;p2!=NULL;prior2=p2,p2=p2->next)
			if(p1->data>p2->data){
				t=p2->next; prior1->next=p2;
				prior2->next=p1; p2->next=p1->next;
				p1->next=t; p1=p2;
			}
}
/*版本2：新增头指针结点的方法*/
void sort_lists_by_pointer_v2(struct s_list **headp)
{	struct s_list *prior1,*prior2,*p1,*p2,*t;
	int i=0;
	p1=(struct s_list *)malloc(sizeof(struct s_list));
	p1->next=*headp;
	(*headp)=prior1=p1;
	for(p1=prior1->next;p1->next!=NULL;prior1=p1,p1=p1->next)
		for(p2=p1->next,prior2=p1;p2!=NULL;prior2=p2,p2=p2->next)
			if(p1->data>p2->data){
				t=p2->next;			//第1步
				prior1->next=p2;		//第2步
				prior2->next=p1;		//第3步
				p2->next=p1->next;	//第4步
				p1->next=t;			//第5步
				t=p1;p1=p2;p2=t;		//第6步
			}
	p1=(*headp);/* p1指向新增头指针结点 */
	(*headp)=(*headp)->next; /* (*headp)指向排序后链表的链头 */
	free(p1); /* 释放新增头指针结点 */
}