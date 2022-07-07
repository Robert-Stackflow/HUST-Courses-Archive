int count_nodes_recursive(struct s_list * head)
{	struct s_list * p=head;
	if(p)  return (1+count_nodes_recursive(p->next));
	else  return 0;
}
