#include <stdio.h>
#include "stdlib.h"
#define MAX_ROW 5		/*�������*/
#define MAX_COL 5		/*�������*/
#define	N	4			/*������*/
void print_maze(void);			/*��ӡ�Թ�*/
void visit(int row, int col);	/*�����ʺ���*/
void enqueue(struct point *p);	/*��Ӳ�������*/
struct point *dequeue(void);	/*���Ӳ�������*/
int is_empty(void);				/*���Զ����Ƿ�Ϊ�պ���*/
struct point		/*����·��������ݽṹ*/
{
    int row, col;		/*�У���*/
	int flag;			/*���ʱ�־*/
	struct point *predecessor;	/*ǰ�����ָ��*/
	struct point *next;			/*��̽��ָ��*/
} node,*pnode;
struct point *front0 = NULL,*front = NULL, *rear = NULL;
int maze[MAX_ROW][MAX_COL] = {	/*5��5������Թ�����*/
     0, 1, 1, 0, 0,
     0, 0, 1, 1, 1,
     0, 0, 0, 0, 0,
     1, 0, 1, 1, 0,
     0, 1, 0, 0, 0
};
/*�ķ���������,����Ϊ�ϡ��¡�����*/
int stepx[N]={ 0, 0, -1, 1};
int stepy[N]={-1, 1,  0, 0};
int n=2;	/*���ʲ���*/
int main()
{    struct point *p;
	 int i;
	 p=(struct point *)malloc(sizeof(struct point));/*�����½��*/
	 p->col=0;	/*�г�Աȡ�Թ���ʼ�����±�ֵ*/
	 p->row=0;	/*�г�Աȡ�Թ���ʼ�����±�ֵ*/
	 p->flag=0;	/*��δ�����־*/
	 p->next=NULL;	/*�ú�̽��ָ��Ϊ��*/
	 p->predecessor=NULL;/*����6�䴴����(0,0)��Ӧ����ʼ���ʽ��*/
     maze[p->row][p->col] = 2; /*2��ʾ�����Թ������*/
	 front0=p;		/*����ͷָ��ָ����ʼ���ʽ��*/
     enqueue(p);	/*����ʼ���ʽ��������*/
     while (!is_empty()){ /*���������пɷ��ʽ�������ѭ��ִ��*/
		 p=dequeue();	/*pָ����ӽ��*/
		 n++;			/*���ʲ����1*/
		 if(p->row==MAX_ROW-1&&p->col==MAX_COL - 1)	/*����ﵽ���ڣ�ֹͣѭ��*/
				 break;
		 for(i=0;i<N;i++){		/*��4�����е�ÿ�����򣬽������в���*/
			 if(p->row+stepy[i]<0 || p->col+stepx[i]<0)	/*��ֹ��Խ��*/
				 continue;
			 if(p->row+stepy[i]<MAX_ROW && p->col+stepx[i]<MAX_COL/*��ֹ��Խ��*/
			&& maze[p->row+stepy[i]][p->col+stepx[i]] == 0)	/*�ҷ����ͨ��*/
					visit(p->row+stepy[i],p->col+stepx[i]);	/*�����Թ�����*/
		 }
	 }
	 if (p->row == MAX_ROW - 1 && p->col == MAX_COL - 1)
     { /*����Ŀ���㣬��ӡ�����������*/
		print_maze();/*�ȴ�ӡ�Թ�*/
		p=front0;/*��ʼ������ָ��*/
		while(p!=NULL){
			printf("(%d, %d)\t%p\n", p->row, p->col,p);/* ���������������*/
			p=p->next;
		}
	 } else printf("No path!\n");/*û�е������Ŀ���·��*/
     return 0;
}
void enqueue(struct point *p)/*��Ӳ�������*/
{	if(rear==NULL){	/*��Ӳ���βָ�봦��*/
		rear=p;
	}
	else{
		rear->next=p;
		rear=rear->next;
	}
	if(front==NULL)	front=p;/*��Ӳ���ͷָ�봦��*/
}
struct point *dequeue(void)/*���Ӳ�������*/
{	struct point *p=front; 
	if(front!=NULL){
		front->flag=1;/*�ô������־*/
		front=front->next;
	}
    return p;
}
int is_empty(void)/*���Զ����Ƿ�Ϊ�պ���*/
{	/*front==rear������ʾ�����н���һ����㣬���front->flag==1�ű�ʾ��*/
	return (front==rear && front->flag);/*����Ѿ�����,����Ϊ�ն���*/
}
void print_maze(void)/*��ӡ�Թ�����*/
{	 int i, j;
     for (i = 0; i < MAX_ROW; i++){
         for (j = 0; j < MAX_COL; j++)
              printf("%3d ", maze[i][j]);
         putchar('\n');
     }
}
void visit(int row, int col)/*�����ʺ���*/
{    struct point *p;
	 maze[row][col] = n;/*�÷��ʲ���*/
	 p=(struct point *)malloc(sizeof(struct point));/*�����½��*/
	 p->col=col;	/*�г�Աȡ�Թ���ʼ�����±�ֵ*/
	 p->row=row;	/*�г�Աȡ�Թ���ʼ�����±�ֵ*/
	 p->flag=0;	/*��δ�����־*/
	 p->predecessor=rear;	/*��ǰ�����ָ��Ϊ��*/
	 p->next=NULL;	/*�ú�̽��ָ��Ϊ��*/
     enqueue(p);	/*���´������������*/
}
