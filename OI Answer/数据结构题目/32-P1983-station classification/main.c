#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
	int n, m, res = 0, q = 0;
	int count[1005] = {0}, sign[1005] = {0}, rank[1005][1005] = {0};
	//flag����������ʶ��Щ��վͣ������Щ�㱻ɾ��
	//count����������ʶ
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) {
		int road[1005] = {0}, flag[1005] = {0};
		scanf("%d", &road[0]);
		for (int j = 1; j <= road[0]; j++) {
			scanf("%d", &road[j]);
			flag[road[j]] = 1;
		}
		for (int k = road[1]; k <= road[road[0]]; k++)
			if (!flag[k]) //�����վ�㲻ͣ����ô�ͽ��������������ͣ��վ������ȼ�
				for (int p = 1; p <= road[0]; p++) //�൱�ڽ���һ������ͼ
					if (!rank[k][road[p]])
						rank[k][road[p]] = 1, count[road[p]]++;
	}
	do {
		q = 0;
		for (int i = 1; i <= n; i++) //ɾȥ��ǰ���ȼ���͵ĵ�
			if (!count[i])
				sign[++q] = i, count[i] = -1;
		for (int i = 1; i <= q; i++ )
			for (int j = 1; j <= n; j++)
				if (rank[sign[i]][j])
					rank[sign[i]][j] = 0, count[j]--;//ɾȥ�뱻ɾ����صıߣ�������Ӧ���ȼ�1
		res++;//���Ӽ���
	} while (q);
	printf("%d", res - 1);
	return 0;
}
