struct d_list * insert_node_next(struct d_list **headp,int x)
{	struct d_list *p,*new1;
	 	new1 = (struct d_list *) malloc(sizeof(struct d_list));
		scanf("%d",&new1->data);
		/* ���ұ�ɾ����� */
		p = *headp;
		while(p->data != x && p!=(*headp)->prior) {
			p = p->next;
		}
		if(p->data == x){/* �ҵ������½�����������p��ָ���֮�� */
			/* ʹ�½�����ǰָ��ָ��p */
			new1->prior= p;
			/* ʹ�½������ָ��ָ����p�ĺ�һ��� */
			new1->next= p->next;
			/* �޸�p��һ������ǰָ�룬ʹ��ָ���½�� */
			p->next->prior = new1;
			/* �޸�p�����ָ�룬ʹ��ָ���½�� */
			p->next=new1;
			return new1;
		}
		else /* û���ҵ�������NULL */
			return NULL;
}
