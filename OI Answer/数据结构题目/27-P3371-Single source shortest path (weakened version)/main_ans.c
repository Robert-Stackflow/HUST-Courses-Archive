#include <stdio.h>
#include <stdlib.h>
#define maxn 2147483647
#define MAX 10005
int n, m, s;
int G[MAX][MAX];
int path[MAX];
int dist[MAX]; //数组的第i个元素表示从源节点到节点i的最短距离,初始化为无穷大
int path[MAX]; //数组的第i个元素表示第i个节点的路径状态，初始化为-1
int order[MAX];//数组的第i个元素代表第i个节点处于的层数
int ShortPath(int v0) {
	int v, w;
	int Order;
	path[v0 - 1] = 0;
	dist[v0 - 1] = 0;
	order[v0 - 1] = 1;//源点的初始化，层序为1
	for (Order = 1; Order <= n; Order++) {
		for (v = 0; v < n; v++) {
			if (order[v] == Order) { //搜索同一层上的节点
				for (w = 0; w < n; w++) {
					if (G[v][w] != maxn && dist[w] > dist[v] + G[v][w])
						//w与v邻接&&w到源点的距离大于v到源点的距离加上v到w的距离
					{
						dist[w] = dist[v] + G[v][w];
						path[w] = v + 1;
						order[w] = Order + 1;
					}
				}
			}

		}
	}
	for (int i = 0; i < n; i++)
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
	for (int i = 0; i < MAX; i++)dist[i] = maxn, path[i] = -1;
	ShortPath(s);
	return 0;
}
