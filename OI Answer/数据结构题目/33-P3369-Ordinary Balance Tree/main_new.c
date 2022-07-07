#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#define INF INT_MAX
#define maxn 100010
#define max(x,y) ((x)<(y)?(y):(x))
#define min(x,y) ((x)>(y)?(y):(x))
int sum, R;
int size[maxn], v[maxn], num[maxn], rd[maxn], son[maxn][2];
// 用于重新统计以p为根节点的子树中元素个数
void pushup(int p) {
	size[p] = size[ son[p][0] ] + size[ son[p][1] ] + num[p];
}
// 左旋（d==0时），右旋（d==1时）
void rot(int *p, int d) {
	int k = son[*p][d ^ 1];
	son[*p][d ^ 1] = son[k][d];
	son[k][d] = *p;
	pushup(*p);
	pushup(k);
	*p = k;
}
// 插入一个数x
void ins(int *p, int x) {
	if (!(*p)) {
		*p = ++sum;
		size[*p] = num[*p] = 1;
		v[*p] = x;
		rd[*p] = rand();
		return;
	}
	if (v[*p] == x) {
		num[*p] ++;
		size[*p] ++;
		return;
	}
	int d = (x > v[*p]);
	ins(&son[*p][d], x);
	if (rd[*p] < rd[ son[*p][d] ]) rot(p, d ^ 1);
	pushup(*p);
}
// 删除一个数x
void del(int *p, int x) {
	if (!(*p)) return;
	if (x < v[*p]) del(&son[*p][0], x);
	else if (x > v[*p]) del(&son[*p][1], x);
	else {
		if (!son[*p][0] && !son[*p][1]) {
			num[*p] --;
			size[*p] --;
			if (!num[*p]) *p = 0;
		} else if (!son[*p][1]) {
			rot(p, 1);
			del(&son[*p][1], x);
		} else if (!son[*p][0]) {
			rot(p, 0);
			del(&son[*p][0], x);
		} else {
			int d = (rd[ son[*p][0] > rd[ son[*p][1] ] ]);
			rot(p, d);
			del(&son[*p][d], x);
		}
	}
	pushup(*p);
}
// 查询x数的排名
int get_rank(int p, int x) {
	if (!p) return 0;
	if (v[p] == x) return size[ son[p][0] ] + 1;
	if (v[p] < x) return size[ son[p][0] ] + num[p] + get_rank(son[p][1], x);
	if (v[p] > x) return get_rank(son[p][0], x);
}
// 查询排名为x的数
int func_find(int p, int x) {
	if (!p) return 0;
	if (size[ son[p][0] ] >= x) return func_find(son[p][0], x);
	else if (size[ son[p][0] ] + num[p] < x)
		return func_find(son[p][1], x - num[p] - size[ son[p][0] ]);
	else return v[p];
}
// 求x的前驱
int pre(int p, int x) {
	if (!p) return -INF;
	if (v[p] >= x) return pre(son[p][0], x);
	else return max(v[p], pre(son[p][1], x));
}
// 求x的后缀
int suc(int p, int x) {
	if (!p) return INF;
	if (v[p] <= x) return suc(son[p][1], x);
	else return min(v[p], suc(son[p][0], x));
}

int T, op, x;
int main() {
	scanf("%d", &T);
	while (T --) {
		scanf("%d%d", &op, &x);
		if (op == 1) ins(&R, x);
		else if (op == 2) del(&R, x);
		else if (op == 3) printf("%d\n", get_rank(R, x));
		else if (op == 4) printf("%d\n", func_find(R, x));
		else if (op == 5) printf("%d\n", pre(R, x));
		else if (op == 6) printf("%d\n", suc(R, x));
	}
	return 0;
}