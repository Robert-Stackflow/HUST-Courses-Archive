void create_d_list(struct d_list **headp,int *p)
{	struct d_list * head=NULL,*tail;
		if(p[0]==0)
			*headp=NULL;
		else {
			head=(struct d_list *)malloc(sizeof(struct d_list));
			head->data=*p++;
			tail=head;
			while(*p){
				tail->next=(struct d_list *)malloc(sizeof(struct d_list));
				tail->next->prior=tail;
				tail=tail->next;
				tail->data=*p++;
			}
			tail->next=head;
			head->prior=tail;
		}
		*headp=head;
}
