struct s_list * find_nodes_recursive(struct s_list * head,int n)
{	struct s_list * p=head;
	if(p){ /* 链表非空，查找 */
		if(p->data==n) return p; /* 找到，返回该结点的地址 */
		else
			find_nodes_recursive(p->next,n);/* 递归查找 */
	}
	else return NULL;
}
