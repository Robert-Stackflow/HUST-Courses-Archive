#include <stdio.h>
#include "stdlib.h"
#define MAX_ROW 5		/*最大行数*/
#define MAX_COL 5		/*最大列数*/
#define	N	4			/*方向数*/
void print_maze(void);			/*打印迷宫*/
void visit(int row, int col);	/*结点访问函数*/
void enqueue(struct point *p);	/*入队操作函数*/
struct point *dequeue(void);	/*出队操作函数*/
int is_empty(void);				/*测试队列是否为空函数*/
struct point		/*定义路径结点数据结构*/
{
    int row, col;		/*行，列*/
	int flag;			/*访问标志*/
	struct point *predecessor;	/*前驱结点指针*/
	struct point *next;			/*后继结点指针*/
} node,*pnode;
struct point *front0 = NULL,*front = NULL, *rear = NULL;
int maze[MAX_ROW][MAX_COL] = {	/*5×5方格的迷宫数组*/
     0, 1, 1, 0, 0,
     0, 0, 1, 1, 1,
     0, 0, 0, 0, 0,
     1, 0, 1, 1, 0,
     0, 1, 0, 0, 0
};
/*四方向数数组,依次为上、下、左、右*/
int stepx[N]={ 0, 0, -1, 1};
int stepy[N]={-1, 1,  0, 0};
int n=2;	/*访问步骤*/
int main()
{    struct point *p;
	 int i;
	 p=(struct point *)malloc(sizeof(struct point));/*创建新结点*/
	 p->col=0;	/*列成员取迷宫起始格列下标值*/
	 p->row=0;	/*行成员取迷宫起始格行下标值*/
	 p->flag=0;	/*置未处理标志*/
	 p->next=NULL;	/*置后继结点指针为空*/
	 p->predecessor=NULL;/*上面6句创建与(0,0)对应的起始访问结点*/
     maze[p->row][p->col] = 2; /*2表示访问迷宫的入口*/
	 front0=p;		/*链表头指针指向起始访问结点*/
     enqueue(p);	/*将起始访问结点加入队列*/
     while (!is_empty()){ /*当队列中有可访问结点则继续循环执行*/
		 p=dequeue();	/*p指向出队结点*/
		 n++;			/*访问步骤加1*/
		 if(p->row==MAX_ROW-1&&p->col==MAX_COL - 1)	/*如果达到出口，停止循环*/
				 break;
		 for(i=0;i<N;i++){		/*对4方向中的每个方向，进行下列操作*/
			 if(p->row+stepy[i]<0 || p->col+stepx[i]<0)	/*防止下越界*/
				 continue;
			 if(p->row+stepy[i]<MAX_ROW && p->col+stepx[i]<MAX_COL/*防止上越界*/
			&& maze[p->row+stepy[i]][p->col+stepx[i]] == 0)	/*且方格可通过*/
					visit(p->row+stepy[i],p->col+stepx[i]);	/*访问迷宫方格*/
		 }
	 }
	 if (p->row == MAX_ROW - 1 && p->col == MAX_COL - 1)
     { /*到达目标结点，打印输出搜索过程*/
		print_maze();/*先打印迷宫*/
		p=front0;/*初始化遍历指针*/
		while(p!=NULL){
			printf("(%d, %d)\t%p\n", p->row, p->col,p);/* 遍历输出搜索过程*/
			p=p->next;
		}
	 } else printf("No path!\n");/*没有到达出口目标的路径*/
     return 0;
}
void enqueue(struct point *p)/*入队操作函数*/
{	if(rear==NULL){	/*入队操作尾指针处理*/
		rear=p;
	}
	else{
		rear->next=p;
		rear=rear->next;
	}
	if(front==NULL)	front=p;/*入队操作头指针处理*/
}
struct point *dequeue(void)/*出队操作函数*/
{	struct point *p=front; 
	if(front!=NULL){
		front->flag=1;/*置处理过标志*/
		front=front->next;
	}
    return p;
}
int is_empty(void)/*测试队列是否为空函数*/
{	/*front==rear仅仅表示队列中仅有一个结点，如果front->flag==1才表示该*/
	return (front==rear && front->flag);/*结点已经处理,队列为空队列*/
}
void print_maze(void)/*打印迷宫函数*/
{	 int i, j;
     for (i = 0; i < MAX_ROW; i++){
         for (j = 0; j < MAX_COL; j++)
              printf("%3d ", maze[i][j]);
         putchar('\n');
     }
}
void visit(int row, int col)/*结点访问函数*/
{    struct point *p;
	 maze[row][col] = n;/*置访问步骤*/
	 p=(struct point *)malloc(sizeof(struct point));/*创建新结点*/
	 p->col=col;	/*列成员取迷宫起始格列下标值*/
	 p->row=row;	/*行成员取迷宫起始格行下标值*/
	 p->flag=0;	/*置未处理标志*/
	 p->predecessor=rear;	/*置前驱结点指针为空*/
	 p->next=NULL;	/*置后继结点指针为空*/
     enqueue(p);	/*将新创建结点加入队列*/
}
