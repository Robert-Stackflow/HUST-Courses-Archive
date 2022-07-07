#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxn  65535
#define MaxVertexNum 200005

struct Graph {
	int vexnum;
	int arcnum;
	int arc[5005][5005];
};

int n, m;
struct Graph G;

void CreateGraph() {
	scanf("%d%d", &n, &m);
	int vex1, vex2, weight;
	for (int i = 1; i <= m; i++) {
		scanf("%d%d%d", &vex1, &vex2, &weight);
		if (!G.arc[vex1 - 1][vex2 - 1] || (G.arc[vex1 - 1][vex2 - 1] && G.arc[vex1 - 1][vex2 - 1] > weight)) {
			G.arc[vex1 - 1][vex2 - 1] = weight;
			G.arc[vex2 - 1][vex1 - 1] = weight;
		}

	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (!G.arc[i][j])
				G.arc[i][j] = maxn;

	G.arcnum = m;
	G.vexnum = n;
//	for (int i = 0; i < n; i++) {
//		for (int j = 0; j < n; j++)
//			printf("%d\t", G.arc[i][j]);
//		printf("\n");
//	}
}

int Prim() {
	int min, i, j, k, ans = 0, cnt = 1;
	int lowcost[MaxVertexNum];
	int adjvex[MaxVertexNum];
	lowcost[0] = 0;
	adjvex[0] = 0;
	for (i = 1; i < G.vexnum; ++i) {
		lowcost[i] = G.arc[0][i];
		adjvex[i] = 0;
	}//初始化数组为第一个顶点的邻接点的各个权值

	for (i = 1;  i < G.vexnum ; i++) {
		min = 65535;
		j = 0;
		k = 0;
		//选出权值最小的
		while (j < G.vexnum) {
			if (lowcost[j] != 0 && lowcost[j] != maxn && lowcost[j] < min) {
				min = lowcost[j];
				k = j;
			}
			j++;
		}
		if (min != maxn) {
			ans += min;
			cnt++;
		}
//		printf("%d->%d 当前权值：%d  当前点数：%d\n", adjvex[k] + 1, k + 1, ans, cnt);
		lowcost[k] = 0; //等于0的话代表这个顶点已经加入生成树 下次取权值不会在用到它。
		//更新lowcost数组
		for (j = 0;  j < G.vexnum ; j++) {
			if (lowcost[j] != 0 && G.arc[k][j] < lowcost[j]) {
				lowcost[j] = G.arc[k][j];
				adjvex[j] = k;
			}
		}
	}
	if (cnt != n)
		return -1;
	else
		return ans;
}

int main(void) {
	CreateGraph();
	int res = Prim();
	if (res == -1)
		printf("orz");
	else
		printf("%d", res);
	return 0;
}