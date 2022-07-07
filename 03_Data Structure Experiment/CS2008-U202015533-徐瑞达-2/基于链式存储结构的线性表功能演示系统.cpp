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
#define LIST_INIT_SIZE 10
#define LISTINCREMENT  10
/*-------- Declare the type ---------*/
typedef int status;
typedef int ElemType; //数据元素类型定义
typedef struct LNode{  //单链表（链式结构）结点的定义
      ElemType data;
      struct LNode *next;
}LNode,*LinkList;
typedef struct{  //单链表的管理表定义
     struct { char name[30];
     		  LinkList L;
      }elem[10];
      int length;
}LISTS;
LinkList L;
/*-----Function Declaration---------*/
status InitList(LinkList &L);
status DestroyList(LinkList &L);
status ClearList(LinkList &L);
status ListEmpty(LinkList L);
status ListLength(LinkList L);
status GetElem(LinkList L,int i,ElemType &e);
status LocateElem(LinkList L,ElemType e);
status PriorElem(LinkList L,ElemType e,ElemType &pre);
status NextElem(LinkList L,ElemType e,ElemType &next);
status ListInsert(LinkList &L,int i,ElemType e);
status ListDelete(LinkList &L,int i,ElemType &e);
status ListTraverse(LinkList L);
status SaveList(LinkList L,char FileName[]);
status LoadList(LinkList &L,char FileName[]);
status AddList(LISTS &Lists,char ListName[]);
status RemoveList(LISTS &Lists,char ListName[]);
status LocateList(LISTS Lists,char ListName[]);
/*----- The main function --------*/
int main(void){
	L=NULL;
	LISTS Lists;
	int op=1,res=0;
while(op){
	system("cls"); printf("\n\n");
	printf("      Menu for Linear Table On Sequence Structure \n");
	printf("-------------------------------------------------------\n");
	printf("    	  1. InitList       10. ListInsert\n");
	printf("    	  2. DestroyList    11. ListDelete\n");
	printf("    	  3. ClearList      12. ListTraverse\n");
	printf("    	  4. ListEmpty      13. SaveList\n");
	printf("    	  5. ListLength     14. LoadList\n");
	printf("    	  6. GetElem        15. AddList\n");
	printf("    	  7. LocateElem     16. RemoveList\n");
	printf("    	  8. PriorElem      17. LocateList\n");
	printf("    	  9. NextElem       0. Exit\n");
	printf("-------------------------------------------------------\n");
	printf("请选择你的操作[0~17]:");
	scanf("%d",&op);
    switch(op){
	   case 1:
		 res=InitList(L);
		 if(res==OK) printf("单链表创建成功");
		 else if(res==INFEASIBLE) printf("单链表已创建");
		 else printf("单链表创建失败");
		 getchar();getchar();
		 break;
	   case 2:
		 res=DestroyList(L);
		 if(res==OK)
		 {
		 if(L) printf("单链表销毁失败");
         else printf("单链表销毁成功");
		 }
         else if(res==INFEASIBLE) printf("单链表未创建，无需销毁");
		 else printf("单链表销毁失败");
		 getchar();getchar();
		 break;
	   case 3:
		 res=ClearList(L);
		 if(res==INFEASIBLE) printf("单链表未创建,");
		 if (!L) printf("单链表清除失败");
		 if (res==OK) printf("单链表清除成功");
		 getchar();getchar();
		 break;
	   case 4:
		 res=ListEmpty(L);
		 if (res==TRUE) printf("单链表为空表");
		 else if(res==FALSE)printf("单链表不为空表");
		 else printf("单链表未创建");
		 getchar();getchar();
		 break;
	   case 5:
		 res=ListLength(L);
		 if(res!=-1) printf("单链表的长度为%d",ListLength(L));
		 else printf("单链表未创建");
		 getchar();getchar();
		 break;
	   case 6:
	   	 int pos,e;
         printf("请输入元素位置:");
         scanf("%d",&pos);
         res=GetElem(L,pos,e);
		 if(res==OK)printf("单链表中第%d个元素是%d",pos,e);
		 else if(res==ERROR) printf("输入位置不合法");
		 else printf("单链表未创建");
		 getchar();getchar();
		 break;
	   case 7:
		 int data;
		 printf("请输入元素:");
         scanf("%d",&data);
         res=LocateElem(L,data);
		 if(res!=ERROR) printf("单链表中元素%d的位置是%d",data,LocateElem(L,data));
		 else if(res==ERROR)printf("该元素不在单链表中");
		 else printf("单链表未创建");
		 getchar();getchar();
		 break;
	   case 8:
		 int data1,pre;
		 printf("请输入元素:");
         scanf("%d",&data1);
         res=PriorElem(L,data1,pre);
		 if(res==INFEASIBLE)printf("该元素无直接前驱");
		 else if(res!=ERROR)printf("单链表中元素%d的直接前驱元素是%d",data1,pre);
		 else printf("该元素不在单链表中");
		 getchar();getchar();
		 break;
	   case 9:
		 int data2,next;
		 printf("请输入元素:");
         scanf("%d",&data2);
         res=NextElem(L,data2,next);
		 if(res==INFEASIBLE) printf("该元素无直接后继");
		 else if(res!=ERROR)printf("单链表中元素%d的直接后继元素是%d\n",data2,next);
		 else printf("该元素不在单链表中");
		 getchar();getchar();
		 break;
	   case 10:
		 int data3,pos1;
		 printf("请输入插入的元素及插入的位置:");
		 scanf("%d%d",&data3,&pos1);
		 res=ListInsert(L,pos1,data3);
		 if(res&&res!=INFEASIBLE)printf("插入元素成功，当前单链表的长度为%d",ListLength(L));
		 else if(res==ERROR) printf("元素位置不合法");
		 else printf("单链表未创建");
		 getchar();getchar();
		 break;
	   case 11:
		 int data4,pos2;
		 printf("请输入删除的元素位置:");
		 scanf("%d",&pos2);
		 res=ListDelete(L,pos2,data4);
		 if(res&&res!=INFEASIBLE)printf("删除元素成功，被删除元素为%d，当前单链表的长度为%d",data4,ListLength(L));
		 else if(res==ERROR) printf("元素位置不合法");
		 else printf("单链表未创建");
		 getchar();getchar();
		 break;
	   case 12:
		 res=ListTraverse(L);
		 if(!res) printf("单链表是空表");
		 else if(res==INFEASIBLE) printf("单链表未创建");
		 getchar();getchar();
		 break;
	   case 13:
		 char FileName[30];
		 printf("请输入文件保存路径或文件名:");
		 scanf("%s",FileName);
		 res=SaveList(L,FileName);
		 if(res) printf("文件成功保存至%s\n",FileName);
		 getchar();getchar();
		 break;
	   case 14:
		 char FileName1[30];
		 printf("请输入待加载文件路径或文件名:");
		 scanf("%s",FileName1);
		 res=LoadList(L,FileName1);
		 if(res) printf("文件成功加载至当前单链表\n");
		 else printf("当前单链表未销毁，不能进行加载操作");
		 getchar();getchar();
		 break;
	   case 15:
		 int n,e1,f;
         char name[30];
         Lists.length=0;
         printf("请选择从文件加载(0)或键盘输入(1)：");
         scanf("%d",&f);
         if(!f)
         {
		 char FileName2[50];
		 printf("请输入待加载文件路径或文件名:");
		 scanf("%s",FileName2);
		 FILE *fp=fopen(FileName2,"r");
		 if(fp==NULL) printf("未成功打开文件");
		 while(!feof(fp))
	     {
		 fscanf(fp,"%d",&n);
		 while(n--)
         {
    	 fscanf(fp,"%s",name);
   		 AddList(Lists,name);
         fscanf(fp,"%d",&e1);
         while (e1)
         {
      		ListInsert(Lists.elem[Lists.length-1].L,ListLength(Lists.elem[Lists.length-1].L)+1,e1);
      		fscanf(fp,"%d",&e1);
         }
         }
		 }
		 fclose(fp);
         printf("插入单链表完毕\n当前管理表为:\n");
	     }
		 else
		 {
		 printf("请输入要添加的单链表个数:");
	     scanf("%d",&n);
		 printf("请依次输入单链表名称和单链表元素:");
	     while(n--)
         {
    	 scanf("%s",name);
   		 AddList(Lists,name);
         scanf("%d",&e1);
         while(e1)
         {
      		ListInsert(Lists.elem[Lists.length-1].L,ListLength(Lists.elem[Lists.length-1].L)+1,e1);
      		scanf("%d",&e1);
         }
         }
         printf("插入单链表完毕\n当前管理表为:\n");
		 }
		 for(n=0;n<Lists.length;n++)
         {
   		 printf("%s ",Lists.elem[n].name);
   		 ListTraverse(Lists.elem[n].L);
         putchar('\n');
         }
		 getchar();getchar();
		 break;
       case 16:
         char check[30];
		 printf("请输入要删除的单链表名称:");
		 scanf("%s",check);
		 if (RemoveList(Lists,check)==OK)
	     for(int n=0;n<Lists.length;n++)
   		 {
   			printf("%s ",Lists.elem[n].name);
   			ListTraverse(Lists.elem[n].L);
        	putchar('\n');
   		 }
         else printf("删除单链表失败");
		 getchar();getchar();
		 break;
	   case 17:
		 char check1[30];
		 printf("请输入要查找的单链表名称:");
		 scanf("%s",check1);
		 if(n=LocateList(Lists,check1))
   		 {
   			printf("%s ",Lists.elem[n-1].name);
   			ListTraverse(Lists.elem[n-1].L);
         putchar('\n');
   		 }
         else printf("该单链表不在此管理表中");
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
函数功能:初始化单链表
函数参数:引用单链表L的地址
函数返回值:返回int类型，创建成功返回1
------------------------------------------*/
status InitList(LinkList &L)
{
	if(L==NULL)
	{
	L=(LinkList)malloc(sizeof(LNode));
	L->next=NULL;
	return OK;
	}
	else return INFEASIBLE;
}
/*------------------------------------------
函数功能:销毁单链表
函数参数:引用单链表L的地址
函数返回值:返回int类型，销毁成功返回1
------------------------------------------*/
status DestroyList(LinkList &L)
{
	if(L==NULL) return INFEASIBLE;
	else
	{
	LinkList q=L->next;
	while(q!=NULL){
		free(L);
		L=q;
		q=L->next;
		}
	}
	L=NULL;
	return OK;
}
/*------------------------------------------
函数功能:清空单链表
函数参数:引用单链表L的地址
函数返回值:返回int类型，清空成功返回1
------------------------------------------*/
status ClearList(LinkList &L)
{
	if(L!=NULL)
	{
	LinkList pre,p;
	p = L->next;
    while(p!=NULL) {
        pre=p;
        p=p->next;
        free(pre);
    }
    L->next=NULL;
	return OK;
	}
	else return INFEASIBLE;
}
/*------------------------------------------
函数功能:单链表判空
函数参数:单链表L
函数返回值:返回int类型，单链表为空返回1
------------------------------------------*/
status ListEmpty(LinkList L)
{
	if(L!=NULL&&L->next==NULL) return TRUE;
	else if(L==NULL)return INFEASIBLE;
	else return FALSE;
}
/*------------------------------------------
函数功能:求单链表表长
函数参数:单链表L
函数返回值:返回int类型的单链表长度
------------------------------------------*/
status ListLength(LinkList L)
{
	if(L==NULL)return INFEASIBLE;
	else
	{
		int i=0;
		LinkList p=L->next;
		while(p)
		{
			i++;
			p=p->next;
		}
		return i;
	}
}
/*------------------------------------------
函数功能:得到单链表中的元素并将该元素赋值给e
函数参数:单链表L，元素的位置i，引用元素e的地址
函数返回值:返回int类型，获得成功返回1
------------------------------------------*/
status GetElem(LinkList L,int i,ElemType &e)
{
	if(L==NULL)return INFEASIBLE;
	else
	{
		if(L->next==NULL)return ERROR;
		LinkList p=L->next;
		int j=1;
		while(p&&j<i)
		{
        ++j;
		p=p->next;
        }
        if(p==NULL||j>i) return ERROR;
        e=p->data;
		return OK;
	}
}
/*------------------------------------------
函数功能:查找元素
函数参数:单链表L，待查找元素e
函数返回值:返回int类型，查找成功返回元素位置，否则返回ERROR
------------------------------------------*/
status LocateElem(LinkList L,ElemType e)
{
	if(L==NULL)return INFEASIBLE;
	else
	{
		if(L->next==NULL)return ERROR;
		LinkList p=L->next;
		int j=1;
		while(p)
		{
			if(p->data==e) return j;
			p=p->next;
			j++;
		}
        return ERROR;
	}
}
/*------------------------------------------
函数功能:得到元素的直接前驱并赋值给pre
函数参数:单链表L，元素e，引用待返回元素的地址
函数返回值:返回int类型，得到前驱成功返回1
------------------------------------------*/
status PriorElem(LinkList L,ElemType e,ElemType &pre)
{
	if(L==NULL)return INFEASIBLE;
	else
	{
		if(L->next==NULL)return ERROR;
		LinkList p=L->next,q=L;
		if(p->data==e)return INFEASIBLE;
		while(p)
		{
			if(p->data==e)
			{
			if(p==L->next)return ERROR;
			pre=q->data;
			return OK;
			}
			q=p;
			p=p->next;
		}
        return ERROR;
	}
}
/*------------------------------------------
函数功能:得到元素的直接后继并赋值给next
函数参数:单链表L，元素e，引用待返回元素的地址
函数返回值:返回int类型，得到后继成功返回1
------------------------------------------*/
status NextElem(LinkList L,ElemType e,ElemType &next)
{
	if(L==NULL)return INFEASIBLE;
	else
	{
		if(L->next==NULL)return ERROR;
		LinkList p=L->next;
		while(p)
		{
			if(p->data==e)
			{
			if(p->next==NULL)return INFEASIBLE;
			next=p->next->data;
			return OK;
			}
			p=p->next;
		}
        return ERROR;
	}
}
/*------------------------------------------
函数功能:插入元素在第i个元素前
函数参数:引用单链表L的地址，待插入元素元素e，待插入位置i
函数返回值:返回int类型，插入成功返回1
------------------------------------------*/
status ListInsert(LinkList &L,int i,ElemType e)
{
	if(L==NULL)return INFEASIBLE;
	else
	{
		if(i<=0)return ERROR;
		LinkList p=L;
		LinkList q=(LinkList)malloc(sizeof(LNode));
		q->data=e;
		int j=1;
		if(p->next==NULL)
		{
		L->next=q;
		q->next=NULL;
		return OK;
		}
		while(p&&j<i)
		{
			p=p->next;
			j++;
		}
		if(p==NULL)return ERROR;
		q->next=p->next;
		p->next=q;
        return OK;
	}
}
/*------------------------------------------
函数功能:删除第i个元素并得到被删除元素的值
函数参数:引用单链表L的地址，引用返回元素e的地址，待删除位置i
函数返回值:返回int类型，插入成功返回1
------------------------------------------*/
status ListDelete(LinkList &L,int i,ElemType &e)
{
	if(L==NULL)return INFEASIBLE;
	else
	{
		if(i<=0||L->next==NULL)return ERROR;
		LinkList p=L,q;
		int j=1;
		while(p&&j<i)
		{
			p=p->next;
			if(p==NULL)return ERROR;
			j++;
		}
		if(p->next==NULL)return ERROR;
		q=p->next;
		e=q->data;
		p->next=q->next;
		free(q);
        return OK;
	}
}
/*------------------------------------------
函数功能:遍历输出单链表中的元素
函数参数:单链表L的
函数返回值:返回int类型，遍历成功返回1
------------------------------------------*/
status ListTraverse(LinkList L)
{
	if(L==NULL)return INFEASIBLE;
	else
	{
	LinkList p=L->next;
	while(p)
	{
		printf("%d",p->data);
		if(p->next!=NULL)printf(" ");
		p=p->next;
	}
	return OK;
	}
}
/*------------------------------------------
函数功能:保存单链表到指定文件中
函数参数:单链表L，待保存文件的路径FileName
函数返回值:返回int类型，保存成功返回1
------------------------------------------*/
status SaveList(LinkList L,char FileName[])
{
	if(L==NULL)return INFEASIBLE;
	else
	{
		FILE *fp=fopen(FileName,"w");
		LinkList q=L->next;
		while(q)
		{
			fprintf(fp,"%d",q->data);
			if(q->next!=NULL)fprintf(fp," ");
			q=q->next;
		}
		fclose(fp);
		return OK;
	}
}
/*------------------------------------------
函数功能:加载文件到单链表中
函数参数:单链表L，待加载文件的路径FileName
函数返回值:返回int类型，加载成功返回1
------------------------------------------*/
status LoadList(LinkList &L,char FileName[])
{
	if(L!=NULL)return INFEASIBLE;
	else
	{
		FILE *fin=fopen(FileName,"r");
		if(!fin)return ERROR;
		L=(LinkList)malloc(sizeof(LNode));
		LinkList q=L;
		while(!feof(fin))
		{
			LinkList p=(LinkList)malloc(sizeof(LNode));
			fscanf(fin,"%d",&p->data);
			q->next=p;
			q=q->next;
		}
		q->next=NULL;
		fclose(fin);
		return OK;
	}
}
/*------------------------------------------
函数功能:在单链表的管理表中插入一个新的单链表
函数参数:引用单链表的管理表Lists的地址，待插入单链表的名称FileName
函数返回值:返回int类型，插入成功返回1
------------------------------------------*/
status AddList(LISTS &Lists,char ListName[])
{
	strcpy(Lists.elem[Lists.length].name,ListName);
	Lists.elem[Lists.length].L=(LNode*)malloc(sizeof(LNode));
	Lists.elem[Lists.length].L->next=NULL;
	Lists.length++;
	return OK;
}
/*------------------------------------------
函数功能:在单链表的管理表中删除一个单链表
函数参数:引用单链表的管理表Lists的地址，待删除单链表的名称FileName
函数返回值:返回int类型，删除成功返回1
------------------------------------------*/
status RemoveList(LISTS &Lists,char ListName[])
{
	for(int j=1;j<=Lists.length;j++)
	{
		if(strcmp(ListName,Lists.elem[j-1].name)==0)
		{
		DestroyList(Lists.elem[j-1].L);
		for(int i=j;i<Lists.length;i++)
		{
		strcpy(Lists.elem[i-1].name,Lists.elem[i].name);
		Lists.elem[i-1].L=Lists.elem[i].L;
		}
		Lists.length--;
		return OK;
		}
	}
	return ERROR;
}
/*------------------------------------------
函数功能:在单链表的管理表中查找单链表
函数参数:单链表的管理表Lists，待查找单链表的名称FileName
函数返回值:返回int类型，查找成功返回该单链表的位置
------------------------------------------*/
int LocateList(LISTS Lists,char ListName[])
{
	for(int i=1;i<=Lists.length;i++)
		if(strcmp(ListName,Lists.elem[i-1].name)==0)
		{
			L=Lists.elem[i-1].L;
			return i;
		}
	return ERROR;
}
