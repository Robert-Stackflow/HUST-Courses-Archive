int delete_d_list(struct d_list **headp,int x)
{	struct d_list *p; 
/*���ұ�ɾ�����*/
		p = *headp;
		while(p->data != x && p->next != NULL) 
			p = p->next;
		if(p->data == x) {  /* �ҵ���ɾ��� */
			if(p == *headp){ /* ��ɾ�����ͷ��� */
				*headp = p->next;
				(*headp)->prior=p->prior;
			}
			else {
				p->prior->next = p->next; /* ��ɾ��㲻��ͷ��� */
				p->next->prior = p->prior;
			}
			free(p);
			return 1;
		}
		else
			return 0;
}
