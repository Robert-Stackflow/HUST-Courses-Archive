#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define VERTEX_MAX 26   /*ͼ����󶥵���*/   
#define MAXVALUE 32767 /*���ֵ(����Ϊһ���������)*/
#define QUEUE_MAXSIZE 30 /*���е��������*/
#define VERTEX_NUM 7 /*������*/
#define EDGE_NUM 9	/*����*/
typedef struct
{
    char Vertex[VERTEX_MAX]; /*���涥����Ϣ(��Ż���ĸ)*/
    int Edges[VERTEX_MAX][VERTEX_MAX]; /*����ߵ�Ȩ*/ 
    int visited[VERTEX_MAX]; /*������־ */
    int VertexNum; /*��������*/ 
    int EdgeNum;/*������*/   
}MatrixGraph; /*�����ڽӾ���ͼ�ṹ*/ 
typedef struct
{
    int Data[QUEUE_MAXSIZE]; /*������*/
    int head; /*��ͷָ��*/
    int tail; /*��βָ��*/
}SeqQueue; /*���нṹ*/

typedef struct _PATH
{
	int path[VERTEX_MAX];
	int p_top;
	struct _PATH *next;
}PATH,*PPATH;
PPATH head=NULL;
int stack[VERTEX_MAX];
int s_top=0;

void initqueue(SeqQueue *q); /*��ʼ��һ������*/   
int empty(SeqQueue q); /*�ж϶����Ƿ��*/   
int enqueue(SeqQueue *q,int n); /*��һ��Ԫ�������*/   
int dequeue(SeqQueue *q,int *p); /*��һ��Ԫ�س�����*/  
void DFS(MatrixGraph *G,int);
void BFS(MatrixGraph *G,int);/*������ȱ���*/ 
void create_matrix_graph(MatrixGraph *G);/*�����ڽӾ���ͼ*/ 
void show_matrix(MatrixGraph *G); /*����ڽӾ���*/
void DFSv2(MatrixGraph *G,int b,int e);
void push(int n);
int pop(void);
void show_path(int b,int e);

void create_matrix_graph(MatrixGraph *G)/*�����ڽӾ���ͼ*/ 
{
    int i,j,k,weight;
    char start,end; /*�ߵ���ʼ����*/ 	
	char v[VERTEX_NUM]={'0','1','2','3','4','5','6'};/*��������*/
	char e[EDGE_NUM][2]={{'0','1'},{'0','3'},{'1','2'},{'1','4'},
		{'2','3'},{'2','4'},{'2','5'},{'3','4'},{'3','6'}};/*������*/
	int w[9]={1,1,1,1,1,1,1,1,1};/*Ȩֵ����*/
    for(i=0;i<G->VertexNum;i++) /*���붥��*/ 
		G->Vertex[i]=v[i];
	for(k=0;k<G->EdgeNum;k++)  /*����ߵ���Ϣ*/ 
	{
		start=e[k][0];
		end=e[k][1];
		weight=w[k];
		for(i=0;start!=G->Vertex[i];i++); /*�����ж����в���ʼ��*/ 
		for(j=0;end!=G->Vertex[j];j++); /*�����ж����в��ҽ��յ�*/ 
			G->Edges[i][j]=weight; /*��Ӧλ�ñ���Ȩֵ����ʾ��һ����*/
		G->Edges[j][i]=weight;/*�ڶԽ�λ�ñ���Ȩֵ*/  
	}
}
void show_matrix(MatrixGraph *G)/*����ڽӾ���*/ 
{
    int i,j;
    for(j=0;j<G->VertexNum;j++)
        printf("\t%c",G->Vertex[j]);    /*�ڵ�1�����������Ϣ*/ 
    printf("\n");
    for(i=0;i<G->VertexNum;i++) 
    {
        printf("%c",G->Vertex[i]);
        for(j=0;j<G->VertexNum;j++)
        {
            if(G->Edges[i][j]==MAXVALUE) /*��ȨֵΪ���ֵ*/ 
                printf("\t��");          /*�����������*/ 
            else
                printf("\t%d",G->Edges[i][j]); /*����ߵ�Ȩֵ*/
        }
        printf("\n");
    }             
}
void initqueue(SeqQueue *Q)    /*���г�ʼ��*/  
{
    Q->head=Q->tail=0;
}
int empty(SeqQueue Q)   /*�ж϶����Ƿ��ѿգ����շ���1,���򷵻�0 */
{
    return Q.head==Q.tail; 
}
int enqueue(SeqQueue *Q,int ch)   /*����У��ɹ�����1��ʧ�ܷ���0 */  
{
    if((Q->tail+1) % QUEUE_MAXSIZE ==Q->head) /*���������� */
        return 0;  /*���ش���*/
    Q->Data[Q->tail]=ch; /*������ch�����*/ 
    Q->tail=(Q->tail+1) % QUEUE_MAXSIZE; /*������βָ��*/ 
    return 1; /*�ɹ�������1*/ 
}
int dequeue(SeqQueue *Q,int *p)   /*������,�ɹ�����1������ch���ظ�Ԫ��ֵ��ʧ�ܷ���0 */ 
{
    if(Q->head==Q->tail) /*������Ϊ��*/ 
        return 0; /*���ش���*/ 
    *p=Q->Data[Q->head]; /*���ض���Ԫ��*/ 
    Q->head=(Q->head+1) % QUEUE_MAXSIZE; /*��������ָ��*/ 
    return 1; /*�ɹ������У�����1*/   
} 
void DFS(MatrixGraph *G,int i) /*�ӵ�i����㿪ʼ����ȱ���ͼ*/ 
{
    int j;
    G->visited[i]=1;	/*��Ǹö����Ѵ����*/ 
    printf("->%c",G->Vertex[i]);	/*����������*/ 
	for(j=G->VertexNum;j>=0;j--)	/*���ŴӴ�С����*/
		if(G->Edges[i][j]!=MAXVALUE && !G->visited[j])
				DFS(G,j); /*�ݹ����������ȱ���*/ 
}

void push(int n)
{
	stack[s_top++]=n;
}
int pop(void)
{
	return stack[--s_top];
}
void DFSv2(MatrixGraph *G,int b,int e) /*�ӵ�i����㿪ʼ����ȱ���ͼ*/ 
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
void BFS(MatrixGraph *G,int k) /*������ȱ���*/ 
{
    int i,j;
    SeqQueue Q; /*����ѭ������*/ 
    initqueue(&Q); /*��ʼ��ѭ������ */
    G->visited[k]=1; /*��Ǹö���*/ 
    printf("->%c",G->Vertex[k]);  /*�����һ������*/ 
    enqueue(&Q,k); /*����� */ 
    while (!empty(Q)) /*���в�Ϊ��*/ 
    {
        dequeue(&Q,&i); /*�����У�����iΪ����*/
        for (j=0;j<G->VertexNum;j++)/*ѭ���ж���iΪE��� */
            if(G->Edges[i][j]!=MAXVALUE && !G->visited[j])
            {
                printf("->%c",G->Vertex[j]);
                G->visited[j]=1;  /*��Ǹö���*/
                enqueue(&Q,j); /*���j����У�����*/ 
            }/*ѭ�������󶥵�iΪ����� */
    }
}
void show_path(int b,int e)
{
		int i,j;
		PPATH p;
		p=head;
		j=0;
		printf("��v%d��v%d��·��:",b,e);
		while(p){
			i=0;
			printf("\n��%d��·����",j++);
			while(i<p->p_top)
				printf("->%d",p->path[i++]);
			p=p->next;
		}
}

int main()
{
    MatrixGraph G; /*���屣���ڽӱ�ṹ��ͼ*/ 
    int i,j,start,end;
	G.VertexNum=7;/*ͼ������*/
	G.EdgeNum=9;/*ͼ����*/
    for(i=0;i<G.VertexNum;i++)  /*��վ���*/ 
		for(j=0;j<G.VertexNum;j++)
			G.Edges[i][j]=MAXVALUE; /*���þ����и�Ԫ�ص�ֵΪMAXVALUE*/         
	create_matrix_graph(&G); /*�����ڽӱ�ṹ��ͼ*/
    printf("�ڽӾ�����������:\n");
    show_matrix(&G); /*����ڽӾ���*/	
    for(i=0;i<G.VertexNum;i++) /*��������������־*/ 
        G.visited[i]=0;
	printf("���ĸ���㿪ʼ����?\n");
	scanf("%d",&start);
    printf("������ȱ������:");
    DFS(&G,start); /*���������������ͼ*/ 
	printf("\n"); 
	for(i=0;i<G.VertexNum;i++) /*��������������־*/ 
        G.visited[i]=0;
	printf("������ȱ������:");
    BFS(&G,start); /*���������������ͼ*/  
	printf("\n"); 
	for(i=0;i<G.VertexNum;i++) /*��������������־*/ 
        G.visited[i]=0;
	printf("�����������յ�\n");
	scanf("%d%d",&start,&end);
	DFSv2(&G,start,end);
	show_path(start,end);
	printf("\n"); 
    return 0;
}