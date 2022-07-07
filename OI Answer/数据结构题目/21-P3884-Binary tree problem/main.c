#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max(x,y) ((x)>=(y)?(x):(y))
int n, maxn = 1, tree, child;
int parent[105], depth[105], width[105];

int  NearestCommonAncestor(int u, int v) {
	if (u == v)
		return u;
	else if (depth[u] == depth[v])
		return NearestCommonAncestor(parent[u], parent[v]);
	else if (depth[u] < depth[v])
		return NearestCommonAncestor(u, parent[v]);
	else
		return NearestCommonAncestor(parent[u], v);
}

int main(void) {
	depth[1] = 1;
	scanf("%d", &n);
	for (int i = 1; i < n; i++) {
		scanf("%d%d", &tree, &child);
		parent[child] = tree;//标识孩子节点的父节点
		depth[child] = depth[tree] + 1;//标识该孩子节点的深度是父节点深度+1
	}
//	for (int i = 1; i <= n; i++)
//		printf("%d %d %d\n", i, parent[i], depth[i]);
//	printf("\n");
	for (int i = 1; i <= n; i++) {
		maxn = max(maxn, depth[i]);
		width[depth[i]]++;
	}
	printf("%d\n", maxn);
	maxn = 1;
	for (int i = 1; i <= n; i++)
		maxn = max(maxn, width[i]);
	printf("%d\n", maxn);
	int u, v, ancestor;
	scanf("%d%d", &u, &v);
	ancestor = NearestCommonAncestor(u, v);
	printf("%d", (depth[u] - depth[ancestor]) * 2 + depth[v] - depth[ancestor]);
	return 0;
}