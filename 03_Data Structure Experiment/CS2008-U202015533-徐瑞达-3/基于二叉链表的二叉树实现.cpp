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
}TElemType; //二叉树结点类型定义
TElemType definition[100];
typedef struct BiTNode{    //二叉链表结点的定义
      TElemType data;
      struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;
typedef struct{  //二叉链表的管理表定义
     struct { char name[30];
     		  BiTree T;
      }elem[10];
      int length;
}LISTS;
int i=0;
BiTree T=NULL;
int num=0;//声明全局变量
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
	printf("    	  24. PrintPath(输出所有叶子结点到根结点的路径)\n");
	printf("-------------------------------------------------------\n");
	printf("请选择你的操作[0~24]:");
	scanf("%d",&op);
    switch(op){
	   case 1:
		 j=0;
		 printf("请依次输入各结点的关键字和数据：\n");
		 do{
		 scanf("%d%s",&definition[j].key,definition[j].others);
		 }while(definition[j++].key!=-1);
		 if(T!=NULL) printf("二叉链表已存在");
		 else
		 {
		 i=0;
		 ans=CreateBiTree(T,definition);
		 if(ans==OK) printf("二叉链表创建成功");
		 else printf("关键字不唯一，二叉链表创建失败");
		 }
		 getchar();getchar();
		 break;
	   case 2:
		 ans=ClearBiTree(T);
		 if(ans==OK)
		 {
		 if(T) printf("二叉链表清空失败");
         else printf("二叉链表清空成功");
		 }
         else if(ans==INFEASIBLE) printf("二叉链表已空，无需清空");
		 else printf("二叉表清空失败");
		 getchar();getchar();
		 break;
	   case 3:
		 ans=BiTreeDepth(T);
		 printf("二叉树的深度为%d",ans);
		 getchar();getchar();
		 break;
	   case 4:
		 printf("请输入待查找结点的关键字：");
		 scanf("%d",&e);
		 ptr=LocateNode(T,e);
		 if (ptr==NULL) printf("查找失败，二叉链表中无此结点");
		 else printf("该结点为%d,%s",ptr->data.key,ptr->data.others);
		 getchar();getchar();
		 break;
	   case 5:
		 printf("请输入待查找结点的关键字：");
		 scanf("%d",&e);
		 printf("请输入待赋值的结点数据：");
		 scanf("%d%s",&value.key,value.others);
		 ans=Assign(T,e,value);
		 if(ans==INFEASIBLE) printf("赋值失败，待赋值的结点关键字与当前二叉树中的结点关键字冲突");
		 else if(ans==OK) printf("赋值成功");
		 else if(ans==ERROR) printf("赋值失败，二叉链表中无待查找结点");
		 getchar();getchar();
		 break;
	   case 6:
         printf("请输入待查找结点的关键字:");
         scanf("%d",&e);
         ptr=LocateNode(T,e);
         if(ptr==NULL)printf("二叉链表中无待查找结点");
         else
		 {
		 ptr=GetSibling(T,e);
		 if(ptr==NULL)printf("无兄弟结点");
		 else printf("兄弟结点为%d,%s",ptr->data.key,ptr->data.others);
		 }
		 getchar();getchar();
		 break;
	   case 7:
		 int data;
		 printf("请输入待查找结点关键字:");
		 scanf("%d",&e);
		 printf("请输入插入结点方式:");
		 scanf("%d",&LR);
		 printf("请输入待插入结点的数据:");
         scanf("%d%s",&value.key,value.others);
         ans=InsertNode(T,e,LR,value);
         if(ans==OK) printf("插入成功");
         else if(ans==INFEASIBLE) printf("插入失败,待插入结点与二叉链表中结点关键字冲突");
         else printf("插入失败,无待查找结点");
		 getchar();getchar();
		 break;
	   case 8:
		 printf("请输入待删除结点关键字:");
         scanf("%d",&e);
         ans=DeleteNode(T,e);
		 if(ans==INFEASIBLE)printf("该二叉链表中无该结点");
		 else if(ans==OK)printf("成功删除结点");
		 else printf("删除失败");
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
		 printf("请输入文件名称:");
		 scanf("%s",FileName);
	     ans=SaveBiTree(T,FileName);
	     if(ans==OK) printf("成功保存至文件%s",FileName);
	     else if(ans==INFEASIBLE) printf("未成功打开文件");
	     else printf("二叉树为空");
		 getchar();getchar();
		 break;
	   case 17:
		 printf("请输入文件名称:");
		 scanf("%s",FileName);
		 T=(BiTree)malloc(sizeof(BiTNode));
	     ans=LoadBiTree(T,FileName);
	     if(ans==OK) printf("成功加载文件%s至二叉链表",FileName);
	     else if(ans==INFEASIBLE) printf("未成功打开文件");
		 getchar();getchar();
		 break;
	   case 18:
		 ans=CountNode(T);
		 printf("二叉树中结点个数为%d",ans);
		 getchar();getchar();
		 break;
       case 19:
		 printf("请输入待查找结点关键字:");
		 scanf("%d",&e);
		 ptr=GetParent(T,e);
		 if(ptr)printf("%d,%s",ptr->data.key,ptr->data.others);
		 else printf("二叉链表中无待查找结点或查找结点为根结点");
		 getchar();getchar();
		 break;
	   case 20:
         char name[30],others[30];
         Trees.length=0;
		 printf("请输入要添加的二叉链表个数:");
	     scanf("%d",&n);
		 printf("请依次输入二叉链表名称和二叉链表结点:");
	     while(n--)
         {
    	 scanf("%s",name);
   		 AddTree(Trees,name);
         }
         printf("\n插入二叉链表完毕\n当前管理表为(依次输出每个树的前序和中序遍历):\n");
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
		 printf("请输入要删除的二叉链表名称:");
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
         else printf("删除二叉链表失败");
		 getchar();getchar();
		 break;
	   case 22:
		 char check1[30];
		 printf("请输入要查找的二叉链表名称:");
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
         else printf("该二叉链表不在此管理表中");
		 getchar();getchar();
		 break;
	   case 23:
		 ans=EmptyTree(T);
		 if(ans)printf("二叉树为空");
		 else printf("二叉树不为空");
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
函数功能:实现遍历时所需的功能
函数参数:二叉树T
函数返回值:无返回值
------------------------------------------*/
void visit(BiTree T)
{
    printf(" %d,%s",T->data.key,T->data.others);
}
/*------------------------------------------
函数功能:创建二叉链表
函数参数:二叉树T的引用，二叉树结点数组
函数返回值:返回int类型，创建成功返回1
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
函数功能:清空二叉链表
函数参数:二叉树T的引用
函数返回值:返回int类型，清空成功返回1
------------------------------------------*/
status ClearBiTree(BiTree &T)
{
    if(T==NULL)return INFEASIBLE;//如果T已为空，无需清空
    if(T)
	{//递归清空根结点中的左右子树
    if(T->lchild!=NULL) ClearBiTree(T->lchild);
    if(T->rchild!=NULL) ClearBiTree(T->rchild);
    free(T);//释放根结点
    T=NULL;
    }
    return OK;
}
/*------------------------------------------
函数功能:判空二叉链表
函数参数:二叉树T的引用
函数返回值:返回int类型,树为空返回1
------------------------------------------*/
status EmptyTree(BiTree&T)
{
	if(T==NULL)return OK;
	else return ERROR;
}
/*------------------------------------------
函数功能:求二叉树的深度
函数参数:二叉树T
函数返回值:返回int类型，二叉树为空返回0，否则返回深度
------------------------------------------*/
int BiTreeDepth(BiTree T)
{
    int ld,rd;
    if(T==NULL)return 0;//如果二叉树为空则深度为0
    else {
        ld=BiTreeDepth(T->lchild);//递归计算最左结点的深度
        rd=BiTreeDepth(T->rchild);//递归计算最右结点的深度
        return (ld>=rd?ld:rd)+1;//左右深度的最大值再加上根结点的层数即为二叉树深度
    }
}
/*------------------------------------------
函数功能:查找二叉链表结点
函数参数:二叉树T，待查找关键字e
函数返回值:返回二叉链表结点的指针类型，指示被找到的结点
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
函数功能:给某个结点赋值
函数参数:二叉树T的引用，被赋值的结点的关键字，待赋值的结点
函数返回值:返回int类型，赋值成功返回1
------------------------------------------*/
status Assign(BiTree &T,KeyType e,TElemType value)
{
	if(T==NULL)return ERROR;
	else
	{
		if(T->data.key==value.key&&e!=value.key) return INFEASIBLE;
		//如果当前结点与待赋值的关键字相同且待查找关键字与待赋值的关键字不同时返回INFEASIBLE
		if(T->data.key==e)
		{//否则进行赋值
			T->data=value;
			return OK;
		}
		int flag1=Assign(T->lchild,e,value);//查找左子树进行查找
		if(flag1==INFEASIBLE)return INFEASIBLE;//如果查找左子树时遇到关键字冲突则返回ERROR
		Assign(T->rchild,e,value);
	}
}
/*------------------------------------------
函数功能:得到兄弟结点
函数参数:二叉树T，待查找兄弟结点的结点的关键字e
函数返回值:返回二叉链表结点的指针类型，若有兄弟结点返回指向兄弟结点指针，否则返回NULL
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
}//得到关键字为e的结点的兄弟结点
/*------------------------------------------
函数功能:插入结点
函数参数:二叉树T的引用，被插入结点的关键字e，指示插入类型的整型参数，待插入结点
函数返回值:返回int类型，插入成功返回1
------------------------------------------*/
status InsertNode(BiTree &T,KeyType e,int LR,TElemType c)
{
    if(T==NULL) return ERROR;
    else
	{
	BiTree ctr=(BiTree)malloc(sizeof(BiTNode));
	ctr->data=c;//创建待插入的结点
	ctr->lchild=NULL;
	ctr->rchild=NULL;
	BiTNode*ptr=LocateNode(T,e);
	BiTNode*ptr_1=LocateNode(T,c.key);
	if(ptr_1!=NULL)return INFEASIBLE;
	if(ptr==NULL)return ERROR;
	//如果未找到被插入的结点或者插入会造成关键字不唯一时返回ERROR
	if(LR==0)
	{//待插入结点作为被插入结点的左孩子，原有左子树变为新结点的右子树
        if(ptr->lchild!=NULL)ctr->rchild=ptr->lchild;
        ptr->lchild=ctr;
    }
	else if(LR==1)
	{//待插入结点作为被插入结点的右孩子，原有右子树变为新结点的右子树
        if(ptr->rchild!=NULL) ctr->rchild=ptr->rchild;
        ptr->rchild=ctr;
    }
    else if(LR==-1)
	{//待插入结点成为新的根结点，原有的二叉树作为新结点的右子树
    	ctr->rchild=T;
    	ctr->lchild=NULL;
    	T=ctr;
	}
    return OK;
    }
}
/*------------------------------------------
函数功能:删除结点
函数参数:二叉树T的引用，待删除结点的关键字
函数返回值:返回int类型，遍历成功返回1
------------------------------------------*/
status DeleteNode(BiTree &T,KeyType e)
{
	if(T==NULL) return ERROR;
    else
	{
	BiTNode *ptr=LocateNode(T,e);//获取关键字为e的结点
	BiTNode *parent=GetParent(T,e);//得到关键字为e的结点的父结点
	if(ptr==NULL)return INFEASIBLE;
	int deg=0;
	if(ptr->lchild==NULL&&ptr->rchild==NULL) deg=0;
	else if(ptr->lchild&&ptr->rchild) deg=2;
	else deg=1;//判断度
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
		}//如果是根结点
		if(parent->lchild!=NULL&&parent->lchild->data.key==e)
		{
		if(ptr->lchild!=NULL) parent->lchild=ptr->lchild;
		else parent->lchild=ptr->rchild;
		}//如果被删除结点是左孩子
		else if(parent->rchild!=NULL&&parent->rchild->data.key==e)
		{
		if(ptr->lchild!=NULL) parent->rchild=ptr->lchild;
		else parent->rchild=ptr->rchild;
		}//如果被删除结点是右孩子
		free(ptr);
		ptr==NULL;
		break;
	case 2:
		if(parent==NULL)T=ptr->lchild;
		//如果父结点为空，即待删除的结点为根结点
		else
		{//如果不为空
		if(parent->lchild!=NULL&&parent->lchild->data.key==e) parent->lchild=ptr->lchild;
		//如果父结点的左孩子是待删除结点，则父结点的左孩子为待删除结点的左孩子
		else if(parent->rchild!=NULL&&parent->rchild->data.key==e) parent->rchild=ptr->lchild;
		//如果父结点的右孩子是待删除结点，则父结点的左孩子为待删除结点的左孩子
		}
		BiTNode *cur=ptr->lchild;
		while(cur->rchild) cur=cur->rchild;//找到待删除结点的左子树的最右结点
		cur->rchild=ptr->rchild;//将待删除结点的右子树接到左子树的最右结点处
		free(ptr);//释放被删除结点的空间
		ptr=NULL;
		break;
	}
    return OK;
    }
}
/*------------------------------------------
函数功能:递归实现先序遍历
函数参数:二叉树T，访问函数的指针visit
函数返回值:返回int类型，遍历成功返回1
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
函数功能:非递归实现先序遍历
函数参数:二叉树T，访问函数的指针visit
函数返回值:返回int类型，遍历成功返回1
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
函数功能:递归实现中序遍历
函数参数:二叉树T，访问函数的指针visit
函数返回值:返回int类型，遍历成功返回1
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
函数功能:非递归实现中序遍历
函数参数:二叉树T，访问函数的指针visit
函数返回值:返回int类型，遍历成功返回1
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
函数功能:递归实现后序遍历
函数参数:二叉树T，访问函数的指针visit
函数返回值:返回int类型，遍历成功返回1
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
函数功能:非递归实现后序遍历
函数参数:二叉树T，访问函数的指针visit
函数返回值:返回int类型，遍历成功返回1
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
函数功能:按层遍历二叉树
函数参数:二叉树T，访问函数的指针visit
函数返回值:返回int类型，遍历成功返回1
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
函数功能:保存二叉树到文件中
函数参数:二叉树T，待保存文件的路径名称
函数返回值:返回int类型，保存成功返回1
------------------------------------------*/
status SaveBiTree(BiTree T,char FileName[])
{//利用非递归的先序带空序列将二叉树保存到文件中
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
函数功能:加载文件到二叉树中
函数参数:二叉树T，待加载文件的路径名称
函数返回值:返回int类型，加载成功返回1
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
函数功能:计算二叉树结点数目
函数参数:二叉树T
函数返回值:返回int类型的结点数目
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
函数功能:得到父结点
函数参数:二叉树T的引用，待得到父结点的结点的关键字
函数返回值:返回二叉树结点的指针类型
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
}//得到关键字为e的结点的父结点
/*------------------------------------------
函数功能:在二叉链表的管理表中添加一个二叉链表
函数参数:引用二叉链表的管理表Trees的地址，待添加二叉链表的名称FileName
函数返回值:返回int类型，添加成功返回1
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
函数功能:在二叉链表的管理表中删除一个二叉链表
函数参数:引用二叉链表的管理表Trees的地址，待删除二叉链表的名称FileName
函数返回值:返回int类型，删除成功返回1
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
函数功能:在二叉链表的管理表中查找二叉链表
函数参数:二叉链表的管理表Trees，待查找二叉链表的名称FileName
函数返回值:返回int类型，查找成功返回该二叉链表的位置
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
函数功能:在函数中输出二叉树中从每个叶子结点到根结点的路径
函数参数:二叉树T，存放路径的指向二叉结点的指针类型数组path，路径长度pathlen
函数返回值:返回
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
