struct s_list{
	int data;
	struct s_list *next;
} ;
int main(void)
{	struct s_list *head=NULL,*p; /*声明头指针head和遍历指针p*/
	head=(struct s_list *)malloc(sizeof(struct s_list)); /*动态创建结点1*/
	head->data=1; /*使用头指针head访问结点1的数据成员 */
	head->next=(struct s_list *)malloc(sizeof(struct s_list)); /*创建结点2*/
	head->next->data=2; /*使用头指针head访问结点2的数据成员*/
	/*动态创建结点3，使用head访问结点2指针成员并使它指向结点3*/
	head->next->next=(struct s_list *)malloc(sizeof(struct s_list));
	head->next->next->data=3; /*使用头指针head访问结点3的数据成员*/
	head->next->next->next=NULL; /*使用头指针head访问结点3的指针成员*/
	p=head; /*p=head使得遍历指针p指向结点1*/
	while(p){
		printf("%p\t%d\t%p\n",p,p->data,p->next);
		p=p->next; 	/* 使遍历指针p指向下一个结点 */
	}
	return 0;
}
