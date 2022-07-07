#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
	int n, top = 0;
	scanf("%d", &n);
	int stack[3000005], num[3000005], f[3000005];
	for (int i = 1; i <= n; i++)
		scanf("%d", &num[i]);
	for (int i = n; i >= 1; i--) {
		while (top > 0 && num[stack[top]] <= num[i])
			top--; //���ջ��Ϊ�ն���ջ��С�ڵ��ڵ�ǰԪ�����ջ
		f[i] = !top ? 0 : stack[top];//���ջΪ����û�б�����������Ϊ0������Ϊջ��Ԫ��
		stack[++top] = i;//�±���ջ
	}
	for (int i = 1; i <= n; i++)
		printf("%d ", f[i]);
	return 0;
}