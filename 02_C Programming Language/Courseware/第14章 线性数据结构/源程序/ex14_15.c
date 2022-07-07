void disp_d_list(struct d_list *p1)
{	struct d_list *p=p1;
	while(p!=p1->prior){
		printf("%d\t",p->data);
		p=p->next;
	}
	printf("%d\n",p->data);
}
