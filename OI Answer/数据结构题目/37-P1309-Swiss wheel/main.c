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

void merge(Data *a, int n, Data *b, Data *t) {
	int i, j, k;
	i = j = k = 1;
	while (i <= n && j <= n) {
		if (a[i].score > b[j].score || (a[i].score == b[j].score && a[i].num < b[j].num)) {
			t[k].num = a[i].num;
			t[k].power = a[i].power;
			t[k++].score = a[i++].score;
		} else {
			t[k].num = b[j].num;
			t[k].power = b[j].power;
			t[k++].score = b[j++].score;
		}
	}
	while (i <= n) {
		t[k].num = a[i].num;
		t[k].power = a[i].power;
		t[k++].score = a[i++].score;
	}
	while (j <= n) {
		t[k].num = b[j].num;
		t[k].power = b[j].power;
		t[k++].score = b[j++].score;
	}
}

int main(void) {
	int n, r, q;
	scanf("%d%d%d", &n, &r, &q);
	Data *win = (Data *)malloc(sizeof(Data) * (n + 1));
	Data *lose = (Data *)malloc(sizeof(Data) * (n + 1));
	Data *top = (Data *)malloc(sizeof(Data) * (n + 1) * 2);
	for (int i = 1; i <= 2 * n; i++) {
		scanf("%d", &top[i].score);
		top[i].num = i;
	}
	for (int i = 1; i <= 2 * n; i++)
		scanf("%d", &top[i].power);
	qsort(top + 1, n * 2, sizeof(top[0]), comp);
	for (int i = 1; i <= r; i++) {
		int flag = 1;
		for (int j = 1; j < n * 2; j += 2) {
			if (top[j].power > top[j + 1].power) {
				win[flag].score = top[j].score + 1;
				win[flag].num = top[j].num;
				win[flag].power = top[j].power;
				lose[flag].score = top[j + 1].score;
				lose[flag].num = top[j + 1].num;
				lose[flag].power = top[j + 1].power;
			} else {
				win[flag].score = top[j + 1].score + 1;
				win[flag].num = top[j + 1].num;
				win[flag].power = top[j + 1].power;
				lose[flag].score = top[j].score;
				lose[flag].num = top[j].num;
				lose[flag].power = top[j].power;
			}
			flag++;
		}
		merge(win, n, lose, top);
	}
//	printf("num\tpower\tscore\t\n");
//	for (int i = 1; i <= n * 2; i++)
//		printf("%d\t%d\t%d\t\n", top[i].num, top[i].power, top[i].score);
	printf("%d", top[q].num);
	return 0;
}
