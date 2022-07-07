#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int dirx[4] = {1, -1, 0, 0}, diry[4] = {0, 0, 1, -1};
int map[105][105], money[105][105];
int m, n, i, j, color;
void DFS(int x, int y, int flag) {
	for (int i = 0; i < 4; i++) { //������
		int x1 = x + dirx[i], y1 = y + diry[i]; //������
		if (x1 >= 1 && x1 <= m && y1 >= 1 && y1 <= m) { //δԽ��
			int temp = -1; //��¼����
			if (map[x][y] == map[x1][y1] && map[x1][y1] != -1) temp = 0; //ͬɫ�޻���
			else { //��ͬɫ������ɫ
				if (map[x1][y1] != -1) temp = 1; //��ͬɫ����
				if (map[x1][y1] == -1 && flag) temp = 2; //ǰ����ɫ������ɫʹ��ħ��
			}
			if (temp == -1) continue; //ǰ������ɫ������
			if (money[x][y] + temp < money[x1][y1] || !money[x1][y1]) { //��ǰ���Ѿ��߹��������߷�������
				money[x1][y1] = money[x][y] + temp; //���»���
				if (temp == 2) { //��ʹ��ħ��
					map[x1][y1] = map[x][y]; //��¼��ɫ
					DFS(x1, y1, 0); //��������
					map[x1][y1] = -1; //�ָ���ɫ
				} else DFS(x1, y1, 1); //����ɫ�����������������
			}
		}
	}
}
int main(void) {
	scanf("%d%d", &m, &n);
	for (int k = 1; k <= m; k++)
		for (int p = 1; p <= m; p++)
			map[k][p] = -1;
	for (int k = 1; k <= n; k++)
		scanf("%d%d%d", &i, &j, &color), map[i][j] = color;
//	for (int k = 1; k <= m; k++) {
//		for (int p = 1; p <= m; p++)
//			printf("%d ", map[k][p]);
//		printf("\n");
//	}
	money[1][1] = 1;
	DFS(1, 1, 1);
	printf("%d", money[m][m] - 1);
	return 0;
}
