struct s_list * find_nodes_recursive(struct s_list * head,int n)
{	struct s_list * p=head;
	if(p){ /* ����ǿգ����� */
		if(p->data==n) return p; /* �ҵ������ظý��ĵ�ַ */
		else
			find_nodes_recursive(p->next,n);/* �ݹ���� */
	}
	else return NULL;
}
