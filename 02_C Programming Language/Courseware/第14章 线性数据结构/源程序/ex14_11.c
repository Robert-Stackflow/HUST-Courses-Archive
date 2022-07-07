void concatenate_lists(struct s_list *headA,struct s_list *headB)
{	struct s_list * current=headA,*prior;
	while(current){
		prior=current; current=current->next;
	}
	prior->next=headB;
}
