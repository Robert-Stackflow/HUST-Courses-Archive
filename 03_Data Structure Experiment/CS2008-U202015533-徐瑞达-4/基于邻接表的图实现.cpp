/* Linear Table On Sequence Structure */
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
/*-------- Macro Definition ---------*/
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX_VERTEX_NUM 20
/*-------- Declare the type ---------*/
typedef int status;
typedef int KeyType;
typedef enum
{
	DG,
	DN,
	UDG,
	UDN
} GraphKind;
typedef struct
{
	KeyType key;
	char others[20];
} VertexType; //顶点数据类型定义
typedef struct ArcNode
{							 //表结点类型定义
	int adjvex;				 //顶点位置编号
	struct ArcNode *nextarc; //下一个表结点指针
} ArcNode;
typedef struct VNode
{					   //头结点及其数组类型定义
	VertexType data;   //顶点信息
	ArcNode *firstarc; //指向第一条边
} VNode, AdjList[MAX_VERTEX_NUM];
typedef struct
{						//邻接表的类型定义
	AdjList vertices;	//头结点数组
	int vexnum, arcnum; //顶点数、边数
	GraphKind kind;		//图的类型
} ALGraph;
typedef struct
{ //邻接表的管理表定义
	struct
	{
		char name[30];
		ALGraph G;
	} elem[10];
	int length;
} LISTS;
int visited[200]; //声明全局变量
/*-----Function Declaration---------*/
status CreateGraph(ALGraph &G, VertexType V[], KeyType VR[][2]);
status DestroyGraph(ALGraph &G);
int LocateVex(ALGraph G, KeyType u);
status PutVex(ALGraph &G, KeyType u, VertexType value);
int FirstAdjVex(ALGraph G, KeyType u);
int NextAdjVex(ALGraph G, KeyType v, KeyType w);
status InsertVex(ALGraph &G, VertexType v);
status DeleteVex(ALGraph &G, KeyType v);
status InsertArc(ALGraph &G, KeyType v, KeyType w);
status DeleteArc(ALGraph &G, KeyType v, KeyType w);
void visit(VertexType v);
status DFSTraverse(ALGraph &G, void (*visit)(VertexType));
status BFSTraverse(ALGraph &G, void (*visit)(VertexType));
status SaveGraph(ALGraph G, char FileName[]);
status LoadGraph(ALGraph &G, char FileName[]);
status EmptyGraph(ALGraph &G);
status AddGraph(LISTS &Graphs, char FileName[]);
status RemoveGraph(LISTS &Graphs, char FileName[]);
status LocateGraph(ALGraph &G, LISTS &Graphs, char FileName[]);
void PrintGraph(ALGraph &G);
/*----- The main function --------*/
int main()
{
	ALGraph G;
	LISTS Graphs;
	G.arcnum = G.vexnum = 0;
	VertexType value;
	KeyType u, v, w;
	char FileName[20];
	int op = 1, ans = 0, i = 0, j = 0, n = 0;
	while (op)
	{
		system("cls");
		printf("\n\n");
		printf("      Menu for Linear Table On Sequence Structure \n");
		printf("-------------------------------------------------------\n");
		printf("    	   1. CreateCraph            2. DestroyGraph\n");
		printf("    	   3. LocateVex              4. PutVex\n");
		printf("    	   5. FirstAdjVex            6. NextAdjVex\n");
		printf("    	   7. InsertVex              8. DeleteVex\n");
		printf("    	   9. InsertArc             10. DeleteArc\n");
		printf("    	  11. DFSTraverse           12. BFSTraverse\n");
		printf("    	  13. SaveGraph             14. LoadGraph\n");
		printf("    	  15. EmptyGraph            16. AddGraph\n");
		printf("    	  17. RemoveGraph           18. LocateGraph\n");
		printf("          19. PrintGraph             0.Exit\n");
		printf("-------------------------------------------------------\n");
		printf("请选择你的操作[0~19]:");
		scanf("%d", &op);
		switch (op)
		{
		case 1:
			printf("请依次输入表头结点的信息及边：\n");
			VertexType V[30];
			KeyType VR[100][2];
			i = j = 0;
			do
			{
				scanf("%d%s", &V[i].key, V[i].others);
			} while (V[i++].key != -1);
			i = 0;
			do
			{
				scanf("%d%d", &VR[i][0], &VR[i][1]);
			} while (VR[i++][0] != -1);
			ans = CreateGraph(G, V, VR);
			if (ans == OK)
				printf("邻接表创建成功");
			else if (ans == INFEASIBLE)
				printf("创建失败，关键字冲突");
			else if (ans == -3)
				printf("邻接表已创建");
			else
				printf("输入信息有误，邻接表创建失败");
			getchar();
			getchar();
			break;
		case 2:
			ans = DestroyGraph(G);
			if (ans == OK)
				printf("邻接表销毁成功");
			else if (ans == INFEASIBLE)
				printf("邻接表未创建，无需销毁");
			else
				printf("邻接表销毁失败");
			getchar();
			getchar();
			break;
		case 3:
			printf("请输入待查找顶点的关键字：");
			scanf("%d", &u);
			ans = LocateVex(G, u);
			if (ans == INFEASIBLE)
				printf("图中无此顶点");
			else if (ans == -3)
				printf("邻接表未创建");
			else
				printf("查找顶点信息为 %d %s\n", G.vertices[ans].key, G.vertices[ans].data.others);
			getchar();
			getchar();
			break;
		case 4:
			printf("请输入待查找结点的关键字：");
			scanf("%d", &u);
			printf("请输入赋值信息:");
			scanf("%d%s", &value.key, value.others);
			ans = PutVex(G, u, value);
			if (ans == ERROR)
				printf("查找失败，邻接表中无此顶点");
			else if (ans == INFEASIBLE)
				printf("赋值失败，待赋值的顶点关键字与当前图中的顶点关键字冲突");
			else if (ans == -3)
				printf("邻接表未创建");
			else
				printf("赋值成功");
			getchar();
			getchar();
			break;
		case 5:
			printf("请输入待查找结点的关键字：");
			scanf("%d", &u);
			ans = FirstAdjVex(G, u);
			if (ans == INFEASIBLE)
				printf("查找失败，邻接表中无此顶点");
			else if (ans == -3)
				printf("邻接表未创建");
			else if (ans == -4)
				printf("无第一邻接点");
			else
				printf("第一邻接点的信息为 %d %s\n", G.vertices[ans].key, G.vertices[ans].data.others);
			getchar();
			getchar();
			break;
		case 6:
			printf("请输入待查找顶点的关键字：");
			scanf("%d", &v);
			printf("请输入该结点的一个邻接点的关键字：");
			scanf("%d", &w);
			ans = NextAdjVex(G, v, w);
			if (ans == INFEASIBLE)
				printf("相对于该邻接点没有下一邻接点");
			else if (ans == -3)
				printf("邻接表未创建");
			else if (ans == -4)
				printf("输入信息有误 ，邻接表中不存在输入的顶点");
			else
				printf("第一邻接点的信息为 %d %s\n", G.vertices[ans].key, G.vertices[ans].data.others);
			getchar();
			getchar();
			break;
		case 7:
			int data;
			printf("请输入待插入顶点的信息:");
			scanf("%d%s", &value.key, value.others);
			ans = InsertVex(G, value);
			if (ans == OK)
				printf("插入成功");
			else if (ans == -3)
				printf("邻接表未创建");
			else
				printf("插入失败,关键字冲突");
			getchar();
			getchar();
			break;
		case 8:
			printf("请输入待删除顶点关键字:");
			scanf("%d", &u);
			ans = DeleteVex(G, u);
			if (ans == INFEASIBLE)
				printf("当前邻接表中仅有一个顶点，无法删除");
			else if (ans == OK)
				printf("成功删除顶点");
			else if (ans == -3)
				printf("邻接表未创建");
			else
				printf("删除失败，邻接表中无待删除顶点");
			getchar();
			getchar();
			break;
		case 9:
			printf("请输入插入的边的信息:");
			scanf("%d%d", &v, &w);
			ans = InsertArc(G, v, w);
			if (ans == ERROR)
				printf("邻接表中不存在其中某顶点");
			else if (ans == INFEASIBLE)
				printf("该边已存在");
			else if (ans == -3)
				printf("邻接表未创建");
			else
				printf("插入成功");
			getchar();
			getchar();
			break;
		case 10:
			printf("请输入删除的边的信息:");
			scanf("%d%d", &v, &w);
			ans = DeleteArc(G, v, w);
			if (ans == ERROR)
				printf("邻接表中不存在其中某顶点");
			else if (ans == INFEASIBLE)
				printf("该边不存在");
			else if (ans == -3)
				printf("邻接表未创建");
			else
				printf("删除成功");
			getchar();
			getchar();
			break;
		case 11:
			ans = DFSTraverse(G, visit);
			if (ans == -3)
				printf("邻接表未创建");
			getchar();
			getchar();
			break;
		case 12:
			ans = BFSTraverse(G, visit);
			if (ans == -3)
				printf("邻接表未创建");
			getchar();
			getchar();
			break;
		case 13:
			printf("请输入文件名称:");
			scanf("%s", FileName);
			ans = SaveGraph(G, FileName);
			if (ans == -3)
				printf("邻接表未创建");
			else
				printf("成功将邻接表保存至文件%s", FileName);
			getchar();
			getchar();
			break;
		case 14:
			printf("请输入文件名称:");
			scanf("%s", FileName);
			ans = LoadGraph(G, FileName);
			printf("成功将文件%s加载至邻接表", FileName);
			getchar();
			getchar();
			break;
		case 15:
			ans = EmptyGraph(G);
			if (ans == -3)
				printf("邻接表未创建");
			else if (ans)
				printf("图为空");
			else
				printf("图不为空");
			getchar();
			getchar();
			break;
		case 16:
			char name[30];
			Graphs.length = 0;
			printf("请输入要添加的邻接表个数:");
			scanf("%d", &n);
			printf("请依次输入邻接表名称和邻接表信息:");
			while (n--)
			{
				scanf("%s", name);
				AddGraph(Graphs, name);
			}
			printf("\n插入邻接表完毕\n当前管理表为:\n");
			for (n = 0; n < Graphs.length; n++)
			{
				printf("%s\n", Graphs.elem[n].name);
				DFSTraverse(Graphs.elem[n].G, visit);
				printf("\n");
			}
			getchar();
			getchar();
			break;
		case 17:
			char check[30];
			printf("请输入要删除的邻接表名称:");
			scanf("%s", check);
			if (RemoveGraph(Graphs, check) == OK)
				for (int n = 0; n < Graphs.length; n++)
				{
					printf("%s ", Graphs.elem[n].name);
					DFSTraverse(Graphs.elem[n].G, visit);
					putchar('\n');
				}
			else
				printf("该邻接表不在管理表中，删除邻接表失败");
			getchar();
			getchar();
			break;
		case 18:
			char check1[30];
			printf("请输入要查找的邻接表名称:");
			scanf("%s", check1);
			if (n = LocateGraph(G, Graphs, check1))
			{
				printf("%s\n", Graphs.elem[n - 1].name);
				DFSTraverse(Graphs.elem[n - 1].G, visit);
				putchar('\n');
			}
			else
				printf("该邻接表不在此管理表中");
			getchar();
			getchar();
			break;
		case 19:
			PrintGraph(G);
			getchar();
			getchar();
			break;
		case 0:
			break;
			printf("请选择你的操作[0~18]:");
		} //end of switch
	}	  //end of while
	printf("\nWelcome to use this system again next time!\n");
	return 0;
	//system("pause");
} //end of main()
/*----- Implementation of functions --------*/
/*------------------------------------------
函数功能:实现遍历时所需的功能
函数参数:图Graph
函数返回值:无返回值
------------------------------------------*/
void visit(VertexType v)
{
	printf(" %d %s", v.key, v.others);
}
/*------------------------------------------
函数功能:创建邻接表
函数参数:图G的引用，图表头结点数组V，边信息数组VR
函数返回值:返回int类型，创建成功返回1
------------------------------------------*/
status CreateGraph(ALGraph &G, VertexType V[], KeyType VR[][2])
{
	if (G.vexnum || G.arcnum)
		return -3;
	int i = 0, j = 0, repeat = 0;
	G.arcnum = G.vexnum = 0;
	if (V[0].key == -1)
		return ERROR;
	for (i = 0; V[i].key != -1; i++)
		for (j = i + 1; V[j].key != -1; j++)
			if (V[i].key == V[j].key)
				return ERROR;
	//判断关键字是否不唯一
	for (i = 0; V[i].key != -1; i++)
	{
		G.vertices[i].data = V[i];
		G.vertices[i].firstarc = NULL;
	}
	//将顶点读入头结点数组中
	G.kind = UDG;
	G.vexnum = i;
	if (G.vexnum > 20)
		return ERROR;
	for (i = 0; VR[i][0] != -1; i++)
	{
		int m = -1, n = -1;
		for (int j = 0; V[j].key != -1; j++)
			if (V[j].key == VR[i][0])
				m = j;
		for (int j = 0; V[j].key != -1; j++)
			if (V[j].key == VR[i][1])
				n = j;
		if (m == -1 || n == -1)
			return ERROR;
		ArcNode *s = G.vertices[m].firstarc;
		while (s)
		{
			if (s->adjvex == n)
				repeat = 1;
			s = s->nextarc;
		}
		if (m == n || repeat)
			continue;
		G.arcnum++;
		//判断关键字是否属于表头节点数组
		ArcNode *p = (ArcNode *)malloc(sizeof(ArcNode));
		ArcNode *q = (ArcNode *)malloc(sizeof(ArcNode));
		p->adjvex = m;
		q->adjvex = n;
		p->nextarc = q->nextarc = NULL;
		//创建链表结点
		q->nextarc = G.vertices[m].firstarc;
		G.vertices[m].firstarc = q;
		p->nextarc = G.vertices[n].firstarc;
		G.vertices[n].firstarc = p;
	}
	//	//排序并将0移至最后
	//	for(i=0;G.arcnum&&i<G.vexnum;i++)
	//	{
	//		if(G.vertices[i].firstarc==NULL||G.vertices[i].firstarc->nextarc==NULL) continue;
	//		for (ArcNode* temp=G.vertices[i].firstarc;temp->nextarc!=NULL;temp=temp->nextarc)
	//		{
	//        	for (ArcNode* p=G.vertices[i].firstarc;p->nextarc!=NULL;p=p->nextarc)
	//			{
	//            	if (p->adjvex>p->nextarc->adjvex)
	//				{
	//                	int t=p->adjvex;
	//                	p->adjvex=p->nextarc->adjvex;
	//                	p->nextarc->adjvex=t;
	//            	}
	//        	}
	//    	}
	//		if(G.vertices[i].firstarc->adjvex==0)
	//		{
	//		ArcNode *p,*q;
	//		p=q=G.vertices[i].firstarc;
	//		while(p->nextarc)p=p->nextarc;
	//		G.vertices[i].firstarc=G.vertices[i].firstarc->nextarc;
	//		p->nextarc=q;
	//		q->nextarc=NULL;
	//		}
	//	}
	return OK;
}
/*------------------------------------------
函数功能:销毁邻接表
函数参数:图G的引用
函数返回值:返回int类型，清空成功返回1
------------------------------------------*/
status DestroyGraph(ALGraph &G)
{
	if (G.arcnum == 0 && G.vexnum == 0)
		return INFEASIBLE;
	for (int i = 0; i < G.vexnum; i++)
	{
		ArcNode *p = G.vertices[i].firstarc, *q;
		while (p)
		{
			q = p;
			p = p->nextarc;
			free(q);
		}
		G.vertices[i].firstarc = NULL;
	}
	G.vexnum = 0;
	G.arcnum = 0;
	return OK;
}
/*------------------------------------------
函数功能:判空邻接表
函数参数:图G的引用
函数返回值:返回int类型,树为空返回1
------------------------------------------*/
status EmptyGraph(ALGraph &G)
{
	if (!G.vexnum && !G.arcnum)
		return -3;
	if (G.arcnum == 0)
		return OK;
	else
		return ERROR;
}
/*------------------------------------------
函数功能:查找邻接表结点
函数参数:图G，待查找关键字u
函数返回值:返回邻接表结点的位序，指示被找到的结点
------------------------------------------*/
int LocateVex(ALGraph G, KeyType u)
{
	if (!G.vexnum && !G.arcnum)
		return -3;
	for (int i = 0; i < G.vexnum; i++)
		if (u == G.vertices[i].key)
			return i;
	return INFEASIBLE;
}
/*------------------------------------------
函数功能:给某个结点赋值
函数参数:图G的引用，被赋值的结点的关键字，待赋值的结点的信息
函数返回值:返回int类型，赋值成功返回1
------------------------------------------*/
status PutVex(ALGraph &G, KeyType u, VertexType value)
{
	if (!G.vexnum && !G.arcnum)
		return -3;
	int flag1 = LocateVex(G, value.key);
	int flag2 = LocateVex(G, u);
	if (flag2 == -1)
		return ERROR;
	if (flag1 != -1 && flag1 != flag2)
		return INFEASIBLE;
	G.vertices[flag2].data = value;
	return OK;
}
/*------------------------------------------
函数功能:得到第一邻接点
函数参数:图G，待查找第一邻接结点的结点的关键字u
函数返回值:返回第一邻接结点的位序
------------------------------------------*/
int FirstAdjVex(ALGraph G, KeyType u)
{
	if (!G.vexnum && !G.arcnum)
		return -3;
	int flag = LocateVex(G, u);
	if (flag == -1)
		return INFEASIBLE;
	if (G.vertices[flag].firstarc)
		return G.vertices[flag].firstarc->adjvex;
	else
		return -4;
}
/*------------------------------------------
函数功能:得到下一邻接点
函数参数:图G，待查找下一邻接结点的结点的关键字v，相对的邻接点的关键字w
函数返回值:返回下一邻接结点的位序
------------------------------------------*/
int NextAdjVex(ALGraph G, KeyType v, KeyType w)
{
	if (!G.vexnum && !G.arcnum)
		return -3;
	int flag = LocateVex(G, v);
	int check = LocateVex(G, w);
	if (flag == -1 || check == -1)
		return -4;
	ArcNode *p = G.vertices[flag].firstarc;
	while (p)
	{
		if (p->adjvex == check)
		{
			if (p->nextarc == NULL)
				return -1;
			else
				return p->nextarc->adjvex;
		}
		p = p->nextarc;
	}
	return -1;
}
/*------------------------------------------
函数功能:插入表头顶点
函数参数:图G的引用，被插入顶点的信息value
函数返回值:返回int类型，插入成功返回1
------------------------------------------*/
status InsertVex(ALGraph &G, VertexType value)
{
	if (!G.vexnum && !G.arcnum)
		return -3;
	if (LocateVex(G, value.key) != -1 || G.vexnum == 20)
		return ERROR;
	G.vertices[G.vexnum].data = value;
	G.vertices[G.vexnum].firstarc = NULL;
	G.vexnum++;
	return OK;
}
/*------------------------------------------
函数功能:删除表头顶点
函数参数:图G的引用，待删除顶点的关键字v
函数返回值:返回int类型，删除成功返回1
------------------------------------------*/
status DeleteVex(ALGraph &G, KeyType v)
{
	if (!G.vexnum && !G.arcnum)
		return -3;
	int flag = LocateVex(G, v);
	if (flag == -1)
		return ERROR;
	if ((flag == 0 && G.vexnum == 1))
		return INFEASIBLE;
	ArcNode *p = G.vertices[flag].firstarc, *q;
	while (p)
	{
		q = p;
		p = p->nextarc;
		free(q);
	}
	G.vertices[flag].firstarc = NULL;
	//清空找到的表头结点的邻接链表
	for (int i = flag; i < G.vexnum; i++)
		G.vertices[i] = G.vertices[i + 1];
	G.vexnum--;
	//覆盖被删除的表头结点并将结点数减一
	for (int i = 0; i < G.vexnum; i++)
	{
		p = q = G.vertices[i].firstarc;
		if (p == NULL)
			continue;
		if (p->adjvex == flag)
		{
			q = p->nextarc;
			free(p);
			G.vertices[i].firstarc = q;
			G.arcnum--;
		} //如果首结点即需删除则直接删除
		else
		{
			while (p)
			{
				if (p->adjvex == flag)
				{
					q->nextarc = p->nextarc;
					G.arcnum--;
					free(p);
					break;
				}
				q = p;
				p = p->nextarc;
			}
		}
		q = G.vertices[i].firstarc;
		while (q)
		{
			if (q->adjvex > flag)
				q->adjvex--;
			q = q->nextarc;
		}
	}
	//删除与被删除的表头结点相关的边并更新结点的位序
	return OK;
}
/*------------------------------------------
函数功能:插入边
函数参数:图G，待插入边的两端的关键字
函数返回值:返回int类型，插入成功返回1
------------------------------------------*/
status InsertArc(ALGraph &G, KeyType v, KeyType w)
{
	if (!G.vexnum && !G.arcnum)
		return -3;
	int m = LocateVex(G, v), n = LocateVex(G, w);
	if (m == -1 || n == -1)
		return ERROR;
	ArcNode *s = G.vertices[m].firstarc;
	while (s)
	{
		if (s->adjvex == n)
			return INFEASIBLE;
		s = s->nextarc;
	}
	ArcNode *p = (ArcNode *)malloc(sizeof(ArcNode));
	ArcNode *q = (ArcNode *)malloc(sizeof(ArcNode));
	p->adjvex = m;
	q->adjvex = n;
	p->nextarc = q->nextarc = NULL;
	//创建链表结点
	q->nextarc = G.vertices[m].firstarc;
	G.vertices[m].firstarc = q;
	p->nextarc = G.vertices[n].firstarc;
	G.vertices[n].firstarc = p;
	G.arcnum++;
	//	//排序并将0移至最后
	//	for(int i=0;G.arcnum&&i<G.vexnum;i++)
	//	{
	//		if(G.vertices[i].firstarc==NULL||G.vertices[i].firstarc->nextarc==NULL) continue;
	//		for (ArcNode* temp=G.vertices[i].firstarc;temp->nextarc!=NULL;temp=temp->nextarc)
	//		{
	//        	for (ArcNode* p=G.vertices[i].firstarc;p->nextarc!=NULL;p=p->nextarc)
	//			{
	//            	if (p->adjvex>p->nextarc->adjvex)
	//				{
	//                	int t=p->adjvex;
	//                	p->adjvex=p->nextarc->adjvex;
	//                	p->nextarc->adjvex=t;
	//            	}
	//        	}
	//    	}//冒泡排序
	//		if(G.vertices[i].firstarc->adjvex==0&&G.vertices[i].firstarc->nextarc)
	//		{
	//		ArcNode *p,*q;
	//		p=q=G.vertices[i].firstarc;
	//		while(p->nextarc)p=p->nextarc;
	//		G.vertices[i].firstarc=G.vertices[i].firstarc->nextarc;
	//		p->nextarc=q;
	//		q->nextarc=NULL;
	//		}
	//	}
	return OK;
}
/*------------------------------------------
函数功能:删除边
函数参数:图G，待删除边的两端的关键字
函数返回值:返回int类型，删除成功返回1
------------------------------------------*/
status DeleteArc(ALGraph &G, KeyType v, KeyType w)
{
	if (!G.vexnum && !G.arcnum)
		return -3;
	int flag1 = LocateVex(G, v), flag2 = LocateVex(G, w), count = 2, k, flag = 1;
	if (flag1 == -1 || flag2 == -1)
		return ERROR;
	ArcNode *s, *q;
	G.arcnum--;
	while (count--)
	{
		s = q = G.vertices[flag1].firstarc;
		if (s != NULL && s->adjvex == flag2)
		{
			G.vertices[flag1].firstarc = s->nextarc;
			free(s);
		} //如果第一个节点即要删除
		else
		{
			while (s)
			{
				if (s->adjvex == flag2)
				{
					q->nextarc = s->nextarc;
					free(s);
					flag = 0;
					break;
				}
				q = s;
				s = s->nextarc;
			}
			if (flag)
				return INFEASIBLE;
		}
		k = flag1;
		flag1 = flag2;
		flag2 = k;
	}
	return OK;
}
/*------------------------------------------
函数功能:深度优先搜索遍历
函数参数:图G，访问函数的指针visit
函数返回值:返回int类型，遍历成功返回1
备注：除DFSTraverse函数之外声明了DFS算法核心实现函数
------------------------------------------*/
void DFS(ALGraph G, int v, void (*visit)(VertexType))
{
	int w;
	visited[v] = 1;
	visit(G.vertices[v].data);
	for (w = FirstAdjVex(G, G.vertices[v].key); w >= 0; w = NextAdjVex(G, G.vertices[v].key, G.vertices[w].key))
		if (!visited[w])
			DFS(G, w, visit);
}
status DFSTraverse(ALGraph &G, void (*visit)(VertexType))
{
	if (!G.vexnum && !G.arcnum)
		return -3;
	int v;
	for (v = 0; v < G.vexnum; v++)
		visited[v] = 0;
	for (v = 0; v < G.vexnum; v++)
		if (!visited[v])
			DFS(G, v, visit);
	return OK;
}
/*------------------------------------------
函数功能:广度优先搜索遍历
函数参数:图G，访问函数的指针visit
函数返回值:返回int类型，遍历成功返回1
------------------------------------------*/
status BFSTraverse(ALGraph &G, void (*visit)(VertexType))
{
	if (!G.vexnum && !G.arcnum)
		return -3;
	int v, w;
	int elem[100], e;
	int front = 0, length = 0;
	for (v = 0; v < G.vexnum; v++)
		visited[v] = 0;
	for (v = 0; v < G.vexnum; v++)
	{
		if (visited[v])
			continue;
		visited[v] = 1;
		visit(G.vertices[v].data);
		elem[front + length] = v;
		length++;
		while (length)
		{
			e = elem[front];
			front = (front + 1) % 100;
			length--;
			for (w = FirstAdjVex(G, G.vertices[e].key); w >= 0; w = NextAdjVex(G, G.vertices[e].key, G.vertices[w].key))
			{
				if (!visited[w])
				{
					visited[w] = 1;
					visit(G.vertices[w].data);
					elem[front + length] = w;
					length++;
				}
			}
		}
	}
	return OK;
}
/*------------------------------------------
函数功能:保存图到文件中
函数参数:图G，待保存文件的路径名称
函数返回值:返回int类型，保存成功返回1
------------------------------------------*/
status SaveGraph(ALGraph G, char FileName[])
{
	if (!G.vexnum && !G.arcnum)
		return -3;
	FILE *fp = fopen(FileName, "w");
	for (int i = 0; i < G.vexnum; i++)
		fprintf(fp, "%d %s ", G.vertices[i].key, G.vertices[i].data.others);
	fprintf(fp, "-1 null ");
	for (int i = 0, j = 0; i < G.vexnum; i++)
	{
		ArcNode *p = G.vertices[i].firstarc;
		KeyType adjvex[100];
		while (p)
		{
			if (G.vertices[i].key < G.vertices[p->adjvex].key)
				fprintf(fp, "%d %d ", G.vertices[i].key, G.vertices[p->adjvex].key);
			p = p->nextarc;
		}
	}
	fprintf(fp, "-1 -1 ");
	fclose(fp);
	return OK;
}
/*------------------------------------------
函数功能:加载文件到图中
函数参数:图G，待加载文件的路径名称
函数返回值:返回int类型，加载成功返回1
------------------------------------------*/
status LoadGraph(ALGraph &G, char FileName[])
{
	FILE *fp = fopen(FileName, "r");
	VertexType V[30];
	KeyType VR[100][2];
	int i = 0;
	do
	{
		fscanf(fp, "%d%s", &V[i].key, V[i].others);
	} while (V[i++].key != -1);
	i = 0;
	do
	{
		fscanf(fp, "%d%d", &VR[i][0], &VR[i][1]);
	} while (VR[i++][0] != -1);
	CreateGraph(G, V, VR);
	fclose(fp);
	return OK;
}
/*------------------------------------------
函数功能:在邻接表的管理表中添加一个邻接表
函数参数:邻接表的管理表Graphs的引用，待添加邻接表的名称FileName
函数返回值:返回int类型，添加成功返回1
------------------------------------------*/
status AddGraph(LISTS &Graphs, char FileName[])
{
	strcpy(Graphs.elem[Graphs.length].name, FileName);
	VertexType V[30];
	KeyType VR[100][2];
	int i = 0;
	do
	{
		scanf("%d%s", &V[i].key, V[i].others);
	} while (V[i++].key != -1);
	i = 0;
	do
	{
		scanf("%d%d", &VR[i][0], &VR[i][1]);
	} while (VR[i++][0] != -1);
	Graphs.elem[Graphs.length].G.arcnum = Graphs.elem[Graphs.length].G.vexnum = 0;
	CreateGraph(Graphs.elem[Graphs.length].G, V, VR);
	Graphs.length++;
	return OK;
}
/*------------------------------------------
函数功能:在邻接表的管理表中删除一个邻接表
函数参数:邻接表的管理表Graphs的引用，待删除邻接表的名称FileName
函数返回值:返回int类型，删除成功返回1
------------------------------------------*/
status RemoveGraph(LISTS &Graphs, char FileName[])
{
	for (int j = 1; j <= Graphs.length; j++)
	{
		if (strcmp(FileName, Graphs.elem[j - 1].name) == 0)
		{
			DestroyGraph(Graphs.elem[j - 1].G);
			for (int i = j; i < Graphs.length; i++)
			{
				strcpy(Graphs.elem[i - 1].name, Graphs.elem[i].name);
				Graphs.elem[i - 1].G = Graphs.elem[i].G;
			}
			Graphs.length--;
			return OK;
		}
	}
	return ERROR;
}
/*------------------------------------------
函数功能:在邻接表的管理表中查找邻接表
函数参数:邻接表的管理表Graphs的引用，待查找邻接表的名称FileName
函数返回值:返回int类型，查找成功返回该邻接表的位置
------------------------------------------*/
status LocateGraph(ALGraph &G, LISTS &Graphs, char FileName[])
{
	for (int i = 1; i <= Graphs.length; i++)
		if (strcmp(FileName, Graphs.elem[i - 1].name) == 0)
		{
			G = Graphs.elem[i - 1].G;
			return i;
		}
	return ERROR;
}
/*------------------------------------------
函数功能:打印邻接表
函数参数:邻接表的引用G
函数返回值:无返回值
------------------------------------------*/
void PrintGraph(ALGraph &G)
{
	int i;
	ArcNode *p;
	if (G.vexnum == 0)
	{
		printf("空图，无需打印！\n");
		return;
	}
	printf("当前图包含%d个顶点，%d条边\n\n", G.vexnum, G.arcnum);
	printf("位序\t顶点数组信息\t邻接表\t\n");
	for (i = 0; i < G.vexnum; i++)
	{
		printf("%d\t  %d  %s  \t", i, G.vertices[i].key, G.vertices[i].data.others);
		p = G.vertices[i].firstarc;
		while (p != NULL)
		{
			printf("%d", p->adjvex);
			p = p->nextarc;
			if (p != NULL)
				printf("->");
		}
		printf("\n");
	}
}
