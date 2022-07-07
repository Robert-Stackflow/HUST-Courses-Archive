#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define VERTEX_MAX 26   /*图的最大顶点数*/   
#define MAXVALUE 32767 /*最大值(可设为一个最大整数)*/
#define QUEUE_MAXSIZE 30 /*队列的最大容量*/
#define VERTEX_NUM 7 /*顶点数*/
#define EDGE_NUM 9	/*边数*/
typedef struct
{
    char Vertex[VERTEX_MAX]; /*保存顶点信息(序号或字母)*/
    int Edges[VERTEX_MAX][VERTEX_MAX]; /*保存边的权*/ 
    int visited[VERTEX_MAX]; /*遍历标志 */
    int VertexNum; /*顶点数量*/ 
    int EdgeNum;/*边数量*/   
}MatrixGraph; /*定义邻接矩阵图结构*/ 
typedef struct
{
    int Data[QUEUE_MAXSIZE]; /*数据域*/
    int head; /*队头指针*/
    int tail; /*队尾指针*/
}SeqQueue; /*队列结构*/

typedef struct _PATH
{
	int path[VERTEX_MAX];
	int p_top;
	struct _PATH *next;
}PATH,*PPATH;
PPATH head=NULL;
int stack[VERTEX_MAX];
int s_top=0;

void initqueue(SeqQueue *q); /*初始化一个队列*/   
int empty(SeqQueue q); /*判断队列是否空*/   
int enqueue(SeqQueue *q,int n); /*将一个元素入队列*/   
int dequeue(SeqQueue *q,int *p); /*将一个元素出队列*/  
void DFS(MatrixGraph *G,int);
void BFS(MatrixGraph *G,int);/*广度优先遍历*/ 
void create_matrix_graph(MatrixGraph *G);/*创建邻接矩阵图*/ 
void show_matrix(MatrixGraph *G); /*输出邻接矩阵*/
void DFSv2(MatrixGraph *G,int b,int e);
void push(int n);
int pop(void);
void show_path(int b,int e);

void create_matrix_graph(MatrixGraph *G)/*创建邻接矩阵图*/ 
{
    int i,j,k,weight;
    char start,end; /*边的起始顶点*/ 	
	char v[VERTEX_NUM]={'0','1','2','3','4','5','6'};/*顶点数组*/
	char e[EDGE_NUM][2]={{'0','1'},{'0','3'},{'1','2'},{'1','4'},
		{'2','3'},{'2','4'},{'2','5'},{'3','4'},{'3','6'}};/*边数组*/
	int w[9]={1,1,1,1,1,1,1,1,1};/*权值数组*/
    for(i=0;i<G->VertexNum;i++) /*输入顶点*/ 
		G->Vertex[i]=v[i];
	for(k=0;k<G->EdgeNum;k++)  /*输入边的信息*/ 
	{
		start=e[k][0];
		end=e[k][1];
		weight=w[k];
		for(i=0;start!=G->Vertex[i];i++); /*在已有顶点中查找始点*/ 
		for(j=0;end!=G->Vertex[j];j++); /*在已有顶点中查找结终点*/ 
			G->Edges[i][j]=weight; /*对应位置保存权值，表示有一条边*/
		G->Edges[j][i]=weight;/*在对角位置保存权值*/  
	}
}
void show_matrix(MatrixGraph *G)/*输出邻接矩阵*/ 
{
    int i,j;
    for(j=0;j<G->VertexNum;j++)
        printf("\t%c",G->Vertex[j]);    /*在第1行输出顶点信息*/ 
    printf("\n");
    for(i=0;i<G->VertexNum;i++) 
    {
        printf("%c",G->Vertex[i]);
        for(j=0;j<G->VertexNum;j++)
        {
            if(G->Edges[i][j]==MAXVALUE) /*若权值为最大值*/ 
                printf("\t∞");          /*输出无穷大符号*/ 
            else
                printf("\t%d",G->Edges[i][j]); /*输出边的权值*/
        }
        printf("\n");
    }             
}
void initqueue(SeqQueue *Q)    /*队列初始化*/  
{
    Q->head=Q->tail=0;
}
int empty(SeqQueue Q)   /*判断队列是否已空，若空返回1,否则返回0 */
{
    return Q.head==Q.tail; 
}
int enqueue(SeqQueue *Q,int ch)   /*入队列，成功返回1，失败返回0 */  
{
    if((Q->tail+1) % QUEUE_MAXSIZE ==Q->head) /*若队列已满 */
        return 0;  /*返回错误*/
    Q->Data[Q->tail]=ch; /*将数据ch入队列*/ 
    Q->tail=(Q->tail+1) % QUEUE_MAXSIZE; /*调整队尾指针*/ 
    return 1; /*成功，返回1*/ 
}
int dequeue(SeqQueue *Q,int *p)   /*出队列,成功返回1，并用ch返回该元素值，失败返回0 */ 
{
    if(Q->head==Q->tail) /*若队列为空*/ 
        return 0; /*返回错误*/ 
    *p=Q->Data[Q->head]; /*返回队首元素*/ 
    Q->head=(Q->head+1) % QUEUE_MAXSIZE; /*调整队首指针*/ 
    return 1; /*成功出队列，返回1*/   
} 
void DFS(MatrixGraph *G,int i) /*从第i个结点开始，深度遍历图*/ 
{
    int j;
    G->visited[i]=1;	/*标记该顶点已处理过*/ 
    printf("->%c",G->Vertex[i]);	/*输出结点数据*/ 
	for(j=G->VertexNum;j>=0;j--)	/*结点号从大到小优先*/
		if(G->Edges[i][j]!=MAXVALUE && !G->visited[j])
				DFS(G,j); /*递归进行深度优先遍历*/ 
}

void push(int n)
{
	stack[s_top++]=n;
}
int pop(void)
{
	return stack[--s_top];
}
void DFSv2(MatrixGraph *G,int b,int e) /*从第i个结点开始，深度遍历图*/ 
{
    int j;
	PPATH p;
	if(e==b)
	{
		push(e);
		p=(PPATH)malloc(sizeof(PATH));
		memcpy(p->path, stack, sizeof(stack));
        p->p_top = s_top;
        p->next = head;
        head = p;
        s_top--;              
        return;
	}
    G->visited[b]=1;
	push(b);	
	for(j=0;j<G->VertexNum;j++)	
		if(G->Edges[b][j]!=MAXVALUE && !G->visited[j])
				DFSv2(G,j,e); 

	G->visited[b]=0;
	pop();
}
void BFS(MatrixGraph *G,int k) /*广度优先遍历*/ 
{
    int i,j;
    SeqQueue Q; /*创建循环队列*/ 
    initqueue(&Q); /*初始化循环队列 */
    G->visited[k]=1; /*标记该顶点*/ 
    printf("->%c",G->Vertex[k]);  /*输出第一个顶点*/ 
    enqueue(&Q,k); /*入队列 */ 
    while (!empty(Q)) /*队列不为空*/ 
    {
        dequeue(&Q,&i); /*出队列，顶点i为活结点*/
        for (j=0;j<G->VertexNum;j++)/*循环中顶点i为E结点 */
            if(G->Edges[i][j]!=MAXVALUE && !G->visited[j])
            {
                printf("->%c",G->Vertex[j]);
                G->visited[j]=1;  /*标记该顶点*/
                enqueue(&Q,j); /*结点j入队列，活结点*/ 
            }/*循环结束后顶点i为死结点 */
    }
}
void show_path(int b,int e)
{
		int i,j;
		PPATH p;
		p=head;
		j=0;
		printf("从v%d到v%d的路径:",b,e);
		while(p){
			i=0;
			printf("\n第%d条路径：",j++);
			while(i<p->p_top)
				printf("->%d",p->path[i++]);
			p=p->next;
		}
}

int main()
{
    MatrixGraph G; /*定义保存邻接表结构的图*/ 
    int i,j,start,end;
	G.VertexNum=7;/*图顶点数*/
	G.EdgeNum=9;/*图边数*/
    for(i=0;i<G.VertexNum;i++)  /*清空矩阵*/ 
		for(j=0;j<G.VertexNum;j++)
			G.Edges[i][j]=MAXVALUE; /*设置矩阵中各元素的值为MAXVALUE*/         
	create_matrix_graph(&G); /*生成邻接表结构的图*/
    printf("邻接矩阵数据如下:\n");
    show_matrix(&G); /*输出邻接矩阵*/	
    for(i=0;i<G.VertexNum;i++) /*清除各顶点遍历标志*/ 
        G.visited[i]=0;
	printf("从哪个结点开始遍历?\n");
	scanf("%d",&start);
    printf("深度优先遍历结点:");
    DFS(&G,start); /*深度优先搜索遍历图*/ 
	printf("\n"); 
	for(i=0;i<G.VertexNum;i++) /*清除各顶点遍历标志*/ 
        G.visited[i]=0;
	printf("广度优先遍历结点:");
    BFS(&G,start); /*广度优先搜索遍历图*/  
	printf("\n"); 
	for(i=0;i<G.VertexNum;i++) /*清除各顶点遍历标志*/ 
        G.visited[i]=0;
	printf("请输入起点和终点\n");
	scanf("%d%d",&start,&end);
	DFSv2(&G,start,end);
	show_path(start,end);
	printf("\n"); 
    return 0;
}