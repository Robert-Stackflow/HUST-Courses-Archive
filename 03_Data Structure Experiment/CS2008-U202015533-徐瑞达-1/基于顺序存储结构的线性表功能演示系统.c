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
typedef struct{  //顺序表（顺序结构）的定义
	ElemType * elem;
	int length;
	int listsize;
}SqList;
typedef struct{ //线性表的管理表定义
    struct{
		char name[30];
    	SqList L;
    }elem[10];
    int length;
    int listsize;
}LISTS;
SqList L;
/*-----Function Declaration---------*/
status InitList(SqList &L);
status DestroyList(SqList &L);
status ClearList(SqList &L);
status ListEmpty(SqList L);
status ListLength(SqList L);
status GetElem(SqList L,int i,ElemType &e);
status LocateElem(SqList L,ElemType e);
status PriorElem(SqList L,ElemType e,ElemType &pre);
status NextElem(SqList L,ElemType e,ElemType &next);
status ListInsert(SqList &L,int i,ElemType e);
status ListDelete(SqList &L,int i,ElemType &e);
status ListTraverse(SqList L);
status SaveList(SqList L,char FileName[]);
status LoadList(SqList &L,char FileName[]);
status AddList(LISTS &Lists,char ListName[]);
status RemoveList(LISTS &Lists,char ListName[]);
status LocateList(LISTS Lists,char ListName[]);
/*----- The main function --------*/
int main(void){
	L.elem=NULL;
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
		 if(res==OK) printf("线性表创建成功");
		 else if(res==INFEASIBLE) printf("线性表已创建");
		 else printf("线性表创建失败");
		 getchar();getchar();
		 break;
	   case 2:
		 res=DestroyList(L);
		 if(res==OK)
		 {
		 if(L.elem) printf("线性表销毁失败");
         else printf("线性表销毁成功");
		 }
         else if(res==INFEASIBLE) printf("线性表未创建，无需销毁");
		 else printf("线性表销毁失败");
		 getchar();getchar();
		 break;
	   case 3:
		 res=ClearList(L);
		 if (L.length||(!L.elem)) printf("线性表清除失败");
		 if (res==OK) printf("线性表清除成功");
		 if(res==INFEASIBLE) printf("线性表未创建");
		 getchar();getchar();
		 break;
	   case 4:
		 res=ListEmpty(L);
		 if (res==TRUE) printf("线性表为空表");
		 else if(res==FALSE)printf("线性表不为空表");
		 else printf("线性表未创建");
		 getchar();getchar();
		 break;
	   case 5:
		 res=ListLength(L);
		 if(res==L.length) printf("线性表的长度为%d",ListLength(L));
		 else printf("线性表未创建");
		 getchar();getchar();
		 break;
	   case 6:
	   	 int pos,e;
         printf("请输入元素位置:");
         scanf("%d",&pos);
         res=GetElem(L,pos,e);
		 if(res==OK)printf("线性表中第%d个元素是%d",pos,e);
		 else if(res==ERROR) printf("输入位置不合法");
		 else printf("线性表未创建");
		 getchar();getchar();
		 break;
	   case 7:
		 int data;
		 printf("请输入元素:");
         scanf("%d",&data);
         res=LocateElem(L,data);
		 if(res!=ERROR) printf("线性表中元素%d的位置是%d",data,LocateElem(L,data));
		 else if(res==ERROR)printf("该元素不在线性表中");
		 else printf("线性表未创建");
		 getchar();getchar();
		 break;
	   case 8:
		 int data1,pre;
		 printf("请输入元素:");
         scanf("%d",&data1);
         res=PriorElem(L,data1,pre);
		 if(res==INFEASIBLE)printf("该元素无直接前驱");
		 else if(res!=ERROR)printf("线性表中元素%d的直接前驱元素是%d",data1,pre);
		 else printf("该元素不在线性表中");
		 getchar();getchar();
		 break;
	   case 9:
		 int data2,next;
		 printf("请输入元素:");
         scanf("%d",&data2);
         res=NextElem(L,data2,next);
		 if(res==INFEASIBLE) printf("该元素无直接后继");
		 else if(res!=ERROR)printf("线性表中元素%d的直接后继元素是%d\n",data2,next);
		 else printf("该元素不在线性表中");
		 getchar();getchar();
		 break;
	   case 10:
		 int data3,pos1;
		 printf("请输入插入的元素及插入的位置:");
		 scanf("%d%d",&data3,&pos1);
		 res=ListInsert(L,pos1,data3);
		 if(res&&res!=INFEASIBLE)printf("插入元素成功，当前线性表的长度为%d",ListLength(L));
		 else if(res==ERROR) printf("元素位置不合法");
		 else printf("线性表未创建");
		 getchar();getchar();
		 break;
	   case 11:
		 int data4,pos2;
		 printf("请输入删除的元素位置:");
		 scanf("%d",&pos2);
		 res=ListDelete(L,pos2,data4);
		 if(res&&res!=INFEASIBLE)printf("删除元素成功，被删除元素为%d，当前线性表的长度为%d",data4,ListLength(L));
		 else if(res==ERROR) printf("元素位置不合法");
		 else printf("线性表未创建");
		 getchar();getchar();
		 break;
	   case 12:
		 res=ListTraverse(L);
		 if(!res) printf("线性表是空表");
		 else if(res==INFEASIBLE) printf("线性表未创建");
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
		 if(res) printf("文件成功加载至当前线性表\n");
		 else printf("当前线性表未销毁，不能进行加载操作");
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
      		ListInsert(Lists.elem[Lists.length-1].L,Lists.elem[Lists.length-1].L.length+1,e1);
      		fscanf(fp,"%d",&e1);
         }
         }
		 }
		 fclose(fp);
         printf("插入线性表完毕\n当前管理表为:\n");
	     }
		 else
		 {
		 printf("请输入要添加的线性表个数:");
	     scanf("%d",&n);
		 printf("请依次输入线性表名称和线性表元素:");
	     while(n--)
         {
    	 scanf("%s",name);
   		 AddList(Lists,name);
         scanf("%d",&e1);
         while (e1)
         {
      		ListInsert(Lists.elem[Lists.length-1].L,Lists.elem[Lists.length-1].L.length+1,e1);
      		scanf("%d",&e1);
         }
         }
         printf("插入线性表完毕\n当前管理表为:\n");
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
		 printf("请输入要删除的线性表名称:");
		 scanf("%s",check);
		 if (RemoveList(Lists,check)==OK)
	     for(int n=0;n<Lists.length;n++)
   		 {
   			printf("%s ",Lists.elem[n].name);
   			ListTraverse(Lists.elem[n].L);
        	putchar('\n');
   		 }
         else printf("删除线性表失败");
		 getchar();getchar();
		 break;
	   case 17:
		 char check1[30];
		 printf("请输入要查找的线性表名称:");
		 scanf("%s",check1);
		 if(n=LocateList(Lists,check1))
   		 {
   			printf("%s ",Lists.elem[n-1].name);
   			ListTraverse(Lists.elem[n-1].L);
         putchar('\n');
   		 }
         else printf("该线性表不在此管理表中");
		 getchar();getchar();
		 break;
	   case 0:
         break;
	}//end of switch
  }//end of while
printf("\nWelcome to use this system again next time!\n");
return 0;
//system("pause");
}//end of main()
/*----- Implementation of functions --------*/
/*------------------------------------------
函数功能:初始化线性表
函数参数:引用线性表L的地址
函数返回值:返回int类型，创建成功返回1
------------------------------------------*/
status InitList(SqList &L)
{
	if(L.elem==NULL)
	{
	ElemType *newbase=(ElemType *)malloc(sizeof(ElemType)*LIST_INIT_SIZE);
	if(!newbase) exit(OVERFLOW);
	L.elem=newbase;
	L.length=0;
	L.listsize=LIST_INIT_SIZE;
	return OK;
	}
	else return INFEASIBLE;
}
/*------------------------------------------
函数功能:销毁线性表
函数参数:引用线性表L的地址
函数返回值:返回int类型，销毁成功返回1
------------------------------------------*/
status DestroyList(SqList &L)
{
	if(L.elem==NULL) return INFEASIBLE;
	else
	{
	free(L.elem);
	L.elem=NULL;
	L.length=0;
	L.listsize=0;
	return OK;
	}
}
/*------------------------------------------
函数功能:清空线性表
函数参数:引用线性表L的地址
函数返回值:返回int类型，清空成功返回1
------------------------------------------*/
status ClearList(SqList &L)
{
	if(L.elem!=NULL)
	{
	L.length=0;
	return OK;
	}
	else return INFEASIBLE;
}
/*------------------------------------------
函数功能:线性表判空
函数参数:线性表L
函数返回值:返回int类型，线性表为空返回1
------------------------------------------*/
status ListEmpty(SqList L)
{
	if(L.elem!=NULL)
	{
	if(L.length==0) return TRUE;
	else return FALSE;
	}
	else return INFEASIBLE;
}
/*------------------------------------------
函数功能:求线性表表长
函数参数:线性表L
函数返回值:返回int类型的线性表长度
------------------------------------------*/
status ListLength(SqList L)
{
	if(L.elem!=NULL) return L.length;
	else return INFEASIBLE;
}
/*------------------------------------------
函数功能:得到线性表中的元素并将该元素赋值给e
函数参数:线性表L，元素的位置i，引用元素e的地址
函数返回值:返回int类型，获得成功返回1
------------------------------------------*/
status GetElem(SqList L,int i,ElemType &e)
{
	if(L.elem==NULL) return INFEASIBLE;
	else if(i<1||i>L.length) return ERROR;
	else
	{
	e=L.elem[i-1];
	return OK;
	}
}
/*------------------------------------------
函数功能:查找元素
函数参数:线性表L，待查找元素e
函数返回值:返回int类型，查找成功返回元素位置，否则返回ERROR
------------------------------------------*/
status LocateElem(SqList L,ElemType e)
{
	if(L.elem==NULL) return INFEASIBLE;
	else
	{
	for(int i=1;i<=L.length;i++)
		if(L.elem[i-1]==e) return i;
	return ERROR;
	}
}
/*------------------------------------------
函数功能:得到元素的直接前驱并赋值给pre
函数参数:线性表L，元素e，引用待返回元素的地址
函数返回值:返回int类型，得到前驱成功返回1
------------------------------------------*/
status PriorElem(SqList L,ElemType e,ElemType &pre)
{
	if(L.elem==NULL) return INFEASIBLE;
	else
	{
	for(int i=1;i<=L.length;i++)
	{//此处也可以直接调用LocateElem函数得到元素e的位置
	if(L.elem[i-1]==e)
	{
	if(i==1) return INFEASIBLE;
	else {pre=L.elem[i-2];return OK;}
	}
	}
	return ERROR;
	}
}
/*------------------------------------------
函数功能:得到元素的直接后继并赋值给next
函数参数:线性表L，元素e，引用待返回元素的地址
函数返回值:返回int类型，得到后继成功返回1
------------------------------------------*/
status NextElem(SqList L,ElemType e,ElemType &next)
{
	if(L.elem==NULL) return INFEASIBLE;
	else
	{
	for(int i=1;i<=L.length;i++)
	{
	if(L.elem[i-1]==e)
	{
	if(i==L.length) return INFEASIBLE;
	else {next=L.elem[i];return OK;}
	}
	}
	return ERROR;
	}
}
/*------------------------------------------
函数功能:插入元素在第i个元素前
函数参数:引用线性表L的地址，待插入元素元素e，待插入位置i
函数返回值:返回int类型，插入成功返回1
------------------------------------------*/
status ListInsert(SqList &L,int i,ElemType e)
{
	if(L.elem==NULL) return INFEASIBLE;
	else
	{
	if(i>L.length+1||i<=0) return ERROR;
	if(L.length==L.listsize)
	{
	ElemType *newbase=(ElemType*)realloc(L.elem,sizeof(ElemType)*(L.length+LISTINCREMENT));
	if(!newbase) exit(OVERFLOW);
	L.elem=newbase;
	L.listsize+=LISTINCREMENT;
	}
	for(int j=L.length;j>=i;j--) L.elem[j]=L.elem[j-1];
	L.elem[i-1]=e;
	L.length++;
	return OK;
	}
}
/*------------------------------------------
函数功能:删除第i个元素并得到被删除元素的值
函数参数:引用线性表L的地址，引用返回元素e的地址，待删除位置i
函数返回值:返回int类型，插入成功返回1
------------------------------------------*/
status ListDelete(SqList &L,int i,ElemType &e)
{
	if(L.elem==NULL) return INFEASIBLE;
	else
	{
	if(i>=L.length+1||i<=0) return ERROR;
	e=L.elem[i-1];
	for(int j=i;j<=L.length;j++) L.elem[j-1]=L.elem[j];
	L.length--;
	return OK;
	}
}
/*------------------------------------------
函数功能:遍历输出线性表中的元素
函数参数:线性表L的
函数返回值:返回int类型，遍历成功返回1
------------------------------------------*/
status ListTraverse(SqList L)
{
	if(L.elem==NULL) return INFEASIBLE;
	else
	{
	for(int i=1;i<=L.length;i++) printf("%d ",L.elem[i-1]);
	if(L.length==0) return ERROR;
	}
	return OK;
}
/*------------------------------------------
函数功能:保存线性表到指定文件中
函数参数:线性表L，待保存文件的路径FileName
函数返回值:返回int类型，保存成功返回1
------------------------------------------*/
status SaveList(SqList L,char FileName[])
{
	if(L.elem==NULL) return INFEASIBLE;
	else
	{
	FILE *fout=fopen(FileName,"w");
	if(fout==NULL) {printf("未成功打开文件");return ERROR;}
	for(int i=1;i<=L.length;i++)
		fprintf(fout,"%d ",L.elem[i-1]);
    fclose(fout);
	return OK;
	}
}
/*------------------------------------------
函数功能:加载文件到线性表中
函数参数:线性表L，待加载文件的路径FileName
函数返回值:返回int类型，加载成功返回1
------------------------------------------*/
status LoadList(SqList &L,char FileName[])
{
	if(L.elem!=NULL) return INFEASIBLE;
	else
	{
	L.elem=(ElemType*)malloc(sizeof(ElemType)*LIST_INIT_SIZE);
	FILE *fp=fopen(FileName,"r");
	if(fp==NULL) {printf("未成功打开文件");return ERROR;}
	int i=1,flag=0;
	L.length=0;
	L.listsize=LIST_INIT_SIZE;
	while(!feof(fp))
	{
	if(L.length==L.listsize)
	{
	ElemType *newbase=(ElemType*)realloc(L.elem,sizeof(ElemType)*(L.length+LISTINCREMENT));
	if(!newbase) exit(OVERFLOW);
	L.elem=newbase;
	L.listsize+=LISTINCREMENT;
	}
    fscanf(fp,"%d",&L.elem[i-1]);
	i++;
	L.length++;
	}
	L.length--;
	fclose(fp);
	return OK;
	}
}
/*------------------------------------------
函数功能:在线性表的管理表中插入一个新的线性表
函数参数:引用线性表的管理表Lists的地址，待插入线性表的名称FileName
函数返回值:返回int类型，插入成功返回1
------------------------------------------*/
status AddList(LISTS &Lists,char ListName[])
{
	strcpy(Lists.elem[Lists.length].name,ListName);
	Lists.elem[Lists.length].L.elem=(ElemType*)malloc(sizeof(ElemType)*LIST_INIT_SIZE);
	Lists.elem[Lists.length].L.listsize=LIST_INIT_SIZE;
	Lists.elem[Lists.length].L.length=0;
	Lists.length++;
	return  OK;
}
/*------------------------------------------
函数功能:在线性表的管理表中删除一个线性表
函数参数:引用线性表的管理表Lists的地址，待删除线性表的名称FileName
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
		Lists.elem[i-1].L.elem=Lists.elem[i].L.elem;
		Lists.elem[i-1].L.length=Lists.elem[i].L.length;
		Lists.elem[i-1].L.listsize=Lists.elem[i].L.listsize;
		}
		Lists.length--;
		return OK;
		}
	}
	return ERROR;
}
/*------------------------------------------
函数功能:在线性表的管理表中查找线性表
函数参数:线性表的管理表Lists，待查找线性表的名称FileName
函数返回值:返回int类型，查找成功返回该线性表的位置
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
