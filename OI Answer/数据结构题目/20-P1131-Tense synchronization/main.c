#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max(x,y) ((x)<(y)?(y):(x))
//��һ����������Ȩ�������� S��ÿ�ο��Ը�һ����Ȩ+1 ������ 1�Ĵ���
//����С����ʹ�� S ������Ҷ�Ӿ�����ȡ�
long long ans, dp[500005];
struct {
	int pre, next, weight;
} data[1000005];
int flag[500005], sign[500005];
void dfs(int a, int order) {
	for (int i = flag[a]; i; i = data[i].pre)
		if (!sign[data[i].next]) {
			sign[data[i].next] = 1;
			dfs(data[i].next, order);
			sign[data[i].next] = 0;
			if (order == 1)dp[a] = max(dp[a], dp[data[i].next] + data[i].weight);
			else  ans += dp[a] - dp[data[i].next] - data[i].weight;
		}
}
int main(void) {
	int n, begin, num = 0;
	scanf("%d%d", &n, &begin);
	for (int i = 1; i < n; i++) {
		int a, b, weight;
		scanf("%d%d%d", &a, &b, &weight);
		data[++num].pre = flag[a];
		data[num].next = b;
		data[num].weight = weight;
		flag[a] = num;
		data[++num].pre = flag[b];
		data[num].next = a;
		data[num].weight = weight;
		flag[b] = num;
	}
	sign[begin] = 1;
	dfs(begin, 1);
	for (int i = 1; i <= n; i++) sign[i] = 0;
	sign[begin] = 1;
	dfs(begin, 2);
	printf("%lld", ans);
	return 0;
}
