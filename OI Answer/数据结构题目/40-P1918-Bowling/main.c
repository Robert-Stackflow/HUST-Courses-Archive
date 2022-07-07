#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxn 100005
//结构体快排，二分查找，桶排序
typedef struct {
	int num;
	int pos;
} Data;

int comp(const void *a, const void *b) {
	Data c = *(Data *)a;
	Data d = *(Data *)b;
	//按个数升序排序
	return c.num - d.num;
}

int main(void) {
	int n, m, p;
	Data in[maxn];
	scanf("%d", &n) ;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &in[i].num);
		in[i].pos = i;
	}
	qsort(in + 1, n, sizeof(in[0]), comp);
	//使用结构体快排函数，在<stdlib.h>函数中
	scanf("%d", &m);
	for (int i = 1; i <= m; i++) {
		scanf("%d", &p);
		int r = n + 1, l = 0, mid = 0;
		while (l + 1 < r) {
			mid = (r + l) / 2;
			if (in[mid].num < p)
				l = mid;
			else
				r = mid;
		}
		if (in[r].num != p)
			printf("0\n");
		else
			printf("%d\n", in[r].pos);
	}
	return 0;
}