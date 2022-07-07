#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define min(x,y) ((x)<(y)?(x):(y))
int n, m;
int map[10005];
int danger[105][105];

int main(void) {
	int ans = 0;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++)
		scanf("%d", &map[i]);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			scanf("%d", &danger[i][j]);
	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				danger[i][j] = min(danger[i][k] + danger[k][j], danger[i][j]);
			}
		}
	}
	for (int i = 2; i <= m; i++) {
		ans += danger[map[i - 1]][map[i]]; //¼ÆÊý
	}
	printf("%d", ans);
	return 0;
}