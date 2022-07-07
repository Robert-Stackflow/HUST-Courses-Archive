#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
	int n, p, i, j, k, bo = 0;
	scanf("%d%d", &n, &p);
	int state[105], u[105], map[105][105] = {0}, sum, flag[105] = {0};
	for (int i = 1; i <= n; i++)
		scanf("%d%d", &state[i], &u[i]);
	for (k = 1; k <= p; k++) {
		scanf("%d%d", &i, &j);
		flag[i] = 1;
		scanf("%d", &map[i][j]);
	}
	/////////////////////////////////////////////////////////
//	printf("\n");
//	for (k = 1; k <= n; k++) {
//		for (int m = 1; m <= n; m++)
//			printf("%d ", map[k][m]);
//		printf("\n");
//	}
//	printf("\n");
//	for (int m = 1; m <= n; m++)
//		printf("%d ", state[m]);
//	printf("\n=======\n");
	/////////////////////////////////////////////////////////
	for (k = 1; k <= n; k++) {
		sum = bo = 0;
		for (int m = 1; m <= n; m++) {
			if (!map[m][k] || state[m] <= 0)
				continue;
			else
				sum += map[m][k] * state[m], bo++;
		}
		if (bo)
			state[k] = sum - u[k];
		/////////////////////////////////////////////////////////
//		printf("\n");
//		for (int m = 1; m <= n; m++)
//			printf("%d ", state[m]);
//		printf("\n");
		/////////////////////////////////////////////////////////
	}
	bo = 0;
	for (k = 1; k <= n; k++)
		if (!flag[k] && state[k] > 0)
			printf("%d %d\n", k, state[k]), bo++;
	if (!bo)
		printf("NULL");
	return 0;
}
