#include <stdio.h>
#include <string.h>
#define maxn 1000005
int next[maxn];
int len1, len2;

void Next(char *T) {
	int i = 0;
	next[0] = -1;
	int j = -1;
	while (i < len2) {
		if (j == -1 || T[i] == T[j]) {
			i++;
			j++;
			next[i] = j;
		} else {
			j = next[j];
		}
	}
}

void KMP(char *S, char *T) {
	Next(T); //根据模式串T,初始化next数组
	int i = 0;
	int j = 0;
	while (i < len1) {
		//j==0:代表模式串的第一个字符就和当前测试的字符不相等；S[i]==T[j],如果对应位置字符相等，两种情况下，指向当前测试的两个指针下标i和j都向后移
		if (j == -1 || S[i] == T[j]) {
			i++;
			j++;
		} else {
			j = next[j]; //如果测试的两个字符不相等，i不动，j变为当前测试字符串的next值
		}
		if (j == len2) {
			//如果条件为真，说明匹配成功
			printf("%d\n", i - (int)len2 + 1);
			j = next[j];
		}
	}
}

int main() {
	char s1[maxn], s2[maxn];
	scanf("%s%s", s1, s2);
	len1 = strlen(s1);
	len2 = strlen(s2);
	KMP(s1, s2);
	for (int i = 1; i <= strlen(s2); i++)
		printf("%d ", next[i]);
	return 0;
}