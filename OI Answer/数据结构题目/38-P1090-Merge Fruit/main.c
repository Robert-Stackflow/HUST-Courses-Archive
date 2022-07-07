#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxn 10005

int comp(const void *a, const void *b) {
	return *(int *)a - *(int *)b;
}

void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

int main(void) {
	int n, a[maxn], j, sum = 0;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	qsort(a + 1, n, sizeof(int), comp);
	for (; n != 1;) {
		j = 1;
		a[j] += a[j + 1];
		sum += a[j];
		for (int i = j + 1; i < n; i++)
			a[i] = a[i + 1];
		n--;
		for (int i = j; i < n; i++)
			if (a[i] > a[i + 1])
				swap(&a[i], &a[i + 1]);
	}
	printf("%d", sum);
	return 0;
}
