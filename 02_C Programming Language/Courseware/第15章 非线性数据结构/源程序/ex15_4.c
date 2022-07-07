#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"
#define N 6
typedef struct _arcnode{ /*������i����Ϊ���ı���Ϣ*/
	int adjvex;	/*�ñ���ָ���㣨�յ㣩���*/
	char *edge_info;	/*�ñ������Ϣ����Ȩֵ��*/
	struct _arcnode *next;
}arcnode;
arcnode *vex[N];/*�ڽӱ�ָ�����飬��iԪ��ָ����i�������ڶ��㹹�ɵ�����*/
void create(arcnode **p,int i);/*Ϊÿ�����㴴�����ڶ��㹹�ɵĺ���ȳ�����*/
void show(int);/*����ָ������vexÿ��Ԫ��ָ��ĵ�������*/
int main(void)
{	int i;
	for(i=0;i<N;i++)	
		create(&vex[i],i);
	show(N);
	return 0;
}
void create(arcnode **p,int i)
{	arcnode *head=NULL,*ptr; int num; char s[80];
	sprintf( s, "%d", i);/*��iֵת��Ϊ�ַ�����ŵ�s��*/
	strcat(s," vertice to ");/*�����ַ���" vertice to "*/
	while(1){
		printf("�������%d�����ڵĶ����ţ�-1��ʾ������\n",i);
		scanf("%d",&num);
		if(num==-1)
			break;/*��numΪ-1ʱ����ֹѭ������ǰ���������*/
		ptr=(arcnode *)malloc(sizeof(arcnode));/*����������洢*/
		ptr->edge_info=(char *)malloc(80*sizeof(char)); /*�������Ϣ�����洢*/
		ptr->next=head;/*�½��ָ��ԭ��ͷ*/
		ptr->adjvex=num;/*�����ڶ�����*/
		strcpy(ptr->edge_info,s); /*���Ʊ���Ϣ����*/
		head=ptr; /*�½���Ϊ�µ���ͷ*/
	}
	*p=head;/*ʵ�ʽ�ͷָ�븳��vex[i]*/
}
void show(int n)
{	int i; arcnode *p;/*��������ָ��*/
	for(i=0;i<N;i++){/*��ָ�������ÿ��Ԫ�أ�����ͷָ�룩*/
		p=vex[i];/*����i��Ӧ�����ͷָ�븳��p*/
		printf("����%d: %p*******\n",i,p);/*��������ź�ͷָ��ֵ*/
		while(p){/*�����������ַ����������Ϣ�����ڶ����š���һ����ַ*/
			printf("%p,%s %d,%p\n",p,p->edge_info,p->adjvex,p->next);
			p=p->next;
		}
	}
}
