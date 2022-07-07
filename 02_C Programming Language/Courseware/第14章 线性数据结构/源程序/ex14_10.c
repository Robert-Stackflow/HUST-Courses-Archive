struct s_list * delete_nodes(struct s_list **headp,int n)
{	struct s_list * current=*headp,*prior=*headp;
	while(current->data!=n&&current!=NULL){ /* 查找成员值与n相等的结点 */
		prior=current;              /* prior指向当前结点 */
		current=current->next;      /* current指向下一结点 */
	}
	if(!current)                    /* 没有符合条件的结点 */
		return NULL;
	if(current==*headp)             /* 被删结点是链头*/
		*headp=current->next;
	else                           /* 被删结点不是链头 */
		prior->next= current->next;
	free(current);                 /* 释放被删结点的存储 */
	return current;
}
