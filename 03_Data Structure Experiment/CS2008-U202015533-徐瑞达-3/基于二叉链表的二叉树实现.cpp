/* Linear Table On Sequence Structure */
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
/*-------- Macro Definition ---------*/
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
/*-------- Declare the type ---------*/
typedef int status;
typedef int KeyType;
typedef struct{
     KeyType key;
     char others[20];
}TElemType; //������������Ͷ���
TElemType definition[100];
typedef struct BiTNode{    //����������Ķ���
      TElemType data;
      struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;
typedef struct{  //��������Ĺ������
     struct { char name[30];
     		  BiTree T;
      }elem[10];
      int length;
}LISTS;
int i=0;
BiTree T=NULL;
int num=0;//����ȫ�ֱ���
/*-----Function Declaration---------*/
status CreateBiTree(BiTree &T,TElemType definition[]);
status ClearBiTree(BiTree&T);
status EmptyTree(BiTree&T);
int BiTreeDepth(BiTree T);
BiTNode* LocateNode(BiTree T,KeyType e);
status Assign(BiTree &T,KeyType e,TElemType value);
BiTNode* GetSibling(BiTree T,KeyType e);
status InsertNode(BiTree &T,KeyType e,int LR,TElemType c);
status DeleteNode(BiTree &T,KeyType e);
void visit(BiTree T);
status PreOrderTraverse_recursive(BiTree T,void (*visit)(BiTree));
status PreOrderTraverse(BiTree T,void (*visit)(BiTree));
status InOrderTraverse_recursive(BiTree T,void (*visit)(BiTree));
status InOrderTraverse(BiTree T,void (*visit)(BiTree));
status PostOrderTraverse_recursive(BiTree T,void (*visit)(BiTree));
status PostOrderTraverse(BiTree T,void (*visit)(BiTree));
status LevelOrderTraverse(BiTree T,void (*visit)(BiTree));
status SaveBiTree(BiTree T,char FileName[]);
status LoadBiTree(BiTree &T,char FileName[]);
status AddTree(LISTS &Trees,char TreeName[]);
status RemoveTree(LISTS &Trees,char TreeName[]);
status LocateTree(LISTS Trees,char TreeName[]);
/*-----Aiddtion of functions --------*/
int CountNode(BiTree T);
BiTNode *GetParent(BiTree&T,KeyType e);
void PrintPath(BiTree T,BiTree*path,int pathlen);
/*----- The main function --------*/
int main(){
	BiTNode*ptr;
	KeyType e;
	TElemType value;
	LISTS Trees;
	int LR=0,op=1,ans=0,j=0,n;
	char FileName[20];
while(op){
	system("cls"); printf("\n\n");
	printf("      Menu for Linear Table On Sequence Structure \n");
	printf("-------------------------------------------------------\n");
	printf("    	   1. CreateBiTree            2. ClearBiTree\n");
	printf("    	   3. BiTreeDepth             4. LocateNode\n");
	printf("    	   5. Assign                  6. GetSibling\n");
	printf("    	   7. InsertNode              8. DeleteNode\n");
	printf("    	   9. PreOrderTraverse       10. PreOrderTraverse_recursive\n");
	printf("    	  11. InOrderTraverse        12. InOrderTraverse_recursive\n");
	printf("    	  13. PostOrderTraverse      14. PostOrderTraverse_recursive\n");
	printf("    	  15. LevelOrderTraverse     16. SaveBiTree\n");
	printf("    	  17. LoadBiTree              0. Exit\n");
	printf("-------------------------------------------------------\n");
	printf("    	  18. CountNode              19. GetParent\n");
	printf("          20. AddTree                21.RemoveTree\n");
	printf("          22. LocateTree             23.EmptyTree\n");
	printf("    	  24. PrintPath(�������Ҷ�ӽ�㵽������·��)\n");
	printf("-------------------------------------------------------\n");
	printf("��ѡ����Ĳ���[0~24]:");
	scanf("%d",&op);
    switch(op){
	   case 1:
		 j=0;
		 printf("��������������Ĺؼ��ֺ����ݣ�\n");
		 do{
		 scanf("%d%s",&definition[j].key,definition[j].others);
		 }while(definition[j++].key!=-1);
		 if(T!=NULL) printf("���������Ѵ���");
		 else
		 {
		 i=0;
		 ans=CreateBiTree(T,definition);
		 if(ans==OK) printf("�����������ɹ�");
		 else printf("�ؼ��ֲ�Ψһ������������ʧ��");
		 }
		 getchar();getchar();
		 break;
	   case 2:
		 ans=ClearBiTree(T);
		 if(ans==OK)
		 {
		 if(T) printf("�����������ʧ��");
         else printf("����������ճɹ�");
		 }
         else if(ans==INFEASIBLE) printf("���������ѿգ��������");
		 else printf("��������ʧ��");
		 getchar();getchar();
		 break;
	   case 3:
		 ans=BiTreeDepth(T);
		 printf("�����������Ϊ%d",ans);
		 getchar();getchar();
		 break;
	   case 4:
		 printf("����������ҽ��Ĺؼ��֣�");
		 scanf("%d",&e);
		 ptr=LocateNode(T,e);
		 if (ptr==NULL) printf("����ʧ�ܣ������������޴˽��");
		 else printf("�ý��Ϊ%d,%s",ptr->data.key,ptr->data.others);
		 getchar();getchar();
		 break;
	   case 5:
		 printf("����������ҽ��Ĺؼ��֣�");
		 scanf("%d",&e);
		 printf("���������ֵ�Ľ�����ݣ�");
		 scanf("%d%s",&value.key,value.others);
		 ans=Assign(T,e,value);
		 if(ans==INFEASIBLE) printf("��ֵʧ�ܣ�����ֵ�Ľ��ؼ����뵱ǰ�������еĽ��ؼ��ֳ�ͻ");
		 else if(ans==OK) printf("��ֵ�ɹ�");
		 else if(ans==ERROR) printf("��ֵʧ�ܣ������������޴����ҽ��");
		 getchar();getchar();
		 break;
	   case 6:
         printf("����������ҽ��Ĺؼ���:");
         scanf("%d",&e);
         ptr=LocateNode(T,e);
         if(ptr==NULL)printf("�����������޴����ҽ��");
         else
		 {
		 ptr=GetSibling(T,e);
		 if(ptr==NULL)printf("���ֵܽ��");
		 else printf("�ֵܽ��Ϊ%d,%s",ptr->data.key,ptr->data.others);
		 }
		 getchar();getchar();
		 break;
	   case 7:
		 int data;
		 printf("����������ҽ��ؼ���:");
		 scanf("%d",&e);
		 printf("����������㷽ʽ:");
		 scanf("%d",&LR);
		 printf("������������������:");
         scanf("%d%s",&value.key,value.others);
         ans=InsertNode(T,e,LR,value);
         if(ans==OK) printf("����ɹ�");
         else if(ans==INFEASIBLE) printf("����ʧ��,������������������н��ؼ��ֳ�ͻ");
         else printf("����ʧ��,�޴����ҽ��");
		 getchar();getchar();
		 break;
	   case 8:
		 printf("�������ɾ�����ؼ���:");
         scanf("%d",&e);
         ans=DeleteNode(T,e);
		 if(ans==INFEASIBLE)printf("�ö����������޸ý��");
		 else if(ans==OK)printf("�ɹ�ɾ�����");
		 else printf("ɾ��ʧ��");
		 getchar();getchar();
		 break;
	   case 9:
		 ans=PreOrderTraverse(T,visit);
		 getchar();getchar();
		 break;
	   case 10:
		 ans=PreOrderTraverse_recursive(T,visit);
		 getchar();getchar();
		 break;
	   case 11:
		 ans=InOrderTraverse(T,visit);
		 getchar();getchar();
		 break;
	   case 12:
		 ans=InOrderTraverse_recursive(T,visit);
		 getchar();getchar();
		 break;
	   case 13:
		 ans=PostOrderTraverse(T,visit);
		 getchar();getchar();
		 break;
	   case 14:
		 ans=PostOrderTraverse_recursive(T,visit);
		 getchar();getchar();
		 break;
	   case 15:
		 ans=LevelOrderTraverse(T,visit);
		 getchar();getchar();
		 break;
       case 16:
		 printf("�������ļ�����:");
		 scanf("%s",FileName);
	     ans=SaveBiTree(T,FileName);
	     if(ans==OK) printf("�ɹ��������ļ�%s",FileName);
	     else if(ans==INFEASIBLE) printf("δ�ɹ����ļ�");
	     else printf("������Ϊ��");
		 getchar();getchar();
		 break;
	   case 17:
		 printf("�������ļ�����:");
		 scanf("%s",FileName);
		 T=(BiTree)malloc(sizeof(BiTNode));
	     ans=LoadBiTree(T,FileName);
	     if(ans==OK) printf("�ɹ������ļ�%s����������",FileName);
	     else if(ans==INFEASIBLE) printf("δ�ɹ����ļ�");
		 getchar();getchar();
		 break;
	   case 18:
		 ans=CountNode(T);
		 printf("�������н�����Ϊ%d",ans);
		 getchar();getchar();
		 break;
       case 19:
		 printf("����������ҽ��ؼ���:");
		 scanf("%d",&e);
		 ptr=GetParent(T,e);
		 if(ptr)printf("%d,%s",ptr->data.key,ptr->data.others);
		 else printf("�����������޴����ҽ�����ҽ��Ϊ�����");
		 getchar();getchar();
		 break;
	   case 20:
         char name[30],others[30];
         Trees.length=0;
		 printf("������Ҫ��ӵĶ����������:");
	     scanf("%d",&n);
		 printf("��������������������ƺͶ���������:");
	     while(n--)
         {
    	 scanf("%s",name);
   		 AddTree(Trees,name);
         }
         printf("\n��������������\n��ǰ�����Ϊ(�������ÿ������ǰ����������):\n");
		 for(n=0;n<Trees.length;n++)
         {
   		 printf("%s\n",Trees.elem[n].name);
   		 PreOrderTraverse(Trees.elem[n].T,visit);
         putchar('\n');
         InOrderTraverse(Trees.elem[n].T,visit);
         putchar('\n');
         }
		 getchar();getchar();
		 break;
       case 21:
         char check[30];
		 printf("������Ҫɾ���Ķ�����������:");
		 scanf("%s",check);
		 if (RemoveTree(Trees,check)==OK)
	     for(int n=0;n<Trees.length;n++)
   		 {
   		 printf("%s ",Trees.elem[n].name);
   		 PreOrderTraverse(Trees.elem[n].T,visit);
         putchar('\n');
         InOrderTraverse(Trees.elem[n].T,visit);
         putchar('\n');
         putchar('\n');
   		 }
         else printf("ɾ����������ʧ��");
		 getchar();getchar();
		 break;
	   case 22:
		 char check1[30];
		 printf("������Ҫ���ҵĶ�����������:");
		 scanf("%s",check1);
		 if(n=LocateTree(Trees,check1))
   		 {
   		 printf("%s\n",Trees.elem[n-1].name);
   		 PreOrderTraverse(Trees.elem[n-1].T,visit);
         putchar('\n');
         InOrderTraverse(Trees.elem[n-1].T,visit);
         putchar('\n');
         putchar('\n');
   		 }
         else printf("�ö��������ڴ˹������");
		 getchar();getchar();
		 break;
	   case 23:
		 ans=EmptyTree(T);
		 if(ans)printf("������Ϊ��");
		 else printf("��������Ϊ��");
		 getchar();getchar();
		 break;
	   case 24:
	   	 BiTree path[100];
		 PrintPath(T,path,0);
		 getchar();getchar();
		 break;
	   case 0:
         break;
	}//end of switch
}//end of while
printf("\nWelcome to use this system again next time!\n");
return 0;
}//end of main()
/*----- Implementation of functions --------*/
/*------------------------------------------
��������:ʵ�ֱ���ʱ����Ĺ���
��������:������T
��������ֵ:�޷���ֵ
------------------------------------------*/
void visit(BiTree T)
{
    printf(" %d,%s",T->data.key,T->data.others);
}
/*------------------------------------------
��������:������������
��������:������T�����ã��������������
��������ֵ:����int���ͣ������ɹ�����1
------------------------------------------*/
status CreateBiTree(BiTree &T,TElemType definition[])
{
	for(int j=0;definition[j].key!=-1;j++)
	{
		for(int k=j+1;definition[k].key!=-1;k++)
		if(definition[k].key==definition[j].key&&definition[j].key)return ERROR;
	}
    if(definition[i].key==0)
	{
	T=NULL;
	i++;
	}
	else
	{
		if(!(T=(BiTNode*)malloc(sizeof(BiTNode))))exit(OVERFLOW);
		T->data=definition[i++];
		CreateBiTree(T->lchild,definition);
		CreateBiTree(T->rchild,definition);
	}
	return OK;
}
/*------------------------------------------
��������:��ն�������
��������:������T������
��������ֵ:����int���ͣ���ճɹ�����1
------------------------------------------*/
status ClearBiTree(BiTree &T)
{
    if(T==NULL)return INFEASIBLE;//���T��Ϊ�գ��������
    if(T)
	{//�ݹ���ո�����е���������
    if(T->lchild!=NULL) ClearBiTree(T->lchild);
    if(T->rchild!=NULL) ClearBiTree(T->rchild);
    free(T);//�ͷŸ����
    T=NULL;
    }
    return OK;
}
/*------------------------------------------
��������:�пն�������
��������:������T������
��������ֵ:����int����,��Ϊ�շ���1
------------------------------------------*/
status EmptyTree(BiTree&T)
{
	if(T==NULL)return OK;
	else return ERROR;
}
/*------------------------------------------
��������:������������
��������:������T
��������ֵ:����int���ͣ�������Ϊ�շ���0�����򷵻����
------------------------------------------*/
int BiTreeDepth(BiTree T)
{
    int ld,rd;
    if(T==NULL)return 0;//���������Ϊ�������Ϊ0
    else {
        ld=BiTreeDepth(T->lchild);//�ݹ��������������
        rd=BiTreeDepth(T->rchild);//�ݹ�������ҽ������
        return (ld>=rd?ld:rd)+1;//������ȵ����ֵ�ټ��ϸ����Ĳ�����Ϊ���������
    }
}
/*------------------------------------------
��������:���Ҷ���������
��������:������T�������ҹؼ���e
��������ֵ:���ض����������ָ�����ͣ�ָʾ���ҵ��Ľ��
------------------------------------------*/
BiTNode* LocateNode(BiTree T,KeyType e)
{
	if(T==NULL)return NULL;
	else
	{
		if(T->data.key==e)return T;
		BiTree pl=LocateNode(T->lchild,e);
		BiTree pr=LocateNode(T->rchild,e);
		if(pl!=NULL)return pl;
		else if(pr!=NULL)return pr;
		else return NULL;
	}
}
/*------------------------------------------
��������:��ĳ����㸳ֵ
��������:������T�����ã�����ֵ�Ľ��Ĺؼ��֣�����ֵ�Ľ��
��������ֵ:����int���ͣ���ֵ�ɹ�����1
------------------------------------------*/
status Assign(BiTree &T,KeyType e,TElemType value)
{
	if(T==NULL)return ERROR;
	else
	{
		if(T->data.key==value.key&&e!=value.key) return INFEASIBLE;
		//�����ǰ��������ֵ�Ĺؼ�����ͬ�Ҵ����ҹؼ��������ֵ�Ĺؼ��ֲ�ͬʱ����INFEASIBLE
		if(T->data.key==e)
		{//������и�ֵ
			T->data=value;
			return OK;
		}
		int flag1=Assign(T->lchild,e,value);//�������������в���
		if(flag1==INFEASIBLE)return INFEASIBLE;//�������������ʱ�����ؼ��ֳ�ͻ�򷵻�ERROR
		Assign(T->rchild,e,value);
	}
}
/*------------------------------------------
��������:�õ��ֵܽ��
��������:������T���������ֵܽ��Ľ��Ĺؼ���e
��������ֵ:���ض����������ָ�����ͣ������ֵܽ�㷵��ָ���ֵܽ��ָ�룬���򷵻�NULL
------------------------------------------*/
BiTNode* GetSibling(BiTree T,KeyType e)
{
	if(T==NULL)return NULL;
	else
	{
	if(T->lchild!=NULL&&T->lchild->data.key==e) return T->rchild;
    if(T->rchild!=NULL&&T->rchild->data.key==e) return T->lchild;
	GetSibling(T->lchild,e);
	GetSibling(T->rchild,e);
    }
}//�õ��ؼ���Ϊe�Ľ����ֵܽ��
/*------------------------------------------
��������:������
��������:������T�����ã���������Ĺؼ���e��ָʾ�������͵����Ͳ�������������
��������ֵ:����int���ͣ�����ɹ�����1
------------------------------------------*/
status InsertNode(BiTree &T,KeyType e,int LR,TElemType c)
{
    if(T==NULL) return ERROR;
    else
	{
	BiTree ctr=(BiTree)malloc(sizeof(BiTNode));
	ctr->data=c;//����������Ľ��
	ctr->lchild=NULL;
	ctr->rchild=NULL;
	BiTNode*ptr=LocateNode(T,e);
	BiTNode*ptr_1=LocateNode(T,c.key);
	if(ptr_1!=NULL)return INFEASIBLE;
	if(ptr==NULL)return ERROR;
	//���δ�ҵ�������Ľ����߲������ɹؼ��ֲ�Ψһʱ����ERROR
	if(LR==0)
	{//����������Ϊ������������ӣ�ԭ����������Ϊ�½���������
        if(ptr->lchild!=NULL)ctr->rchild=ptr->lchild;
        ptr->lchild=ctr;
    }
	else if(LR==1)
	{//����������Ϊ����������Һ��ӣ�ԭ����������Ϊ�½���������
        if(ptr->rchild!=NULL) ctr->rchild=ptr->rchild;
        ptr->rchild=ctr;
    }
    else if(LR==-1)
	{//���������Ϊ�µĸ���㣬ԭ�еĶ�������Ϊ�½���������
    	ctr->rchild=T;
    	ctr->lchild=NULL;
    	T=ctr;
	}
    return OK;
    }
}
/*------------------------------------------
��������:ɾ�����
��������:������T�����ã���ɾ�����Ĺؼ���
��������ֵ:����int���ͣ������ɹ�����1
------------------------------------------*/
status DeleteNode(BiTree &T,KeyType e)
{
	if(T==NULL) return ERROR;
    else
	{
	BiTNode *ptr=LocateNode(T,e);//��ȡ�ؼ���Ϊe�Ľ��
	BiTNode *parent=GetParent(T,e);//�õ��ؼ���Ϊe�Ľ��ĸ����
	if(ptr==NULL)return INFEASIBLE;
	int deg=0;
	if(ptr->lchild==NULL&&ptr->rchild==NULL) deg=0;
	else if(ptr->lchild&&ptr->rchild) deg=2;
	else deg=1;//�ж϶�
	switch(deg)
	{
	case 0:
		if(parent==NULL)T=NULL;
	    if(parent&&parent->lchild!=NULL&&parent->lchild->data.key==e) parent->lchild=NULL;
	    else if(parent&&parent->rchild!=NULL&&parent->rchild->data.key==e) parent->rchild=NULL;
		free(ptr);
		ptr=NULL;
		break;
	case 1:
    	if(parent==NULL)
    	{
		if(ptr->lchild!=NULL) T=ptr->lchild;
		else if(ptr->rchild!=NULL) T=ptr->rchild;
		return OK;
		}//����Ǹ����
		if(parent->lchild!=NULL&&parent->lchild->data.key==e)
		{
		if(ptr->lchild!=NULL) parent->lchild=ptr->lchild;
		else parent->lchild=ptr->rchild;
		}//�����ɾ�����������
		else if(parent->rchild!=NULL&&parent->rchild->data.key==e)
		{
		if(ptr->lchild!=NULL) parent->rchild=ptr->lchild;
		else parent->rchild=ptr->rchild;
		}//�����ɾ��������Һ���
		free(ptr);
		ptr==NULL;
		break;
	case 2:
		if(parent==NULL)T=ptr->lchild;
		//��������Ϊ�գ�����ɾ���Ľ��Ϊ�����
		else
		{//�����Ϊ��
		if(parent->lchild!=NULL&&parent->lchild->data.key==e) parent->lchild=ptr->lchild;
		//��������������Ǵ�ɾ����㣬�򸸽�������Ϊ��ɾ����������
		else if(parent->rchild!=NULL&&parent->rchild->data.key==e) parent->rchild=ptr->lchild;
		//����������Һ����Ǵ�ɾ����㣬�򸸽�������Ϊ��ɾ����������
		}
		BiTNode *cur=ptr->lchild;
		while(cur->rchild) cur=cur->rchild;//�ҵ���ɾ�����������������ҽ��
		cur->rchild=ptr->rchild;//����ɾ�������������ӵ������������ҽ�㴦
		free(ptr);//�ͷű�ɾ�����Ŀռ�
		ptr=NULL;
		break;
	}
    return OK;
    }
}
/*------------------------------------------
��������:�ݹ�ʵ���������
��������:������T�����ʺ�����ָ��visit
��������ֵ:����int���ͣ������ɹ�����1
------------------------------------------*/
status PreOrderTraverse_recursive(BiTree T,void (*visit)(BiTree))
{
	if(T==NULL)return ERROR;
	else
    {
        visit(T);
        PreOrderTraverse(T->lchild,visit);
        PreOrderTraverse(T->rchild,visit);
        return OK;
    }
}
/*------------------------------------------
��������:�ǵݹ�ʵ���������
��������:������T�����ʺ�����ָ��visit
��������ֵ:����int���ͣ������ɹ�����1
------------------------------------------*/
status PreOrderTraverse(BiTree T,void (*visit)(BiTree))
{
	struct BiTNode *St[100],*p;
	int top=0;
	if (T!=NULL)
	{
	St[top++]=T;
    while(top)
	{
	p=St[--top];
	visit(p);
	if(p->rchild!=NULL) St[top++]=p->rchild;
	if(p->lchild!=NULL) St[top++]=p->lchild;
    }
    }
}
/*------------------------------------------
��������:�ݹ�ʵ���������
��������:������T�����ʺ�����ָ��visit
��������ֵ:����int���ͣ������ɹ�����1
------------------------------------------*/
status InOrderTraverse_recursive(BiTree T,void (*visit)(BiTree))
{
	if(T==NULL)return ERROR;
	else
    {
        InOrderTraverse(T->lchild,visit);
		visit(T);
        InOrderTraverse(T->rchild,visit);
        return OK;
    }
}
/*------------------------------------------
��������:�ǵݹ�ʵ���������
��������:������T�����ʺ�����ָ��visit
��������ֵ:����int���ͣ������ɹ�����1
------------------------------------------*/
status InOrderTraverse(BiTree T,void (*visit)(BiTree))
{
	BiTNode *st[100];
    int top=0;
	do
	{
    while(T)
    {
	if(top==100) exit(OVERFLOW);
	st[top++]=T;
	T=T->lchild;
    }
    if (top)
    {
	T=st[--top];
    visit(T);
    T=T->rchild;
    }
    }while(top||T);
}
/*------------------------------------------
��������:�ݹ�ʵ�ֺ������
��������:������T�����ʺ�����ָ��visit
��������ֵ:����int���ͣ������ɹ�����1
------------------------------------------*/
status PostOrderTraverse_recursive(BiTree T,void (*visit)(BiTree))
{
	if(T==NULL)return ERROR;
	else
    {
        PostOrderTraverse(T->lchild,visit);
        PostOrderTraverse(T->rchild,visit);
		visit(T);
        return OK;
    }
}
/*------------------------------------------
��������:�ǵݹ�ʵ�ֺ������
��������:������T�����ʺ�����ָ��visit
��������ֵ:����int���ͣ������ɹ�����1
------------------------------------------*/
status PostOrderTraverse(BiTree T,void (*visit)(BiTree))
{
	BiTNode *St[100],*pre;
	int flag,top=0;
	if(T!=NULL)
	{
	do
	{
	while(T!=NULL)
	{
	St[top++]=T;
	T=T->lchild;
	}
	pre=NULL;
	flag=1;
	while(top&&flag)
	{
    T=St[top-1];
	if(T->rchild==pre)
	{
	visit(T);
	top--;
	pre=T;
	}
	else
	{
	T=T->rchild;
	flag=0;
	}
	}
	}while(top);
	}
}
/*------------------------------------------
��������:�������������
��������:������T�����ʺ�����ָ��visit
��������ֵ:����int���ͣ������ɹ�����1
------------------------------------------*/
status LevelOrderTraverse(BiTree T,void (*visit)(BiTree))
{
    if(T==NULL) return ERROR;
	else
	{
	BiTree elem[100],e;
	int front=0,length=0;
	elem[front+length]=T;
	length++;
	while(length!=0)
	{
		e=elem[front];
    	front=(front+1)%100;
    	length--;
    	visit(e);
    	if(e->lchild!=NULL)
    	{
    	elem[front+length]=e->lchild;
	    length++;
		}
    	if(e->rchild!=NULL)
    	{
    	elem[front+length]=e->rchild;
	    length++;
		}
	}
    return OK;
	}
}
/*------------------------------------------
��������:������������ļ���
��������:������T���������ļ���·������
��������ֵ:����int���ͣ�����ɹ�����1
------------------------------------------*/
status SaveBiTree(BiTree T,char FileName[])
{//���÷ǵݹ������������н����������浽�ļ���
	if(T==NULL)return ERROR;
	else
    {
    FILE *fp=fopen(FileName,"w");
    if(fp==NULL)return INFEASIBLE;
    struct BiTNode *St[100],*p;
  	int top=0;
	St[top++]=T;
    while(top)
	{
	p=St[--top];
	if(p!=NULL)fprintf(fp,"%d %s ",p->data.key,p->data.others);
	else {fprintf(fp,"0 null ");continue;}
	if(p->rchild!=NULL) St[top++]=p->rchild;
	else if(p->rchild==NULL)St[top++]=NULL;
	if(p->lchild!=NULL) St[top++]=p->lchild;
	else if(p->lchild==NULL)St[top++]=NULL;
    }
    fprintf(fp,"-1 null ");
    fclose(fp);
    return OK;
    }
}
/*------------------------------------------
��������:�����ļ�����������
��������:������T���������ļ���·������
��������ֵ:����int���ͣ����سɹ�����1
------------------------------------------*/
status LoadBiTree(BiTree &T,char FileName[])
{
	FILE *fp=fopen(FileName,"r");
	if(fp==NULL)return INFEASIBLE;
	int j=0;
	TElemType definition[100];
	do{
	fscanf(fp,"%d%s",&definition[j].key,definition[j].others);
	}while(definition[j++].key!=-1);
	i=0;
	CreateBiTree(T,definition);
	fclose(fp);
	return OK;
}
/*------------------------------------------
��������:��������������Ŀ
��������:������T
��������ֵ:����int���͵Ľ����Ŀ
------------------------------------------*/
int CountNode(BiTree T)
{
	int n=0;
	if(T)
	{
	n=1;
    n+=CountNode(T->lchild);
    n+=CountNode(T->rchild);
    }
    return n;
}
/*------------------------------------------
��������:�õ������
��������:������T�����ã����õ������Ľ��Ĺؼ���
��������ֵ:���ض���������ָ������
------------------------------------------*/
BiTNode *GetParent(BiTree&T,KeyType e)
{
	if(T==NULL)return NULL;
	else
	{
    if(T->data.key==e) return NULL;
	if(T->lchild!=NULL&&T->lchild->data.key==e) return T;
    if(T->rchild!=NULL&&T->rchild->data.key==e) return T;
	BiTree p=GetParent(T->lchild,e);
	BiTree q=GetParent(T->rchild,e);
	if(p!=NULL)return p;
	if(q!=NULL)return q;
    }
}//�õ��ؼ���Ϊe�Ľ��ĸ����
/*------------------------------------------
��������:�ڶ�������Ĺ���������һ����������
��������:���ö�������Ĺ����Trees�ĵ�ַ������Ӷ������������FileName
��������ֵ:����int���ͣ���ӳɹ�����1
------------------------------------------*/
status AddTree(LISTS &Trees,char TreeName[])
{
	strcpy(Trees.elem[Trees.length].name,TreeName);
	int r=-1;
	TElemType trees_definition[100];
    do{
        r++;
		scanf("%d%s",&trees_definition[r].key,trees_definition[r].others);
	}while(trees_definition[r].key!=-1);
	i=0;
	CreateBiTree(Trees.elem[Trees.length].T,trees_definition);
	Trees.length++;
	return OK;
}
/*------------------------------------------
��������:�ڶ�������Ĺ������ɾ��һ����������
��������:���ö�������Ĺ����Trees�ĵ�ַ����ɾ���������������FileName
��������ֵ:����int���ͣ�ɾ���ɹ�����1
------------------------------------------*/
status RemoveTree(LISTS &Trees,char TreeName[])
{
	for(int j=1;j<=Trees.length;j++)
	{
		if(strcmp(TreeName,Trees.elem[j-1].name)==0)
		{
		ClearBiTree(Trees.elem[j-1].T);
		for(int i=j;i<Trees.length;i++)
		{
		strcpy(Trees.elem[i-1].name,Trees.elem[i].name);
		Trees.elem[i-1].T=Trees.elem[i].T;
		}
		Trees.length--;
		return OK;
		}
	}
	return ERROR;
}
/*------------------------------------------
��������:�ڶ�������Ĺ�����в��Ҷ�������
��������:��������Ĺ����Trees�������Ҷ������������FileName
��������ֵ:����int���ͣ����ҳɹ����ظö��������λ��
------------------------------------------*/
int LocateTree(LISTS Trees,char TreeName[])
{
	for(int i=1;i<=Trees.length;i++)
		if(strcmp(TreeName,Trees.elem[i-1].name)==0)
		{
			T=Trees.elem[i-1].T;
			return i;
		}
	return ERROR;
}
/*------------------------------------------
��������:�ں���������������д�ÿ��Ҷ�ӽ�㵽������·��
��������:������T�����·����ָ��������ָ����������path��·������pathlen
��������ֵ:����
------------------------------------------*/
void PrintPath(BiTree T,BiTree *path,int pathlen)
{
    int i;
    if(T!=NULL)
	{
    path[pathlen]=T;
    if(T->lchild==NULL&&T->rchild==NULL)
    {
    	for(i=pathlen;i>=0;i--)
			printf("%d,%s ",path[i]->data.key,path[i]->data.others);
  		printf("\n");
	}
	else
	{
    	PrintPath(T->lchild,path,pathlen+1);
    	PrintPath(T->rchild,path,pathlen+1);
    }
    }
}
