#include "stdio.h"
#define VNUM 9 //������
#define ENUM 14 //����
typedef struct { 	
	int u;             //�ߵ���ʼ����
	int v;             //�ߵ���ֹ����
	int w;             //�ߵ�Ȩֵ
}EDGE,*PEDGE;
int cmp(const int i,const int j);
int find(int x);
int Kruskal(void);
void sort(void);
int r[ENUM];	//���������飬r[i]�д��������iС�ıߵ����
int p[ENUM];	//���鼯����
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
int find(int u)//���鼯��find
{
	return (p[u]==u?u:(p[u]=find(p[u])));
}
int Kruskal(void)
{
	int ans=0,i,j;
	int e,x,y;
	for(i=0;i<VNUM;i++)
		p[i]=i; //��ʼ�����鼯
	for(i=0;i<ENUM;i++)
		r[i]=i;  //��ʼ�������
	sort();
//	printf("���\t�յ�\tȨֵ\n");
	for(i=0;i<ENUM;i++){
		e=r[i];//E�����е�iСԪ�ص��±긳��e
		x=find(E[e].u);
		y=find(E[e].v);	//�ҳ���ǰ�ߵ������˵����ڼ���
		if(x!=y){		//x��p[x]����ͨ�߼��ϵ������˵㣬p[x]�Ǹ���(����)�ĸ�		
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
void sort(void) //���������
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