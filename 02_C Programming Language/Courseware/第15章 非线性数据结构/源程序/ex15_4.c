#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"
#define N 6
typedef struct _arcnode{ /*描述以i顶点为起点的边信息*/
	int adjvex;	/*该边所指顶点（终点）编号*/
	char *edge_info;	/*该边相关信息，如权值等*/
	struct _arcnode *next;
}arcnode;
arcnode *vex[N];/*邻接表指针数组，其i元素指向与i顶点相邻顶点构成的链表*/
void create(arcnode **p,int i);/*为每个顶点创建相邻顶点构成的后进先出链表*/
void show(int);/*遍历指针数组vex每个元素指向的单向链表*/
int main(void)
{	int i;
	for(i=0;i<N;i++)	
		create(&vex[i],i);
	show(N);
	return 0;
}
void create(arcnode **p,int i)
{	arcnode *head=NULL,*ptr; int num; char s[80];
	sprintf( s, "%d", i);/*将i值转换为字符串存放到s中*/
	strcat(s," vertice to ");/*连接字符串" vertice to "*/
	while(1){
		printf("输入与第%d个相邻的顶点编号，-1表示结束。\n",i);
		scanf("%d",&num);
		if(num==-1)
			break;/*当num为-1时，终止循环，当前链表创建完毕*/
		ptr=(arcnode *)malloc(sizeof(arcnode));/*分配链表结点存储*/
		ptr->edge_info=(char *)malloc(80*sizeof(char)); /*分配边信息描述存储*/
		ptr->next=head;/*新结点指向原链头*/
		ptr->adjvex=num;/*赋相邻顶点编号*/
		strcpy(ptr->edge_info,s); /*复制边信息描述*/
		head=ptr; /*新结点称为新的链头*/
	}
	*p=head;/*实际将头指针赋给vex[i]*/
}
void show(int n)
{	int i; arcnode *p;/*声明遍历指针*/
	for(i=0;i<N;i++){/*对指针数组的每个元素（链表头指针）*/
		p=vex[i];/*顶点i对应链表的头指针赋给p*/
		printf("顶点%d: %p*******\n",i,p);/*输出顶点编号和头指针值*/
		while(p){/*依次输出结点地址、边描述信息、相邻顶点编号、下一结点地址*/
			printf("%p,%s %d,%p\n",p,p->edge_info,p->adjvex,p->next);
			p=p->next;
		}
	}
}
