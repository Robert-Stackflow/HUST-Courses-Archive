#include <stdio.h>
#include <stdlib.h>
#define size 10005
int father[size], rank[size];

void IniUFS(int n) {
	int i;
	for (i = 1; i < n; ++i) {
		father[i] = i;
		rank[i] = 1;
	}
}

int FindRoot(int node) {
	if (father[node] != node) {
		father[node] = FindRoot(father[node]);
	}
	return father[node];
}

int  AllyUFS(int p, int q) {
	int root1 = FindRoot(p);
	int root2 = FindRoot(q);
	if (root1 == root2)
		return 0;
	if (rank[root1] > rank[root2]) {
		father[root2] = root1;        //小树连接到大树上,并且权值加至合并后的树上，表示这个树有多少个子节点（压缩存储）
		rank[root1] += rank[root2];
	} else {
		father[root1] = root2;
		rank[root2] += rank[root1];
	}
	return 1;
}

int Judge(int p, int q) {
	int root1 = FindRoot(p);
	int root2 = FindRoot(q);
	if (root1 == root2)
		return 1;
	else
		return 0;
}

int main(void) {
	int n, m;
	scanf("%d%d", &n, &m);
	IniUFS(n + 5);
	for (int i = 1; i <= m; i++) {
		int op, x, y;
		op = x = y = 0;
		scanf("%d%d%d", &op, &x, &y);
		if (op == 1)
			AllyUFS(x, y);
		else {
			int ans = Judge(x, y);
			if (ans)
				printf("Y\n");
			else
				printf("N\n");
		}
	}
	return 0;
}