struct s_list{
	int data;
	struct s_list *next;
} ;
int main(void)
{	struct s_list *head=NULL,*p; /*����ͷָ��head�ͱ���ָ��p*/
	head=(struct s_list *)malloc(sizeof(struct s_list)); /*��̬�������1*/
	head->data=1; /*ʹ��ͷָ��head���ʽ��1�����ݳ�Ա */
	head->next=(struct s_list *)malloc(sizeof(struct s_list)); /*�������2*/
	head->next->data=2; /*ʹ��ͷָ��head���ʽ��2�����ݳ�Ա*/
	/*��̬�������3��ʹ��head���ʽ��2ָ���Ա��ʹ��ָ����3*/
	head->next->next=(struct s_list *)malloc(sizeof(struct s_list));
	head->next->next->data=3; /*ʹ��ͷָ��head���ʽ��3�����ݳ�Ա*/
	head->next->next->next=NULL; /*ʹ��ͷָ��head���ʽ��3��ָ���Ա*/
	p=head; /*p=headʹ�ñ���ָ��pָ����1*/
	while(p){
		printf("%p\t%d\t%p\n",p,p->data,p->next);
		p=p->next; 	/* ʹ����ָ��pָ����һ����� */
	}
	return 0;
}
