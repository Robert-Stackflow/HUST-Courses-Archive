#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*��������
1
4 
U202012345 Jack 99 100 80 96   
U202054321 Rose 89 94 85 100
U202056789 Tom 12 34 56 78
U202098765 Jerry 98 76 54 32
2
3
U202054321 1 66
4
5
*/
typedef struct s_list
{
	char num[20];
	char name[10];
	int score[4];
	int sum;
	float average;
	struct s_list *next;
}list; 
void create_list(list **headp,int number);
void AddToTail(list ** pHead);
int main(void)
{
	list *head=NULL,*p,*before;
	int number,flag=1,check_count=0,check_new,count=1;
	char check_num[20];
	while(flag!=5)
{
	scanf("%d",&flag);
	if(flag==1)
	{
	scanf("%d",&number);
	if(count!=1)//�����������Ϣʱ��һ���Ժ�ͨ�����ӽڵ���¼����Ϣ 
	{
	for(int i=0;i<number;i++)
		AddToTail(&head);	
	}
	else	create_list(&head,number);
	p=head;
	while(p)
		{
			p->sum=p->score[0]+p->score[1]+p->score[2]+p->score[3];
			//����ɼ��ܺ� 
			p->average=(float)((p->sum)/4.0);
			p=p->next;//����ƽ��ֵ		
		}
	count++;//��¼������Ϣ���� 
	}
	if(flag==2)
	{
		
		p=head;
		while(p){
		printf("%s %s ",p->num,p->name);
		for(int i=0;i<4;i++)
		{
			printf("%d",p->score[i]);
			if(i<3)	printf(" ");
		}
		printf("\n"); 
		p=p->next;
	}
	} 
	if(flag==3)
	{
		scanf("%s%d%d",check_num,&check_count,&check_new);
		p=head;
		while(p)
		{ 
		if(strcmp(p->num,check_num)==0)//�����Ƚ�ѧ�ŴӶ����� 
		{
			p->score[check_count-1]=check_new;
			break;
		}
		else p=p->next;
		}
		p=head;
		while(p)
		{
			p->sum=p->score[0]+p->score[1]+p->score[2]+p->score[3];
			p->average=(float)((p->sum)/4.0);
			p=p->next;//���¼����ܺͺ�ƽ��ֵ			
		}
	}
	if(flag==4)
	{
		p=head;
		while(p)
		{
			printf("%s %s %.2f\n",p->num,p->name,p->average);
			p=p->next;		
		}
	}
	if(flag==5)
	{
		p=head;
		while(p)
		{
			printf("%s %s %d %.2f\n",p->num,p->name,p->sum,p->average);
			p=p->next;
		}
		return 0;	
	}
}		
}

void create_list(list **headp,int number)
{	list *loc_head=NULL,*tail;
	char num0[20];
	char name0[10];
	int score0[4];//����ΪEnglish,math,physics,C�ɼ�
	scanf("%s%s%d%d%d%d",num0,name0,&score0[0],&score0[1],&score0[2],&score0[3]);
	//��¼�����Ϣ������ʱ�������� 
		loc_head=(list *)malloc(sizeof(struct s_list));
		strcpy(loc_head->num,num0);
		strcpy(loc_head->name,name0);
		for(int i=0;i<4;i++)
			loc_head->score[i]=score0[i];
		//���θ�ֵ 
		tail=loc_head; 
		for(int i=1;i<number;i++){
			scanf("%s%s%d%d%d%d",num0,name0,&score0[0],&score0[1],&score0[2],&score0[3]);
			tail->next=(list *)malloc(sizeof(struct s_list));
			tail=tail->next; 
			strcpy(tail->num,num0);
			strcpy(tail->name,name0);
			for(int i=0;i<4;i++)
			tail->score[i]=score0[i];
			//���θ�ֵ
		}
		tail->next=NULL; 
	*headp=loc_head; 
}


void AddToTail(list **pHead)//����������β�ڵ������½ڵ� 
{
	list * pNew=(list *)malloc(sizeof(struct s _list));
	char num0[20];
	char name0[10];
	int score0[4];//����ΪEnglish,math,physics,C�ɼ� 
	scanf("%s%s%d%d%d%d",num0,name0,&score0[0],&score0[1],&score0[2],&score0[3]);
	strcpy(pNew->num,num0);
			strcpy(pNew->name,name0);
	for(int i=0;i<4;i++)
			pNew->score[i]=score0[i];
	pNew->next=NULL;
	if(*pHead==NULL)
		*pHead=pNew;
	else
	{
		list *pNode=*pHead;
		while(pNode->next != NULL)
			pNode=pNode->next;
		pNode->next=pNew;
	}
}

