#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int power;
	int score;
	int num;
} Data;

int comp(const void *a, const void *b) {
	Data c = *(Data *)a;
	Data d = *(Data *)b;
	//∞¥∑÷ ˝…˝–Ú≈≈–Ú
	return d.score - c.score;
}

int main(void) {
	int n, r, q;
	scanf("%d%d%d", &n, &r, &q);
	Data *top = (Data *)malloc(sizeof(Data) * (n * 2 + 5));
	for (int i = 1; i <= 2 * n; i++) {
		scanf("%d", &top[i].score);
		top[i].num = i;
	}
	for (int i = 1; i <= 2 * n; i++)
		scanf("%d", &top[i].power);
	for (int i = 1; i <= r; i++) {
		qsort(top + 1, n * 2, sizeof(top[0]), comp);
		for (int j = 1; j <= n * 2 - 1; j += 2) {
			if (top[j].power > top[j + 1].power)
				top[j].score++;
			else
				top[j + 1].score++;
		}
	}
	qsort(top + 1, n * 2, sizeof(top[0]), comp);
//	printf("num\tpower\tscore\t\n");
//	for (int i = 1; i <= n * 2; i++)
//		printf("%d\t%d\t%d\t\n", top[i].num, top[i].power, top[i].score);
	printf("%d", top[q].num);
	return 0;
}
