struct d_list * insert_node_next(struct d_list **headp,int x)
{	struct d_list *p,*new1;
	 	new1 = (struct d_list *) malloc(sizeof(struct d_list));
		scanf("%d",&new1->data);
		/* 查找被删除结点 */
		p = *headp;
		while(p->data != x && p!=(*headp)->prior) {
			p = p->next;
		}
		if(p->data == x){/* 找到，将新结点插人链表中p所指结点之后 */
			/* 使新结点的向前指针指向p */
			new1->prior= p;
			/* 使新结点的向后指针指向结点p的后一结点 */
			new1->next= p->next;
			/* 修改p后一结点的向前指针，使它指向新结点 */
			p->next->prior = new1;
			/* 修改p的向后指针，使它指向新结点 */
			p->next=new1;
			return new1;
		}
		else /* 没有找到，返回NULL */
			return NULL;
}
