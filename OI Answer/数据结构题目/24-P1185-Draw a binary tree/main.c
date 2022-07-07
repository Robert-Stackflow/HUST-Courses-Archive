#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

char map[3100][3100];
int PosofFirst[15], LengthofTrunk[15], HeightofLevel[15];
void IniTree(int i, int j, int level);
void Remove(int i, int j);

int main(void) {
	int m, n, i, j, pos, mid = 1;
	scanf("%d%d", &m, &n);
	HeightofLevel[m] = LengthofTrunk[1] = PosofFirst[1] = 1;
	for (int i = 2; i <= m; i++) {
		LengthofTrunk[i] = mid + i - 1;
		mid += LengthofTrunk[i];
		PosofFirst[i] = LengthofTrunk[i] + 1;
	}
	for (int i = m - 1; i > 0; i--)
		HeightofLevel[i] = HeightofLevel[i + 1] + LengthofTrunk[i] + 1;
	for (int i = 1; i <= HeightofLevel[1]; i++)
		for (int j = 1; j <= ((int)pow(2, m - 1)) * 6; j++)
			map[i][j] = ' ';
	IniTree(1, PosofFirst[m], m);
	for (int k = 1; k <= n; k++) {
		scanf("%d%d", &i, &j);
//		if (i > 10)continue;
		if (i == m)
			j = PosofFirst[1] + j / 2 * 6 - ((j & 1) ? 0 : 2);
		else
			j = PosofFirst[m + 1 - i] + (j - 1) * (2 * LengthofTrunk[m + 1 - i] + 2);
		Remove(HeightofLevel[m - i + 1], j);
	}
	for (int i = 1; i <= HeightofLevel[1]; i++) {
		for (int j = 1; j <= ((int)pow(2, m - 1)) * 6; j++)
			printf("%c", map[i][j]);
		printf("\n");
	}
	return 0;
}

void IniTree(int i, int j, int level) {
	map[i][j] = 'o';
	if (level == 1)//说明在画最后一层，return
		return;
	int li = i + 1, lj = j - 1, ri = i + 1, rj = j + 1;
	for (int i = 1; i <= LengthofTrunk[level - 1]; i++) {
		map[ri][rj] = '\\';
		map[li][lj] = '/';
		li = li + 1, lj = lj - 1;
		ri = ri + 1, rj = rj + 1;
		//向左下方和右下方延伸画图
	}
	IniTree(li, lj, level - 1);//画左下层
	IniTree(ri, rj, level - 1);//画右下层
}

void Remove(int i, int j) {
	map[i][j] = ' ';
	if (map[i - 1][j - 1] == '\\')
		Remove(i - 1, j - 1);
	if (map[i - 1][j + 1] == '/')
		Remove(i - 1, j + 1);
	if (map[i + 1][j - 1] == '/' || map[i + 1][j - 1] == 'o')
		Remove(i + 1, j - 1);
	if (map[i + 1][j + 1] == '\\' || map[i + 1][j + 1] == 'o')
		Remove(i + 1, j + 1);
}