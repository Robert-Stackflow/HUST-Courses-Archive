#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max(x,y) ((x)>=(y)?(x):(y))

typedef struct BitNode {
	int child1, child2;
} Tree;
Tree tree[1000005];
int n, maxn;

void DFS(int num, int depth) {
	if (num == 0)
		return;
	maxn = max(maxn, depth);
	DFS(tree[num].child1, depth + 1);
	DFS(tree[num].child2, depth + 1);
}

int main(void) {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d%d", &tree[i].child1, &tree[i].child2);
	DFS(1, 1);
	printf("%d\n", maxn);
	return 0;
}