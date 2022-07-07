#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct list {
	int data;
	struct list* next;
}list;
typedef struct 
{
	list* list1;
	int scale;
	list* last;
}list1;
void add (list1* list1,int x);
int positon (list1* list1,int check);
list* new_position (list1* list1,int check);
void new_free(list1* list1);
int main()
{ 
	list1 list1= {NULL,0,NULL};
	char c='a';
	int flag=0;
	int t=0;
	while(c!=EOF&&c!='\n')
	{
	c=getchar();
	if(c>='0'&&c<='9'){
	t*=10;
	t+=c-'0';
	flag=1;
}
	else if(c==' '){
	if(flag){
	add(&list1,t);
	t=0;
	flag=0;
}
}
	else if(c=='+')
	{
	int y=positon(&list1,1)+positon(&list1,0);
	new_free(&list1);
	new_free(&list1);
	add (&list1,y);
}
	else if(c=='-'){
	if((c=getchar())==' '||c==EOF||c=='\n')
	{
	int y=positon(&list1,1)-positon(&list1,0);
	new_free(&list1);
	new_free(&list1);
	add(&list1,y);
	}
	else 
	{
	t*=10;
	t+=c-'0';
	t*=-1;
	flag=1;
}
}
	else if(c=='*'){
	int y=positon(&list1,1)*positon(&list1,0);
	new_free(&list1);
	new_free(&list1);
	add(&list1,y);
}

	else if(c=='/'){
	int y=positon(&list1,1)/positon(&list1,0);
	new_free(&list1);
	new_free(&list1);
	add (&list1,y);
}
}
	printf("%d",positon(&list1,0));
	return 0;
}

void add (list1* list1, int x)
{//在链表后添加节点 
	list1->scale++;
	list* np=(list*) malloc(sizeof(list));
	np->data=x;
	if(list1->scale==1)	list1->last=np;
	else 	np->next=list1->list1;
	list1->list1=np;
}

int positon (list1* list1,int check) 
{//定位节点所在处，返回数据域  
	list* np=list1->list1;
	for(int i=0;i<check;i++)	np=np->next;
	return (np->data);
}

list* new_position(list1* list1,int check)
{//返回定位节点处的地址 
	list*np=list1->list1;
	for(int i=0;i<check;i++)	np=np->next;
	return np;
}

void new_free(list1* list1){
//释放节点 
	list*temp=list1->list1->next;
	free(list1->list1);
	list1->list1=temp;
	list1->scale--;
}

