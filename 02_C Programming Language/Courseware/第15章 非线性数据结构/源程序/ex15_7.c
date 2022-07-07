#include "stdio.h"
#define VNUM 9 //顶点数
#define ENUM 14 //边数
typedef struct { 	
	int u;             //边的起始顶点
	int v;             //边的终止顶点
	int w;             //边的权值
}EDGE,*PEDGE;
int cmp(const int i,const int j);
int find(int x);
int Kruskal(void);
void sort(void);
int r[ENUM];	//排序结果数组，r[i]中存放排序后第i小的边的序号
int p[ENUM];	//并查集数组
EDGE E[ENUM]={{1,2,4},{2,3,8},{3,4,7},{4,5,9},{5,6,10},{6,7,2},{7,8,1},
	{8,1,8},{2,8,11},{3,9,2},{8,9,7},{7,9,6},{3,6,4},{4,6,14}};
int main(void)
{
	printf("result is %d\n",Kruskal());		
	return 0;
}
int cmp(const int i,const int j)
{ 
	return E[i].w<E[j].w;
}
int find(int u)//并查集的find
{
	return (p[u]==u?u:(p[u]=find(p[u])));
}
int Kruskal(void)
{
	int ans=0,i,j;
	int e,x,y;
	for(i=0;i<VNUM;i++)
		p[i]=i; //初始化并查集
	for(i=0;i<ENUM;i++)
		r[i]=i;  //初始化边序号
	sort();
//	printf("起点\t终点\t权值\n");
	for(i=0;i<ENUM;i++){
		e=r[i];//E数组中第i小元素的下标赋给e
		x=find(E[e].u);
		y=find(E[e].v);	//找出当前边的两个端点所在集合
		if(x!=y){		//x和p[x]是连通边集合的两个端点，p[x]是该树(集合)的根		
			ans+=E[e].w;
			p[x]=y;
//			printf("%3d  -> %3d\t%d\n",E[e].u,E[e].v,E[e].w);
		}
		printf("e=%d,E[%d].u=%d,x=%d,E[%d].v=%d,y=%d,ans=%d\n",e,e,E[e].u,x,e,E[e].v,y,ans);
		for(j=0;j<VNUM;j++)
			printf("%d  ",p[j]);
		printf("\n");
	}
	return ans;
}
void sort(void) //间接排序函数
{
	int i,j,k,min,w[ENUM];
	for(i=0;i<ENUM;i++)
		w[i]=E[i].w;
	for(i=0;i<ENUM-1;i++){
		k=0,min=w[0];
		for(j=1;j<ENUM;j++){
			if(min>w[j]){
				min=w[j];
				k=j;
			}
		}
		r[i]=k;w[k]=((unsigned)(~0))>>1;
	}
}