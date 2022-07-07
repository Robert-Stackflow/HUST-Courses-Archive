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
	Next(T); //����ģʽ��T,��ʼ��next����
	int i = 0;
	int j = 0;
	while (i < len1) {
		//j==0:����ģʽ���ĵ�һ���ַ��ͺ͵�ǰ���Ե��ַ�����ȣ�S[i]==T[j],�����Ӧλ���ַ���ȣ���������£�ָ��ǰ���Ե�����ָ���±�i��j�������
		if (j == -1 || S[i] == T[j]) {
			i++;
			j++;
		} else {
			j = next[j]; //������Ե������ַ�����ȣ�i������j��Ϊ��ǰ�����ַ�����nextֵ
		}
		if (j == len2) {
			//�������Ϊ�棬˵��ƥ��ɹ�
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