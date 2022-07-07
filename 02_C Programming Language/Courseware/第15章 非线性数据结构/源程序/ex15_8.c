#include "stdio.h"
#include "stdlib.h"
#define INF (unsigned)~0>>1
#define VNUM 9 /*������*/
#define ENUM 14 /*����*/
typedef struct { 	
	int u,v,w; /*u:���,v:�յ�,w:�ߵ�Ȩֵ*/
}EDGE,*PEDGE;
EDGE E[ENUM]={{0,1,4},{1,2,8},{2,3,7},{3,4,9},{4,5,10},{5,6,2},{6,7,1},
	{7,0,8},{1,7,11},{2,8,2},{7,8,7},{6,8,6},{2,5,4},{3,5,14}};
struct node
{	int b,w,st; }; /*b:���,w:Ȩֵ,stΪ1,�ѷ���;stΪ0,δ����*/
struct edge
{	int u,v; }; /*u: �ߵ����,v:�ߵ��յ�*/
void graph(void);
int prim(struct edge T[],int *weight);
int all_perm(struct node U[]);
int adj[VNUM][VNUM];
int prim(struct edge T[],int *weight)
{	struct node U[VNUM];	/*U[i]�У�b����㣬�±�i���յ㣬w�Ǳ�(b,i)��Ȩֵ*/
	int i,min,count,cur,u1,v1;	
	*weight=0;
	for(i=0;i<VNUM;i++){ /* U[i].st==0,U[i]����V-U��U[i].st==1,��U[i]���ڼ���U*/
		U[i].b=0; U[i].w = INF; U[i].st = 0; /*�����н��Ϊδ����*/
	}
	U[0].b=0; U[0].w=0; U[0].st=1; /*�ö���0�ѷ��ʣ��������0���뼯��U*/
	cur=0; /*�Ӷ���0����*/
	count=0; /*conutֵ������T�еĽ����Ŀ*/
	while( all_perm(U) != 1 ){/*ѭ����֪�����ж��㶼������.��V-UΪ�ռ�����U=V*/
		for(i=0;i<VNUM;i++){/*�����õ��Ӷ���i������curȨֵ��С��������*/
			if ( adj[cur][i] > 0 && U[i].st == 0 ){/*���ڣ���δ����*/
				if( adj[cur][i] < U[i].w ){/*��ȨֵС��U[i].e*/
					U[i].b = cur;/*���b,�յ�i,���"��ѡһ��Ȩֵ��С�ı�"*/
					U[i].w = adj[cur][i];/*wȡ��(b,i)��Ȩֵ"*/
				}
			}
		}/*forѭ������ʱ��U[i]�ʹ�����СȨֵ��*/
		/*�����������������СȨֵ����ʱ��㣬���ҽ�����Ϊ��ǰ���*/
		min=INF;
		for(i=0;i<VNUM;i++){/*��T��û�з��ʵ�Ԫ����Ѱ��Ȩֵ��С��Ԫ��*/
			if(U[i].st == 0 && U[i].w < min){
				min = U[i].w; cur=i;
			}
		}/*��U[cur]Ϊ�ѷ���,�ȼ������"ͬʱ��v0����U",��*/
		U[cur].st=1;/*��"�ظ�����(2)"����cur��ʼ*/
		u1=U[cur].b;/*u1:�����*/
		v1=cur;/*v1:���յ�*/
		T[count].u=u1; T[count].v=v1;/*����(u1,v1)���뼯��T*/
		count++;/*����T�ڽ�����ֵ��1*/
		*weight=*weight+adj[u1][v1];/*���ñ�Ȩֵ���뵽T��Ȩ����*/
	}
	return (count);
}
int all_perm(struct node U[] )/*T�����н�㶼�ѷ��ʣ�����1*/
{	int i;
	for(i=0;i<VNUM;i++)
		if( U[i].st == 0 )
			return 0;
	return 1;
}
void graph(void)/*graph���������ڽӾ���*/
{	int k,i,j,wt;
	for(k=0;k<ENUM;k++){		
		i=E[k].u;/*ȡ�ߵ����*/
		j=E[k].v;/*ȡ�ߵ��յ�*/
		wt=E[k].w;	/*ȡ�ߵ�Ȩֵ*/
		adj[i][j]=wt;/*�ڽӾ���Ԫ�ظ�ֵ*/
		adj[j][i]=wt;/*�ڽӾ���Գ�Ԫ�ظ�ֵ*/
	}
}
int main(void)
{	int i,wt,count; 
struct edge T[VNUM];
	graph();
	count = prim(T,&wt);
	printf("��С��������Ȩֵ��: %d\n", wt);
	printf("�����С�������ı�: \n");
	for(i=0;i<count;i++)
		printf("%4d  ->%3d\n",T[i].u,T[i].v);
	return 0;
}
