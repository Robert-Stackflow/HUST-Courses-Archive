#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
	int n, m, res = 0, q = 0;
	int count[1005] = {0}, sign[1005] = {0}, rank[1005][1005] = {0};
	//flag数组用来标识哪些车站停靠和哪些点被删除
	//count数组用来标识
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) {
		int road[1005] = {0}, flag[1005] = {0};
		scanf("%d", &road[0]);
		for (int j = 1; j <= road[0]; j++) {
			scanf("%d", &road[j]);
			flag[road[j]] = 1;
		}
		for (int k = road[1]; k <= road[road[0]]; k++)
			if (!flag[k]) //如果该站点不停靠那么就降低相对于所有已停靠站点的优先级
				for (int p = 1; p <= road[0]; p++) //相当于建立一张网络图
					if (!rank[k][road[p]])
						rank[k][road[p]] = 1, count[road[p]]++;
	}
	do {
		q = 0;
		for (int i = 1; i <= n; i++) //删去当前优先级最低的点
			if (!count[i])
				sign[++q] = i, count[i] = -1;
		for (int i = 1; i <= q; i++ )
			for (int j = 1; j <= n; j++)
				if (rank[sign[i]][j])
					rank[sign[i]][j] = 0, count[j]--;//删去与被删点相关的边，并将对应出度减1
		res++;//增加计数
	} while (q);
	printf("%d", res - 1);
	return 0;
}
