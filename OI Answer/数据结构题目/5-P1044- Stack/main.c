#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
	int n;
	scanf("%d", &n);
	unsigned long long dfs[25][25];
	for (int i = 0; i <= n; i++) {
		dfs[0][i] = 1;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = i; j <= n; j++) {
			if (i == j)
				dfs[i][j] = dfs[i - 1][j];
			else
				dfs[i][j] = dfs[i][j - 1] + dfs[i - 1][j];
		}
	}
	printf("%llu", dfs[n][n]);
	return 0;
}