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
typedef struct LNode{  //��������ʽ�ṹ�����Ķ���
      ElemType data;
      struct LNode *next;
}LNode,*LinkList;
typedef struct{  //������Ĺ������
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
	printf("��ѡ����Ĳ���[0~17]:");
	scanf("%d",&op);
    switch(op){
	   case 1:
		 res=InitList(L);
		 if(res==OK) printf("���������ɹ�");
		 else if(res==INFEASIBLE) printf("�������Ѵ���");
		 else printf("��������ʧ��");
		 getchar();getchar();
		 break;
	   case 2:
		 res=DestroyList(L);
		 if(res==OK)
		 {
		 if(L) printf("����������ʧ��");
         else printf("���������ٳɹ�");
		 }
         else if(res==INFEASIBLE) printf("������δ��������������");
		 else printf("����������ʧ��");
		 getchar();getchar();
		 break;
	   case 3:
		 res=ClearList(L);
		 if(res==INFEASIBLE) printf("������δ����,");
		 if (!L) printf("���������ʧ��");
		 if (res==OK) printf("����������ɹ�");
		 getchar();getchar();
		 break;
	   case 4:
		 res=ListEmpty(L);
		 if (res==TRUE) printf("������Ϊ�ձ�");
		 else if(res==FALSE)printf("������Ϊ�ձ�");
		 else printf("������δ����");
		 getchar();getchar();
		 break;
	   case 5:
		 res=ListLength(L);
		 if(res!=-1) printf("������ĳ���Ϊ%d",ListLength(L));
		 else printf("������δ����");
		 getchar();getchar();
		 break;
	   case 6:
	   	 int pos,e;
         printf("������Ԫ��λ��:");
         scanf("%d",&pos);
         res=GetElem(L,pos,e);
		 if(res==OK)printf("�������е�%d��Ԫ����%d",pos,e);
		 else if(res==ERROR) printf("����λ�ò��Ϸ�");
		 else printf("������δ����");
		 getchar();getchar();
		 break;
	   case 7:
		 int data;
		 printf("������Ԫ��:");
         scanf("%d",&data);
         res=LocateElem(L,data);
		 if(res!=ERROR) printf("��������Ԫ��%d��λ����%d",data,LocateElem(L,data));
		 else if(res==ERROR)printf("��Ԫ�ز��ڵ�������");
		 else printf("������δ����");
		 getchar();getchar();
		 break;
	   case 8:
		 int data1,pre;
		 printf("������Ԫ��:");
         scanf("%d",&data1);
         res=PriorElem(L,data1,pre);
		 if(res==INFEASIBLE)printf("��Ԫ����ֱ��ǰ��");
		 else if(res!=ERROR)printf("��������Ԫ��%d��ֱ��ǰ��Ԫ����%d",data1,pre);
		 else printf("��Ԫ�ز��ڵ�������");
		 getchar();getchar();
		 break;
	   case 9:
		 int data2,next;
		 printf("������Ԫ��:");
         scanf("%d",&data2);
         res=NextElem(L,data2,next);
		 if(res==INFEASIBLE) printf("��Ԫ����ֱ�Ӻ��");
		 else if(res!=ERROR)printf("��������Ԫ��%d��ֱ�Ӻ��Ԫ����%d\n",data2,next);
		 else printf("��Ԫ�ز��ڵ�������");
		 getchar();getchar();
		 break;
	   case 10:
		 int data3,pos1;
		 printf("����������Ԫ�ؼ������λ��:");
		 scanf("%d%d",&data3,&pos1);
		 res=ListInsert(L,pos1,data3);
		 if(res&&res!=INFEASIBLE)printf("����Ԫ�سɹ�����ǰ������ĳ���Ϊ%d",ListLength(L));
		 else if(res==ERROR) printf("Ԫ��λ�ò��Ϸ�");
		 else printf("������δ����");
		 getchar();getchar();
		 break;
	   case 11:
		 int data4,pos2;
		 printf("������ɾ����Ԫ��λ��:");
		 scanf("%d",&pos2);
		 res=ListDelete(L,pos2,data4);
		 if(res&&res!=INFEASIBLE)printf("ɾ��Ԫ�سɹ�����ɾ��Ԫ��Ϊ%d����ǰ������ĳ���Ϊ%d",data4,ListLength(L));
		 else if(res==ERROR) printf("Ԫ��λ�ò��Ϸ�");
		 else printf("������δ����");
		 getchar();getchar();
		 break;
	   case 12:
		 res=ListTraverse(L);
		 if(!res) printf("�������ǿձ�");
		 else if(res==INFEASIBLE) printf("������δ����");
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
		 if(res) printf("�ļ��ɹ���������ǰ������\n");
		 else printf("��ǰ������δ���٣����ܽ��м��ز���");
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
      		ListInsert(Lists.elem[Lists.length-1].L,ListLength(Lists.elem[Lists.length-1].L)+1,e1);
      		fscanf(fp,"%d",&e1);
         }
         }
		 }
		 fclose(fp);
         printf("���뵥�������\n��ǰ�����Ϊ:\n");
	     }
		 else
		 {
		 printf("������Ҫ��ӵĵ��������:");
	     scanf("%d",&n);
		 printf("���������뵥�������ƺ͵�����Ԫ��:");
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
         printf("���뵥�������\n��ǰ�����Ϊ:\n");
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
		 printf("������Ҫɾ���ĵ���������:");
		 scanf("%s",check);
		 if (RemoveList(Lists,check)==OK)
	     for(int n=0;n<Lists.length;n++)
   		 {
   			printf("%s ",Lists.elem[n].name);
   			ListTraverse(Lists.elem[n].L);
        	putchar('\n');
   		 }
         else printf("ɾ��������ʧ��");
		 getchar();getchar();
		 break;
	   case 17:
		 char check1[30];
		 printf("������Ҫ���ҵĵ���������:");
		 scanf("%s",check1);
		 if(n=LocateList(Lists,check1))
   		 {
   			printf("%s ",Lists.elem[n-1].name);
   			ListTraverse(Lists.elem[n-1].L);
         putchar('\n');
   		 }
         else printf("�õ������ڴ˹������");
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
��������:��ʼ��������
��������:���õ�����L�ĵ�ַ
��������ֵ:����int���ͣ������ɹ�����1
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
��������:���ٵ�����
��������:���õ�����L�ĵ�ַ
��������ֵ:����int���ͣ����ٳɹ�����1
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
��������:��յ�����
��������:���õ�����L�ĵ�ַ
��������ֵ:����int���ͣ���ճɹ�����1
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
��������:�������п�
��������:������L
��������ֵ:����int���ͣ�������Ϊ�շ���1
------------------------------------------*/
status ListEmpty(LinkList L)
{
	if(L!=NULL&&L->next==NULL) return TRUE;
	else if(L==NULL)return INFEASIBLE;
	else return FALSE;
}
/*------------------------------------------
��������:�������
��������:������L
��������ֵ:����int���͵ĵ�������
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
��������:�õ��������е�Ԫ�ز�����Ԫ�ظ�ֵ��e
��������:������L��Ԫ�ص�λ��i������Ԫ��e�ĵ�ַ
��������ֵ:����int���ͣ���óɹ�����1
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
��������:����Ԫ��
��������:������L��������Ԫ��e
��������ֵ:����int���ͣ����ҳɹ�����Ԫ��λ�ã����򷵻�ERROR
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
��������:�õ�Ԫ�ص�ֱ��ǰ������ֵ��pre
��������:������L��Ԫ��e�����ô�����Ԫ�صĵ�ַ
��������ֵ:����int���ͣ��õ�ǰ���ɹ�����1
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
��������:�õ�Ԫ�ص�ֱ�Ӻ�̲���ֵ��next
��������:������L��Ԫ��e�����ô�����Ԫ�صĵ�ַ
��������ֵ:����int���ͣ��õ���̳ɹ�����1
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
��������:����Ԫ���ڵ�i��Ԫ��ǰ
��������:���õ�����L�ĵ�ַ��������Ԫ��Ԫ��e��������λ��i
��������ֵ:����int���ͣ�����ɹ�����1
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
��������:ɾ����i��Ԫ�ز��õ���ɾ��Ԫ�ص�ֵ
��������:���õ�����L�ĵ�ַ�����÷���Ԫ��e�ĵ�ַ����ɾ��λ��i
��������ֵ:����int���ͣ�����ɹ�����1
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
��������:��������������е�Ԫ��
��������:������L��
��������ֵ:����int���ͣ������ɹ�����1
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
��������:���浥����ָ���ļ���
��������:������L���������ļ���·��FileName
��������ֵ:����int���ͣ�����ɹ�����1
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
��������:�����ļ�����������
��������:������L���������ļ���·��FileName
��������ֵ:����int���ͣ����سɹ�����1
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
��������:�ڵ�����Ĺ�����в���һ���µĵ�����
��������:���õ�����Ĺ����Lists�ĵ�ַ�������뵥���������FileName
��������ֵ:����int���ͣ�����ɹ�����1
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
��������:�ڵ�����Ĺ������ɾ��һ��������
��������:���õ�����Ĺ����Lists�ĵ�ַ����ɾ�������������FileName
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
		Lists.elem[i-1].L=Lists.elem[i].L;
		}
		Lists.length--;
		return OK;
		}
	}
	return ERROR;
}
/*------------------------------------------
��������:�ڵ�����Ĺ�����в��ҵ�����
��������:������Ĺ����Lists�������ҵ����������FileName
��������ֵ:����int���ͣ����ҳɹ����ظõ������λ��
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
