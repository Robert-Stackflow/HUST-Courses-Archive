int count_nodes(struct s_list * head)
{	struct s_list * p=head;
	int num=0;
	while(p){
		num++; p=p->next;
	}
	return num;
} 
