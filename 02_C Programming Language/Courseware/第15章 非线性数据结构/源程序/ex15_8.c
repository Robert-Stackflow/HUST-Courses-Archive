#include "stdio.h"
#include "stdlib.h"
#define INF (unsigned)~0>>1
#define VNUM 9 /*顶点数*/
#define ENUM 14 /*边数*/
typedef struct { 	
	int u,v,w; /*u:起点,v:终点,w:边的权值*/
}EDGE,*PEDGE;
EDGE E[ENUM]={{0,1,4},{1,2,8},{2,3,7},{3,4,9},{4,5,10},{5,6,2},{6,7,1},
	{7,0,8},{1,7,11},{2,8,2},{7,8,7},{6,8,6},{2,5,4},{3,5,14}};
struct node
{	int b,w,st; }; /*b:起点,w:权值,st为1,已访问;st为0,未访问*/
struct edge
{	int u,v; }; /*u: 边的起点,v:边的终点*/
void graph(void);
int prim(struct edge T[],int *weight);
int all_perm(struct node U[]);
int adj[VNUM][VNUM];
int prim(struct edge T[],int *weight)
{	struct node U[VNUM];	/*U[i]中：b是起点，下标i是终点，w是边(b,i)的权值*/
	int i,min,count,cur,u1,v1;	
	*weight=0;
	for(i=0;i<VNUM;i++){ /* U[i].st==0,U[i]属于V-U；U[i].st==1,则U[i]属于集合U*/
		U[i].b=0; U[i].w = INF; U[i].st = 0; /*置所有结点为未访问*/
	}
	U[0].b=0; U[0].w=0; U[0].st=1; /*置顶点0已访问，即将结点0加入集合U*/
	cur=0; /*从顶点0出发*/
	count=0; /*conut值代表树T中的结点数目*/
	while( all_perm(U) != 1 ){/*循环，知道所有顶点都被访问.即V-U为空集，即U=V*/
		for(i=0;i<VNUM;i++){/*搜索得到从顶点i到顶点cur权值最小的那条边*/
			if ( adj[cur][i] > 0 && U[i].st == 0 ){/*相邻，且未访问*/
				if( adj[cur][i] < U[i].w ){/*若权值小于U[i].e*/
					U[i].b = cur;/*起点b,终点i,完成"任选一条权值最小的边"*/
					U[i].w = adj[cur][i];/*w取边(b,i)的权值"*/
				}
			}
		}/*for循环结束时，U[i]就代表最小权值边*/
		/*下面程序搜索具有最小权值的临时结点，并且将其置为当前结点*/
		min=INF;
		for(i=0;i<VNUM;i++){/*在T中没有访问的元素中寻找权值最小的元素*/
			if(U[i].st == 0 && U[i].w < min){
				min = U[i].w; cur=i;
			}
		}/*置U[cur]为已访问,等价于完成"同时将v0并入U",并*/
		U[cur].st=1;/*且"重复步骤(2)"将从cur开始*/
		u1=U[cur].b;/*u1:边起点*/
		v1=cur;/*v1:边终点*/
		T[count].u=u1; T[count].v=v1;/*将边(u1,v1)并入集合T*/
		count++;/*集合T内结点计数值加1*/
		*weight=*weight+adj[u1][v1];/*将该边权值加入到T的权和中*/
	}
	return (count);
}
int all_perm(struct node U[] )/*T若所有结点都已访问，返回1*/
{	int i;
	for(i=0;i<VNUM;i++)
		if( U[i].st == 0 )
			return 0;
	return 1;
}
void graph(void)/*graph函数创建邻接矩阵*/
{	int k,i,j,wt;
	for(k=0;k<ENUM;k++){		
		i=E[k].u;/*取边的起点*/
		j=E[k].v;/*取边的终点*/
		wt=E[k].w;	/*取边的权值*/
		adj[i][j]=wt;/*邻接矩阵元素赋值*/
		adj[j][i]=wt;/*邻接矩阵对称元素赋值*/
	}
}
int main(void)
{	int i,wt,count; 
struct edge T[VNUM];
	graph();
	count = prim(T,&wt);
	printf("最小生成树的权值和: %d\n", wt);
	printf("组成最小生成树的边: \n");
	for(i=0;i<count;i++)
		printf("%4d  ->%3d\n",T[i].u,T[i].v);
	return 0;
}
