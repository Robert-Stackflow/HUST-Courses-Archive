#include <stdio.h>
#include <stdlib.h>

typedef struct ArcNode {//�������Ͷ���
	int adjvex;				 //����λ�ñ��
	struct ArcNode *nextarc; //��һ������ָ��
} ArcNode;

typedef struct VNode {//ͷ��㼰���������Ͷ���
	int key;   //������Ϣ
	ArcNode *firstarc; //ָ���һ����
} VNode, AdjList[100005];

typedef struct {//�ڽӱ�����Ͷ���
	AdjList vertices;	//ͷ�������
	int vexnum, arcnum; //������������
} ALGraph;
ALGraph G;
int visited[100005];
int n, m; //�������ͱ���
int vex1, vex2; //������ȡ���ݵı���
int DFSTraverse();
int BFSTraverse();

void PrintGraph() {
	int i;
	ArcNode *p;
	printf("\n����\t�ڽӱ�\t\n");
	for (i = 1; i <= G.vexnum; i++) {
		printf("%d\t", i, G.vertices[i].key);
		p = G.vertices[i].firstarc;
		while (p != NULL) {
			printf("%d", p->adjvex);
			p = p->nextarc;
			if (p != NULL)
				printf("->");
		}
		printf("\n");
	}
	printf("\n");
}

int main(void) {
	G.arcnum = G.vexnum = 0;
	scanf("%d%d", &n, &m);
	G.vexnum = n;
	G.arcnum = m;
	for (int i = 1; i <= n; i++) {
		G.vertices[i].key = i;
		G.vertices[i].firstarc = NULL;
	}//��ʼ����������
	for (int i = 1; i <= m; i++) {
		scanf("%d%d", &vex1, &vex2);
		ArcNode *p =  G.vertices[vex1].firstarc;
		ArcNode *add = (ArcNode *)malloc(sizeof(ArcNode));
		add->adjvex = vex2;
		add->nextarc = NULL;
		if (p == NULL)
			G.vertices[vex1].firstarc = add;
		else if (p->adjvex > vex2) {
			add->nextarc = p;
			G.vertices[vex1].firstarc = add;
		} else {
			while (p) {
				if (p->adjvex < vex2 && p->nextarc == NULL)
					p->nextarc = add;
				if (p->nextarc != NULL && p->adjvex < vex2 && p->nextarc->adjvex > vex2) {
					add->nextarc = p->nextarc;
					p->nextarc = add;
				}
				p = p->nextarc;
			}
		}
	}
//	PrintGraph();
	DFSTraverse();
	printf("\n");
	BFSTraverse();
	return 0;
}

int FirstAdjVex(int u) {
	if (G.vertices[u].firstarc)
		return G.vertices[u].firstarc->adjvex;
	else
		return -1;
}

int NextAdjVex(int v, int w) {
	ArcNode *p = G.vertices[v].firstarc;
	while (p) {
		if (p->adjvex == w) {
			if (p->nextarc == NULL)
				return -1;
			else
				return p->nextarc->adjvex;
		}
		p = p->nextarc;
	}
	return -1;
}

void DFS(int v) {
	int w;
	visited[v] = 1;
	printf("%d ", G.vertices[v].key);
	for (w = FirstAdjVex(G.vertices[v].key); w >= 0;
	        w = NextAdjVex(G.vertices[v].key, G.vertices[w].key))
		if (!visited[w])
			DFS(w);
}

int DFSTraverse() {
	int v;
	for (v = 1; v <= G.vexnum; v++)
		visited[v] = 0;
	DFS(1);
}

int BFSTraverse() {
	int v, w;
	int elem[100000], e;
	int front = 0, length = 0;
	for (v = 1; v <= G.vexnum; v++)
		visited[v] = 0;
	v = 1;
	visited[v] = 1;
	printf("%d ", G.vertices[v].key);
	elem[front + length] = v;
	length++;
	while (length) {
		e = elem[front];
		front = (front + 1) % 100000;
		length--;
		for (w = FirstAdjVex(G.vertices[e].key); w >= 0;
		        w = NextAdjVex(G.vertices[e].key, G.vertices[w].key)) {
			if (!visited[w]) {
				visited[w] = 1;
				printf("%d ", G.vertices[w].key);
				elem[front + length] = w;
				length++;
			}
		}
	}
}