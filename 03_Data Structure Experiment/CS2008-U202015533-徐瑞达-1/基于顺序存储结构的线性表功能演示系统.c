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
typedef int ElemType; //����Ԫ�����Ͷ���
typedef struct{  //˳���˳��ṹ���Ķ���
	ElemType * elem;
	int length;
	int listsize;
}SqList;
typedef struct{ //���Ա�Ĺ������
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
	printf("��ѡ����Ĳ���[0~17]:");
	scanf("%d",&op);
    switch(op){
	   case 1:
		 res=InitList(L);
		 if(res==OK) printf("���Ա����ɹ�");
		 else if(res==INFEASIBLE) printf("���Ա��Ѵ���");
		 else printf("���Ա���ʧ��");
		 getchar();getchar();
		 break;
	   case 2:
		 res=DestroyList(L);
		 if(res==OK)
		 {
		 if(L.elem) printf("���Ա�����ʧ��");
         else printf("���Ա����ٳɹ�");
		 }
         else if(res==INFEASIBLE) printf("���Ա�δ��������������");
		 else printf("���Ա�����ʧ��");
		 getchar();getchar();
		 break;
	   case 3:
		 res=ClearList(L);
		 if (L.length||(!L.elem)) printf("���Ա����ʧ��");
		 if (res==OK) printf("���Ա�����ɹ�");
		 if(res==INFEASIBLE) printf("���Ա�δ����");
		 getchar();getchar();
		 break;
	   case 4:
		 res=ListEmpty(L);
		 if (res==TRUE) printf("���Ա�Ϊ�ձ�");
		 else if(res==FALSE)printf("���Ա�Ϊ�ձ�");
		 else printf("���Ա�δ����");
		 getchar();getchar();
		 break;
	   case 5:
		 res=ListLength(L);
		 if(res==L.length) printf("���Ա�ĳ���Ϊ%d",ListLength(L));
		 else printf("���Ա�δ����");
		 getchar();getchar();
		 break;
	   case 6:
	   	 int pos,e;
         printf("������Ԫ��λ��:");
         scanf("%d",&pos);
         res=GetElem(L,pos,e);
		 if(res==OK)printf("���Ա��е�%d��Ԫ����%d",pos,e);
		 else if(res==ERROR) printf("����λ�ò��Ϸ�");
		 else printf("���Ա�δ����");
		 getchar();getchar();
		 break;
	   case 7:
		 int data;
		 printf("������Ԫ��:");
         scanf("%d",&data);
         res=LocateElem(L,data);
		 if(res!=ERROR) printf("���Ա���Ԫ��%d��λ����%d",data,LocateElem(L,data));
		 else if(res==ERROR)printf("��Ԫ�ز������Ա���");
		 else printf("���Ա�δ����");
		 getchar();getchar();
		 break;
	   case 8:
		 int data1,pre;
		 printf("������Ԫ��:");
         scanf("%d",&data1);
         res=PriorElem(L,data1,pre);
		 if(res==INFEASIBLE)printf("��Ԫ����ֱ��ǰ��");
		 else if(res!=ERROR)printf("���Ա���Ԫ��%d��ֱ��ǰ��Ԫ����%d",data1,pre);
		 else printf("��Ԫ�ز������Ա���");
		 getchar();getchar();
		 break;
	   case 9:
		 int data2,next;
		 printf("������Ԫ��:");
         scanf("%d",&data2);
         res=NextElem(L,data2,next);
		 if(res==INFEASIBLE) printf("��Ԫ����ֱ�Ӻ��");
		 else if(res!=ERROR)printf("���Ա���Ԫ��%d��ֱ�Ӻ��Ԫ����%d\n",data2,next);
		 else printf("��Ԫ�ز������Ա���");
		 getchar();getchar();
		 break;
	   case 10:
		 int data3,pos1;
		 printf("����������Ԫ�ؼ������λ��:");
		 scanf("%d%d",&data3,&pos1);
		 res=ListInsert(L,pos1,data3);
		 if(res&&res!=INFEASIBLE)printf("����Ԫ�سɹ�����ǰ���Ա�ĳ���Ϊ%d",ListLength(L));
		 else if(res==ERROR) printf("Ԫ��λ�ò��Ϸ�");
		 else printf("���Ա�δ����");
		 getchar();getchar();
		 break;
	   case 11:
		 int data4,pos2;
		 printf("������ɾ����Ԫ��λ��:");
		 scanf("%d",&pos2);
		 res=ListDelete(L,pos2,data4);
		 if(res&&res!=INFEASIBLE)printf("ɾ��Ԫ�سɹ�����ɾ��Ԫ��Ϊ%d����ǰ���Ա�ĳ���Ϊ%d",data4,ListLength(L));
		 else if(res==ERROR) printf("Ԫ��λ�ò��Ϸ�");
		 else printf("���Ա�δ����");
		 getchar();getchar();
		 break;
	   case 12:
		 res=ListTraverse(L);
		 if(!res) printf("���Ա��ǿձ�");
		 else if(res==INFEASIBLE) printf("���Ա�δ����");
		 getchar();getchar();
		 break;
	   case 13:
		 char FileName[30];
		 printf("�������ļ�����·�����ļ���:");
		 scanf("%s",FileName);
		 res=SaveList(L,FileName);
		 if(res) printf("�ļ��ɹ�������%s\n",FileName);
		 getchar();getchar();
		 break;
	   case 14:
		 char FileName1[30];
		 printf("������������ļ�·�����ļ���:");
		 scanf("%s",FileName1);
		 res=LoadList(L,FileName1);
		 if(res) printf("�ļ��ɹ���������ǰ���Ա�\n");
		 else printf("��ǰ���Ա�δ���٣����ܽ��м��ز���");
		 getchar();getchar();
		 break;
	   case 15:
		 int n,e1,f;
         char name[30];
         Lists.length=0;
         printf("��ѡ����ļ�����(0)���������(1)��");
         scanf("%d",&f);
         if(!f)
         {
		 char FileName2[50];
		 printf("������������ļ�·�����ļ���:");
		 scanf("%s",FileName2);
		 FILE *fp=fopen(FileName2,"r");
		 if(fp==NULL) printf("δ�ɹ����ļ�");
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
         printf("�������Ա����\n��ǰ�����Ϊ:\n");
	     }
		 else
		 {
		 printf("������Ҫ��ӵ����Ա����:");
	     scanf("%d",&n);
		 printf("�������������Ա����ƺ����Ա�Ԫ��:");
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
         printf("�������Ա����\n��ǰ�����Ϊ:\n");
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
		 printf("������Ҫɾ�������Ա�����:");
		 scanf("%s",check);
		 if (RemoveList(Lists,check)==OK)
	     for(int n=0;n<Lists.length;n++)
   		 {
   			printf("%s ",Lists.elem[n].name);
   			ListTraverse(Lists.elem[n].L);
        	putchar('\n');
   		 }
         else printf("ɾ�����Ա�ʧ��");
		 getchar();getchar();
		 break;
	   case 17:
		 char check1[30];
		 printf("������Ҫ���ҵ����Ա�����:");
		 scanf("%s",check1);
		 if(n=LocateList(Lists,check1))
   		 {
   			printf("%s ",Lists.elem[n-1].name);
   			ListTraverse(Lists.elem[n-1].L);
         putchar('\n');
   		 }
         else printf("�����Ա��ڴ˹������");
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
��������:��ʼ�����Ա�
��������:�������Ա�L�ĵ�ַ
��������ֵ:����int���ͣ������ɹ�����1
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
��������:�������Ա�
��������:�������Ա�L�ĵ�ַ
��������ֵ:����int���ͣ����ٳɹ�����1
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
��������:������Ա�
��������:�������Ա�L�ĵ�ַ
��������ֵ:����int���ͣ���ճɹ�����1
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
��������:���Ա��п�
��������:���Ա�L
��������ֵ:����int���ͣ����Ա�Ϊ�շ���1
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
��������:�����Ա��
��������:���Ա�L
��������ֵ:����int���͵����Ա���
------------------------------------------*/
status ListLength(SqList L)
{
	if(L.elem!=NULL) return L.length;
	else return INFEASIBLE;
}
/*------------------------------------------
��������:�õ����Ա��е�Ԫ�ز�����Ԫ�ظ�ֵ��e
��������:���Ա�L��Ԫ�ص�λ��i������Ԫ��e�ĵ�ַ
��������ֵ:����int���ͣ���óɹ�����1
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
��������:����Ԫ��
��������:���Ա�L��������Ԫ��e
��������ֵ:����int���ͣ����ҳɹ�����Ԫ��λ�ã����򷵻�ERROR
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
��������:�õ�Ԫ�ص�ֱ��ǰ������ֵ��pre
��������:���Ա�L��Ԫ��e�����ô�����Ԫ�صĵ�ַ
��������ֵ:����int���ͣ��õ�ǰ���ɹ�����1
------------------------------------------*/
status PriorElem(SqList L,ElemType e,ElemType &pre)
{
	if(L.elem==NULL) return INFEASIBLE;
	else
	{
	for(int i=1;i<=L.length;i++)
	{//�˴�Ҳ����ֱ�ӵ���LocateElem�����õ�Ԫ��e��λ��
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
��������:�õ�Ԫ�ص�ֱ�Ӻ�̲���ֵ��next
��������:���Ա�L��Ԫ��e�����ô�����Ԫ�صĵ�ַ
��������ֵ:����int���ͣ��õ���̳ɹ�����1
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
��������:����Ԫ���ڵ�i��Ԫ��ǰ
��������:�������Ա�L�ĵ�ַ��������Ԫ��Ԫ��e��������λ��i
��������ֵ:����int���ͣ�����ɹ�����1
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
��������:ɾ����i��Ԫ�ز��õ���ɾ��Ԫ�ص�ֵ
��������:�������Ա�L�ĵ�ַ�����÷���Ԫ��e�ĵ�ַ����ɾ��λ��i
��������ֵ:����int���ͣ�����ɹ�����1
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
��������:����������Ա��е�Ԫ��
��������:���Ա�L��
��������ֵ:����int���ͣ������ɹ�����1
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
��������:�������Ա�ָ���ļ���
��������:���Ա�L���������ļ���·��FileName
��������ֵ:����int���ͣ�����ɹ�����1
------------------------------------------*/
status SaveList(SqList L,char FileName[])
{
	if(L.elem==NULL) return INFEASIBLE;
	else
	{
	FILE *fout=fopen(FileName,"w");
	if(fout==NULL) {printf("δ�ɹ����ļ�");return ERROR;}
	for(int i=1;i<=L.length;i++)
		fprintf(fout,"%d ",L.elem[i-1]);
    fclose(fout);
	return OK;
	}
}
/*------------------------------------------
��������:�����ļ������Ա���
��������:���Ա�L���������ļ���·��FileName
��������ֵ:����int���ͣ����سɹ�����1
------------------------------------------*/
status LoadList(SqList &L,char FileName[])
{
	if(L.elem!=NULL) return INFEASIBLE;
	else
	{
	L.elem=(ElemType*)malloc(sizeof(ElemType)*LIST_INIT_SIZE);
	FILE *fp=fopen(FileName,"r");
	if(fp==NULL) {printf("δ�ɹ����ļ�");return ERROR;}
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
��������:�����Ա�Ĺ�����в���һ���µ����Ա�
��������:�������Ա�Ĺ����Lists�ĵ�ַ�����������Ա������FileName
��������ֵ:����int���ͣ�����ɹ�����1
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
��������:�����Ա�Ĺ������ɾ��һ�����Ա�
��������:�������Ա�Ĺ����Lists�ĵ�ַ����ɾ�����Ա������FileName
��������ֵ:����int���ͣ�ɾ���ɹ�����1
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
��������:�����Ա�Ĺ�����в������Ա�
��������:���Ա�Ĺ����Lists�����������Ա������FileName
��������ֵ:����int���ͣ����ҳɹ����ظ����Ա��λ��
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
