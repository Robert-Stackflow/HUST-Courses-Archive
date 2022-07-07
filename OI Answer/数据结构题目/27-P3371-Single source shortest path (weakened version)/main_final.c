#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#define INF 2147483647

struct Edge { //前向星存边
	int child;//此边的子节点
	int value;//此边的权值
	int brother;//与它最近的父节点一样的边的编号
} edge[500010];
int n, m, s, u, v, w, top, head[20000], visited[20000], pos;
long long  distance[20000], minn;

int main() {
	scanf("%d%d%d", &n, &m, &s);
	for (int i = 1; i <= n; i++)
		distance[i] = INF;
	for (int i = 0; i < m; i++) {
		scanf("%d%d%d", &u, &v, &w);
		edge[++top].child = v;
		edge[top].value = w;
		edge[top].brother = head[u];
		head[u] = top;
	}
	pos = s;
	distance[s] = 0;
	while (!visited[pos]) {
		visited[pos] = 1;
		for (int i = head[pos]; i != 0; i = edge[i].brother)
			if (!visited[edge[i].child] && distance[edge[i].child] > distance[pos] + edge[i].value)
				distance[edge[i].child] = distance[pos] + edge[i].value;
//		for (int i = 1; i <= n; i++)
//			printf("%lld ", distance[i]);
//		printf("\n");
		minn = INF;
		for (int i = 1; i <= n; i++)
			if (!visited[i] && minn > distance[i])
				minn = distance[i], pos = i;
	}
	for (int i = 1; i <= n; i++)
		printf("%lld ", distance[i]);
	return 0;
}