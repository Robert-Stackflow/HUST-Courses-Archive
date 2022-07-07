#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxn 10005

int comp(const void *a, const void *b) {
	return *(int *)a - *(int *)b;
}

int main(void) {
	int n, k, num[maxn], count = 0, flag;
	scanf("%d%d", &n, &k);
	num[0] = -1;
	for (int i = 1; i <= n; i++)
		scanf("%d", &num[i]);
	qsort(num + 1, n, sizeof(int), comp);
//	for (int i = 1; i <= n; i++)
//		printf("%d ", num[i]);
//	printf("\n");
	for (flag = 1; flag <= n; flag++) {
		if (num[flag] == num[flag - 1])
			continue;
		else
			count++;
		if (count == k)
			break;
	}
	if (count < k)
		printf("NO RESULT");
	else
		printf("%d", num[flag]);
	return 0;
}