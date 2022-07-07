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
} VertexType; //�����������Ͷ���
typedef struct ArcNode
{							 //�������Ͷ���
	int adjvex;				 //����λ�ñ��
	struct ArcNode *nextarc; //��һ������ָ��
} ArcNode;
typedef struct VNode
{					   //ͷ��㼰���������Ͷ���
	VertexType data;   //������Ϣ
	ArcNode *firstarc; //ָ���һ����
} VNode, AdjList[MAX_VERTEX_NUM];
typedef struct
{						//�ڽӱ�����Ͷ���
	AdjList vertices;	//ͷ�������
	int vexnum, arcnum; //������������
	GraphKind kind;		//ͼ������
} ALGraph;
typedef struct
{ //�ڽӱ�Ĺ������
	struct
	{
		char name[30];
		ALGraph G;
	} elem[10];
	int length;
} LISTS;
int visited[200]; //����ȫ�ֱ���
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
		printf("��ѡ����Ĳ���[0~19]:");
		scanf("%d", &op);
		switch (op)
		{
		case 1:
			printf("�����������ͷ������Ϣ���ߣ�\n");
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
				printf("�ڽӱ����ɹ�");
			else if (ans == INFEASIBLE)
				printf("����ʧ�ܣ��ؼ��ֳ�ͻ");
			else if (ans == -3)
				printf("�ڽӱ��Ѵ���");
			else
				printf("������Ϣ�����ڽӱ���ʧ��");
			getchar();
			getchar();
			break;
		case 2:
			ans = DestroyGraph(G);
			if (ans == OK)
				printf("�ڽӱ����ٳɹ�");
			else if (ans == INFEASIBLE)
				printf("�ڽӱ�δ��������������");
			else
				printf("�ڽӱ�����ʧ��");
			getchar();
			getchar();
			break;
		case 3:
			printf("����������Ҷ���Ĺؼ��֣�");
			scanf("%d", &u);
			ans = LocateVex(G, u);
			if (ans == INFEASIBLE)
				printf("ͼ���޴˶���");
			else if (ans == -3)
				printf("�ڽӱ�δ����");
			else
				printf("���Ҷ�����ϢΪ %d %s\n", G.vertices[ans].key, G.vertices[ans].data.others);
			getchar();
			getchar();
			break;
		case 4:
			printf("����������ҽ��Ĺؼ��֣�");
			scanf("%d", &u);
			printf("�����븳ֵ��Ϣ:");
			scanf("%d%s", &value.key, value.others);
			ans = PutVex(G, u, value);
			if (ans == ERROR)
				printf("����ʧ�ܣ��ڽӱ����޴˶���");
			else if (ans == INFEASIBLE)
				printf("��ֵʧ�ܣ�����ֵ�Ķ���ؼ����뵱ǰͼ�еĶ���ؼ��ֳ�ͻ");
			else if (ans == -3)
				printf("�ڽӱ�δ����");
			else
				printf("��ֵ�ɹ�");
			getchar();
			getchar();
			break;
		case 5:
			printf("����������ҽ��Ĺؼ��֣�");
			scanf("%d", &u);
			ans = FirstAdjVex(G, u);
			if (ans == INFEASIBLE)
				printf("����ʧ�ܣ��ڽӱ����޴˶���");
			else if (ans == -3)
				printf("�ڽӱ�δ����");
			else if (ans == -4)
				printf("�޵�һ�ڽӵ�");
			else
				printf("��һ�ڽӵ����ϢΪ %d %s\n", G.vertices[ans].key, G.vertices[ans].data.others);
			getchar();
			getchar();
			break;
		case 6:
			printf("����������Ҷ���Ĺؼ��֣�");
			scanf("%d", &v);
			printf("������ý���һ���ڽӵ�Ĺؼ��֣�");
			scanf("%d", &w);
			ans = NextAdjVex(G, v, w);
			if (ans == INFEASIBLE)
				printf("����ڸ��ڽӵ�û����һ�ڽӵ�");
			else if (ans == -3)
				printf("�ڽӱ�δ����");
			else if (ans == -4)
				printf("������Ϣ���� ���ڽӱ��в���������Ķ���");
			else
				printf("��һ�ڽӵ����ϢΪ %d %s\n", G.vertices[ans].key, G.vertices[ans].data.others);
			getchar();
			getchar();
			break;
		case 7:
			int data;
			printf("����������붥�����Ϣ:");
			scanf("%d%s", &value.key, value.others);
			ans = InsertVex(G, value);
			if (ans == OK)
				printf("����ɹ�");
			else if (ans == -3)
				printf("�ڽӱ�δ����");
			else
				printf("����ʧ��,�ؼ��ֳ�ͻ");
			getchar();
			getchar();
			break;
		case 8:
			printf("�������ɾ������ؼ���:");
			scanf("%d", &u);
			ans = DeleteVex(G, u);
			if (ans == INFEASIBLE)
				printf("��ǰ�ڽӱ��н���һ�����㣬�޷�ɾ��");
			else if (ans == OK)
				printf("�ɹ�ɾ������");
			else if (ans == -3)
				printf("�ڽӱ�δ����");
			else
				printf("ɾ��ʧ�ܣ��ڽӱ����޴�ɾ������");
			getchar();
			getchar();
			break;
		case 9:
			printf("���������ıߵ���Ϣ:");
			scanf("%d%d", &v, &w);
			ans = InsertArc(G, v, w);
			if (ans == ERROR)
				printf("�ڽӱ��в���������ĳ����");
			else if (ans == INFEASIBLE)
				printf("�ñ��Ѵ���");
			else if (ans == -3)
				printf("�ڽӱ�δ����");
			else
				printf("����ɹ�");
			getchar();
			getchar();
			break;
		case 10:
			printf("������ɾ���ıߵ���Ϣ:");
			scanf("%d%d", &v, &w);
			ans = DeleteArc(G, v, w);
			if (ans == ERROR)
				printf("�ڽӱ��в���������ĳ����");
			else if (ans == INFEASIBLE)
				printf("�ñ߲�����");
			else if (ans == -3)
				printf("�ڽӱ�δ����");
			else
				printf("ɾ���ɹ�");
			getchar();
			getchar();
			break;
		case 11:
			ans = DFSTraverse(G, visit);
			if (ans == -3)
				printf("�ڽӱ�δ����");
			getchar();
			getchar();
			break;
		case 12:
			ans = BFSTraverse(G, visit);
			if (ans == -3)
				printf("�ڽӱ�δ����");
			getchar();
			getchar();
			break;
		case 13:
			printf("�������ļ�����:");
			scanf("%s", FileName);
			ans = SaveGraph(G, FileName);
			if (ans == -3)
				printf("�ڽӱ�δ����");
			else
				printf("�ɹ����ڽӱ������ļ�%s", FileName);
			getchar();
			getchar();
			break;
		case 14:
			printf("�������ļ�����:");
			scanf("%s", FileName);
			ans = LoadGraph(G, FileName);
			printf("�ɹ����ļ�%s�������ڽӱ�", FileName);
			getchar();
			getchar();
			break;
		case 15:
			ans = EmptyGraph(G);
			if (ans == -3)
				printf("�ڽӱ�δ����");
			else if (ans)
				printf("ͼΪ��");
			else
				printf("ͼ��Ϊ��");
			getchar();
			getchar();
			break;
		case 16:
			char name[30];
			Graphs.length = 0;
			printf("������Ҫ��ӵ��ڽӱ����:");
			scanf("%d", &n);
			printf("�����������ڽӱ����ƺ��ڽӱ���Ϣ:");
			while (n--)
			{
				scanf("%s", name);
				AddGraph(Graphs, name);
			}
			printf("\n�����ڽӱ����\n��ǰ�����Ϊ:\n");
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
			printf("������Ҫɾ�����ڽӱ�����:");
			scanf("%s", check);
			if (RemoveGraph(Graphs, check) == OK)
				for (int n = 0; n < Graphs.length; n++)
				{
					printf("%s ", Graphs.elem[n].name);
					DFSTraverse(Graphs.elem[n].G, visit);
					putchar('\n');
				}
			else
				printf("���ڽӱ��ڹ�����У�ɾ���ڽӱ�ʧ��");
			getchar();
			getchar();
			break;
		case 18:
			char check1[30];
			printf("������Ҫ���ҵ��ڽӱ�����:");
			scanf("%s", check1);
			if (n = LocateGraph(G, Graphs, check1))
			{
				printf("%s\n", Graphs.elem[n - 1].name);
				DFSTraverse(Graphs.elem[n - 1].G, visit);
				putchar('\n');
			}
			else
				printf("���ڽӱ��ڴ˹������");
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
			printf("��ѡ����Ĳ���[0~18]:");
		} //end of switch
	}	  //end of while
	printf("\nWelcome to use this system again next time!\n");
	return 0;
	//system("pause");
} //end of main()
/*----- Implementation of functions --------*/
/*------------------------------------------
��������:ʵ�ֱ���ʱ����Ĺ���
��������:ͼGraph
��������ֵ:�޷���ֵ
------------------------------------------*/
void visit(VertexType v)
{
	printf(" %d %s", v.key, v.others);
}
/*------------------------------------------
��������:�����ڽӱ�
��������:ͼG�����ã�ͼ��ͷ�������V������Ϣ����VR
��������ֵ:����int���ͣ������ɹ�����1
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
	//�жϹؼ����Ƿ�Ψһ
	for (i = 0; V[i].key != -1; i++)
	{
		G.vertices[i].data = V[i];
		G.vertices[i].firstarc = NULL;
	}
	//���������ͷ���������
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
		//�жϹؼ����Ƿ����ڱ�ͷ�ڵ�����
		ArcNode *p = (ArcNode *)malloc(sizeof(ArcNode));
		ArcNode *q = (ArcNode *)malloc(sizeof(ArcNode));
		p->adjvex = m;
		q->adjvex = n;
		p->nextarc = q->nextarc = NULL;
		//����������
		q->nextarc = G.vertices[m].firstarc;
		G.vertices[m].firstarc = q;
		p->nextarc = G.vertices[n].firstarc;
		G.vertices[n].firstarc = p;
	}
	//	//���򲢽�0�������
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
��������:�����ڽӱ�
��������:ͼG������
��������ֵ:����int���ͣ���ճɹ�����1
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
��������:�п��ڽӱ�
��������:ͼG������
��������ֵ:����int����,��Ϊ�շ���1
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
��������:�����ڽӱ���
��������:ͼG�������ҹؼ���u
��������ֵ:�����ڽӱ����λ��ָʾ���ҵ��Ľ��
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
��������:��ĳ����㸳ֵ
��������:ͼG�����ã�����ֵ�Ľ��Ĺؼ��֣�����ֵ�Ľ�����Ϣ
��������ֵ:����int���ͣ���ֵ�ɹ�����1
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
��������:�õ���һ�ڽӵ�
��������:ͼG�������ҵ�һ�ڽӽ��Ľ��Ĺؼ���u
��������ֵ:���ص�һ�ڽӽ���λ��
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
��������:�õ���һ�ڽӵ�
��������:ͼG����������һ�ڽӽ��Ľ��Ĺؼ���v����Ե��ڽӵ�Ĺؼ���w
��������ֵ:������һ�ڽӽ���λ��
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
��������:�����ͷ����
��������:ͼG�����ã������붥�����Ϣvalue
��������ֵ:����int���ͣ�����ɹ�����1
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
��������:ɾ����ͷ����
��������:ͼG�����ã���ɾ������Ĺؼ���v
��������ֵ:����int���ͣ�ɾ���ɹ�����1
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
	//����ҵ��ı�ͷ�����ڽ�����
	for (int i = flag; i < G.vexnum; i++)
		G.vertices[i] = G.vertices[i + 1];
	G.vexnum--;
	//���Ǳ�ɾ���ı�ͷ��㲢���������һ
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
		} //����׽�㼴��ɾ����ֱ��ɾ��
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
	//ɾ���뱻ɾ���ı�ͷ�����صı߲����½���λ��
	return OK;
}
/*------------------------------------------
��������:�����
��������:ͼG��������ߵ����˵Ĺؼ���
��������ֵ:����int���ͣ�����ɹ�����1
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
	//����������
	q->nextarc = G.vertices[m].firstarc;
	G.vertices[m].firstarc = q;
	p->nextarc = G.vertices[n].firstarc;
	G.vertices[n].firstarc = p;
	G.arcnum++;
	//	//���򲢽�0�������
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
	//    	}//ð������
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
��������:ɾ����
��������:ͼG����ɾ���ߵ����˵Ĺؼ���
��������ֵ:����int���ͣ�ɾ���ɹ�����1
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
		} //�����һ���ڵ㼴Ҫɾ��
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
��������:���������������
��������:ͼG�����ʺ�����ָ��visit
��������ֵ:����int���ͣ������ɹ�����1
��ע����DFSTraverse����֮��������DFS�㷨����ʵ�ֺ���
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
��������:���������������
��������:ͼG�����ʺ�����ָ��visit
��������ֵ:����int���ͣ������ɹ�����1
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
��������:����ͼ���ļ���
��������:ͼG���������ļ���·������
��������ֵ:����int���ͣ�����ɹ�����1
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
��������:�����ļ���ͼ��
��������:ͼG���������ļ���·������
��������ֵ:����int���ͣ����سɹ�����1
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
��������:���ڽӱ�Ĺ���������һ���ڽӱ�
��������:�ڽӱ�Ĺ����Graphs�����ã�������ڽӱ������FileName
��������ֵ:����int���ͣ���ӳɹ�����1
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
��������:���ڽӱ�Ĺ������ɾ��һ���ڽӱ�
��������:�ڽӱ�Ĺ����Graphs�����ã���ɾ���ڽӱ������FileName
��������ֵ:����int���ͣ�ɾ���ɹ�����1
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
��������:���ڽӱ�Ĺ�����в����ڽӱ�
��������:�ڽӱ�Ĺ����Graphs�����ã��������ڽӱ������FileName
��������ֵ:����int���ͣ����ҳɹ����ظ��ڽӱ��λ��
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
��������:��ӡ�ڽӱ�
��������:�ڽӱ������G
��������ֵ:�޷���ֵ
------------------------------------------*/
void PrintGraph(ALGraph &G)
{
	int i;
	ArcNode *p;
	if (G.vexnum == 0)
	{
		printf("��ͼ�������ӡ��\n");
		return;
	}
	printf("��ǰͼ����%d�����㣬%d����\n\n", G.vexnum, G.arcnum);
	printf("λ��\t����������Ϣ\t�ڽӱ�\t\n");
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
