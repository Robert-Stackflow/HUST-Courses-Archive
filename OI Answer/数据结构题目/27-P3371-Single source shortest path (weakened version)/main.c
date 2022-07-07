#include <stdio.h>
#include <stdlib.h>
#define maxn 2147483647
#define MAX 1005
int n, m, s;
int G[MAX][MAX];
int path[MAX];

int ShortPath() {
	int i, j;
	int min, minid;
	int tmp;
	int prev[MAX] = {0};
	int dist[MAX] = {2147483647};
	int visited[MAX];
	//visited[i]=1��ʾ"����s"��"����i"�����·���ѳɹ���ȡ
	s--;
	for (i = 0; i < n; i++) {
		visited[i] = 0;              // ����i�����·����û��ȡ����
		prev[i] = 0;              // ����i��ǰ������Ϊ0��
		dist[i] = G[s][i];// ����i�����·��Ϊ"����s"��"����i"��Ȩ��
	}
	// ��"����s"���г�ʼ��
	visited[s] = 1;//������s�������·������Ӧ��visited[i]��Ϊ1
	dist[s] = 0;//���Լ���ȨΪ0
	// ����G.vexnum-1�Σ�ÿ���ҳ�һ����������·����
	for (i = 1; i < n; i++) {
		// Ѱ�ҵ�ǰ��С��·����
		// ������δ��ȡ���·���Ķ����У��ҵ���s����Ķ���(minid)��
		min = maxn;
		for (j = 0; j < n; j++) {
			if (visited[j] == 0 && dist[j] < min) {
				min = dist[j];
				minid = j;
			}
		}
		visited[minid] = 1;// ���"����minid"Ϊ�Ѿ���ȡ�����·��
		// ���µ�ǰ���·����ǰ������
		// �������Ѿ�"����minid�����·��"֮�󣬸���"δ��ȡ���·���Ķ�������·����ǰ������"��
		for (j = 0; j < n; j++) {
			tmp = ((G[minid][j] == maxn) ? maxn : (min + G[minid][j])); // ��ֹ���
			if (visited[j] == 0 && (tmp  < dist[j]) ) {
				dist[j] = tmp;
				prev[j] = minid;
			}
		}
	}
	for (i = 0; i < n; i++)
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
	ShortPath();
	return 0;
}
