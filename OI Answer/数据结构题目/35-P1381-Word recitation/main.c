#include <stdio.h>
#include <stdlib.h>
#include <string.h>
const int MOD = 1000100;
const int MUL = 37;
#define maxn 1000100
#define min(x,y) ((x)<(y)?(x):(y))
long long Hash(char *str) {
	long long res = 0;
	for (int i = 0; i < strlen(str); i++) {
		res = res * MUL + str[i] - 'a';
		res %= MOD;
	}
	return res % MOD;
}

int main(void) {
	int n, m, appeared, res, len =1e10;
	char mid[15];
	long long a[1005], b[100005];
	int visited[maxn] = {0}, todo[maxn] = {0}, count[maxn] = {0};
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%s", mid);
		a[i] = Hash(mid);
		todo[a[i]] = 1;
	}
	scanf("%d", &m);
	appeared = 0;
	for (int i = 1; i <= m; i++) {
		scanf("%s", mid);
		b[i] = Hash(mid);
		if (todo[b[i]] && !visited[b[i]]) {
			visited[b[i]] = 1;
			appeared++;
		}
	}
	res = appeared;
	if (!appeared) {
		printf("0\n0");
		return 0;
	}
	int l = 1, r = 1;
	while (1) {
		if (appeared) {
			if (r > m)
				break;
			if (visited[b[r]]) {
				if (count[b[r]] == 0)
					appeared--;
				count[b[r]]++;
			}
			r++;
		} else {
			while (!visited[b[l]])
				l++;
			if (l > m)
				break;
			len = min(len,r-l);
			if (count[b[l]] == 1)
				appeared++;
			if (count[b[l]] >= 1) {
				count[b[l]]--;
				l++;
			}
		}
	}
	printf("%d\n%d", res, len);
	return 0;
}