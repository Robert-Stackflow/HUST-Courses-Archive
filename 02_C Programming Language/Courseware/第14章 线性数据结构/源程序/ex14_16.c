int delete_d_list(struct d_list **headp,int x)
{	struct d_list *p; 
/*查找被删除结点*/
		p = *headp;
		while(p->data != x && p->next != NULL) 
			p = p->next;
		if(p->data == x) {  /* 找到被删结点 */
			if(p == *headp){ /* 被删结点是头结点 */
				*headp = p->next;
				(*headp)->prior=p->prior;
			}
			else {
				p->prior->next = p->next; /* 被删结点不是头结点 */
				p->next->prior = p->prior;
			}
			free(p);
			return 1;
		}
		else
			return 0;
}
