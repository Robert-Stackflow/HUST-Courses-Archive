#include <stdio.h>
#include <stdlib.h>
int num[1000005], queue[1000005], order[1000005], l = 1, r;
#define min(x,y) ((x)<(y)?:(x):(y))
#define max(x,y) ((x)>(y)?:(x):(y))
#define maxn

int main(void) {
	int n, k, cnt = 0;
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++)
		scanf("%d", &num[i]);
	for (int i = 1; i <= n; ++i) {
		while (l <= r && queue[r] >= num[i])
			r--;
		queue[++r] = num[i];
		order[r] = i;
		while (order[l] <= i - k)
			l++;
		if (i >= k)
			printf("%d ", queue[l]);
	}
	printf("\n");
	l = 1;
	r = 0;
	for (int i = 1; i <= n; ++i) {
		while (l <= r && queue[r] <= num[i])
			r--;
		queue[++r] = num[i];
		order[r] = i;
		while (order[l] <= i - k)
			l++;
		if (i >= k)
			printf("%d ", queue[l]);
	}
	return 0;
}