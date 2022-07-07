#include <stdio.h>
int n, map[35][35], dirx[4] = {0, 0, -1, 1}, diry[4] = {-1, 1, 0, 0};
void DFS(int x, int y) {
	if (x < 0 || x > n + 1 || y < 0 || y > n + 1 || map[x][y] != 0)
		return;
	map[x][y] = -1;
	for (int i = 0; i < 4; i++)
		DFS(x + dirx[i], y + diry[i]);
}

int main(void) {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			scanf("%d", &map[i][j]);
	DFS(0, 0);
//	printf("\n\n");
//	for (int i = 1; i <= n; i++) {
//		for (int j = 1; j <= n; j++)
//			printf("%d ", map[i][j]);
//		printf("\n");
//	}
//	printf("\n\n");
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (!map[i][j])
				printf("2 ");
			else if (map[i][j] == -1)
				printf("0 ");
			else
				printf("1 ");
		}
		printf("\n");
	}
	return 0;
}