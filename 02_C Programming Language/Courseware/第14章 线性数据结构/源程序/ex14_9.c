struct s_list * insert_nodes(struct s_list * head,int n)
{	struct s_list * current=head,*after,*other;
	while(current->data != n && current != NULL)
		current=current->next;
	if(!current) return NULL; /*如果没有找到符合条件的插入点，返回NULL*/
		
	after=current->next;     /*找到符合条件的插入点，建立after*/
	/* other指向新建立结点 */
	other = (struct s_list *)malloc(sizeof(struct s_list));
	scanf("%d",&other->data);  /*对新结点数据成员赋值*/
	if(after){	/* 在链头或链中执行插入 */
		other->next=after;     /*新结点指向后继结点*/
		current->next=other;   /*新结点成为插入点的后继结点*/
	}
	else{	/* 在链尾执行插入 */
		other->next=NULL;     /*置新结点指针域为空*/
		current->next=other;  /*原尾结点指向新结点，新结点成为新的尾结点*/
	}
	return current;           /*返回插入点的地址*/
}
