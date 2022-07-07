#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxn 500005
long long ans;

void mergesort(int *a, int l, int *b, int r) {
	if (l == r)
		return;
	int mid = (l + r) / 2, i = l, j = mid + 1, k = l;
	mergesort(a, l, b, mid), mergesort(a, mid + 1, b, r);
	while (i <= mid && j <= r) //�����������������δ����
		if (a[i] <= a[j]) //����������Ԫ�ر�������Ԫ��С��ô����Ԫ�ط���������b
			b[k++] = a[i++];
		else//����������Ԫ�ر�������Ԫ�ش���ô�ɹ�������ԣ����Ҹ�Ԫ�غ��Ԫ�ؾ��ɹ�������ԣ�д��𰸲���������Ԫ�ط���������b
			b[k++] = a[j++], ans += mid - i + 1;
	while (i <= mid) //����������ʣ��Ԫ��
		b[k++] = a[i++];
	while (j <= r) //����������ʣ��Ԫ��
		b[k++] = a[j++];
	for (int m = l; m <= r; m++) //���������д��ԭ������
		a[m] = b[m];
}

int main(void) {
	int n, num[maxn], temp[maxn];
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &num[i]);
	mergesort(num, 1, temp, n);
	printf("%lld\n", ans);
	return 0;
}
