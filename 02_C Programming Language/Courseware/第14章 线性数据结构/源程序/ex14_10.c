struct s_list * delete_nodes(struct s_list **headp,int n)
{	struct s_list * current=*headp,*prior=*headp;
	while(current->data!=n&&current!=NULL){ /* ���ҳ�Աֵ��n��ȵĽ�� */
		prior=current;              /* priorָ��ǰ��� */
		current=current->next;      /* currentָ����һ��� */
	}
	if(!current)                    /* û�з��������Ľ�� */
		return NULL;
	if(current==*headp)             /* ��ɾ�������ͷ*/
		*headp=current->next;
	else                           /* ��ɾ��㲻����ͷ */
		prior->next= current->next;
	free(current);                 /* �ͷű�ɾ���Ĵ洢 */
	return current;
}
