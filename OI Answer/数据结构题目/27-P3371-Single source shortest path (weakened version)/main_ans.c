#include <stdio.h>
#include <stdlib.h>
#define maxn 2147483647
#define MAX 10005
int n, m, s;
int G[MAX][MAX];
int path[MAX];
int dist[MAX]; //����ĵ�i��Ԫ�ر�ʾ��Դ�ڵ㵽�ڵ�i����̾���,��ʼ��Ϊ�����
int path[MAX]; //����ĵ�i��Ԫ�ر�ʾ��i���ڵ��·��״̬����ʼ��Ϊ-1
int order[MAX];//����ĵ�i��Ԫ�ش����i���ڵ㴦�ڵĲ���
int ShortPath(int v0) {
	int v, w;
	int Order;
	path[v0 - 1] = 0;
	dist[v0 - 1] = 0;
	order[v0 - 1] = 1;//Դ��ĳ�ʼ��������Ϊ1
	for (Order = 1; Order <= n; Order++) {
		for (v = 0; v < n; v++) {
			if (order[v] == Order) { //����ͬһ���ϵĽڵ�
				for (w = 0; w < n; w++) {
					if (G[v][w] != maxn && dist[w] > dist[v] + G[v][w])
						//w��v�ڽ�&&w��Դ��ľ������v��Դ��ľ������v��w�ľ���
					{
						dist[w] = dist[v] + G[v][w];
						path[w] = v + 1;
						order[w] = Order + 1;
					}
				}
			}

		}
	}
	for (int i = 0; i < n; i++)
		printf("%d ", dist[i]);
}

int main(void) {
	scanf("%d%d%d", &n, &m, &s);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			if (i == j)
				continue;
			else
				G[i][j] = maxn;
		}//��ʼ�����飬�������Խ��߾���Ϊmaxn
	for (int i = 1; i <= m; i++) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		G[u - 1][v - 1] = w;
	}//�������ݸ�������ͼ
	for (int i = 0; i < MAX; i++)dist[i] = maxn, path[i] = -1;
	ShortPath(s);
	return 0;
}
