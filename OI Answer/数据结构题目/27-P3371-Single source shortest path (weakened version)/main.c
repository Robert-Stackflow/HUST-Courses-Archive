#include <stdio.h>
#include <stdlib.h>
#define maxn 2147483647
#define MAX 1005
int n, m, s;
int G[MAX][MAX];
int path[MAX];

int ShortPath() {
	int i, j;
	int min, minid;
	int tmp;
	int prev[MAX] = {0};
	int dist[MAX] = {2147483647};
	int visited[MAX];
	//visited[i]=1表示"顶点s"到"顶点i"的最短路径已成功获取
	s--;
	for (i = 0; i < n; i++) {
		visited[i] = 0;              // 顶点i的最短路径还没获取到。
		prev[i] = 0;              // 顶点i的前驱顶点为0。
		dist[i] = G[s][i];// 顶点i的最短路径为"顶点s"到"顶点i"的权。
	}
	// 对"顶点s"进行初始化
	visited[s] = 1;//将顶点s加入最短路径，对应的visited[i]置为1
	dist[s] = 0;//到自己的权为0
	// 遍历G.vexnum-1次；每次找出一个顶点的最短路径。
	for (i = 1; i < n; i++) {
		// 寻找当前最小的路径；
		// 即，在未获取最短路径的顶点中，找到离s最近的顶点(minid)。
		min = maxn;
		for (j = 0; j < n; j++) {
			if (visited[j] == 0 && dist[j] < min) {
				min = dist[j];
				minid = j;
			}
		}
		visited[minid] = 1;// 标记"顶点minid"为已经获取到最短路径
		// 更新当前最短路径和前驱顶点
		// 即，当已经"顶点minid的最短路径"之后，更新"未获取最短路径的顶点的最短路径和前驱顶点"。
		for (j = 0; j < n; j++) {
			tmp = ((G[minid][j] == maxn) ? maxn : (min + G[minid][j])); // 防止溢出
			if (visited[j] == 0 && (tmp  < dist[j]) ) {
				dist[j] = tmp;
				prev[j] = minid;
			}
		}
	}
	for (i = 0; i < n; i++)
		printf("%d ", dist[i]);
}

int main(void) {
	scanf("%d%d%d", &n, &m, &s);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			if (i == j)
				continue;
			else
				G[i][j] = maxn;
		}//初始化数组，除了主对角线均置为maxn
	for (int i = 1; i <= m; i++) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		G[u - 1][v - 1] = w;
	}//读入数据更新有向图
	ShortPath();
	return 0;
}
