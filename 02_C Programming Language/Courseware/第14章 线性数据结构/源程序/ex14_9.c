struct s_list * insert_nodes(struct s_list * head,int n)
{	struct s_list * current=head,*after,*other;
	while(current->data != n && current != NULL)
		current=current->next;
	if(!current) return NULL; /*���û���ҵ����������Ĳ���㣬����NULL*/
		
	after=current->next;     /*�ҵ����������Ĳ���㣬����after*/
	/* otherָ���½������ */
	other = (struct s_list *)malloc(sizeof(struct s_list));
	scanf("%d",&other->data);  /*���½�����ݳ�Ա��ֵ*/
	if(after){	/* ����ͷ������ִ�в��� */
		other->next=after;     /*�½��ָ���̽��*/
		current->next=other;   /*�½���Ϊ�����ĺ�̽��*/
	}
	else{	/* ����βִ�в��� */
		other->next=NULL;     /*���½��ָ����Ϊ��*/
		current->next=other;  /*ԭβ���ָ���½�㣬�½���Ϊ�µ�β���*/
	}
	return current;           /*���ز����ĵ�ַ*/
}
