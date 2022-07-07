#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int dirx[4] = {1, -1, 0, 0}, diry[4] = {0, 0, 1, -1};
int map[105][105], money[105][105];
int m, n, i, j, color;
void DFS(int x, int y, int flag) {
	for (int i = 0; i < 4; i++) { //四周走
		int x1 = x + dirx[i], y1 = y + diry[i]; //新坐标
		if (x1 >= 1 && x1 <= m && y1 >= 1 && y1 <= m) { //未越界
			int temp = -1; //记录花费
			if (map[x][y] == map[x1][y1] && map[x1][y1] != -1) temp = 0; //同色无花费
			else { //不同色或者无色
				if (map[x1][y1] != -1) temp = 1; //不同色花费
				if (map[x1][y1] == -1 && flag) temp = 2; //前格有色本格无色使用魔法
			}
			if (temp == -1) continue; //前后格均无色，回溯
			if (money[x][y] + temp < money[x1][y1] || !money[x1][y1]) { //当前格已经走过，但新走法花费少
				money[x1][y1] = money[x][y] + temp; //更新花费
				if (temp == 2) { //若使用魔法
					map[x1][y1] = map[x][y]; //记录颜色
					DFS(x1, y1, 0); //继续搜索
					map[x1][y1] = -1; //恢复颜色
				} else DFS(x1, y1, 1); //若有色则无需操作继续搜索
			}
		}
	}
}
int main(void) {
	scanf("%d%d", &m, &n);
	for (int k = 1; k <= m; k++)
		for (int p = 1; p <= m; p++)
			map[k][p] = -1;
	for (int k = 1; k <= n; k++)
		scanf("%d%d%d", &i, &j, &color), map[i][j] = color;
//	for (int k = 1; k <= m; k++) {
//		for (int p = 1; p <= m; p++)
//			printf("%d ", map[k][p]);
//		printf("\n");
//	}
	money[1][1] = 1;
	DFS(1, 1, 1);
	printf("%d", money[m][m] - 1);
	return 0;
}
