#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
	struct Node *next, *prior;
	int num;
} Node;
Node queue[100005];
int sign[100005];//��ʶ�Ƿ��ڶ�����
int main(void) {
	int n, top = 0, m;
	scanf("%d", &n);
	for (int i = 1; i < 100005; i++)
		queue[i].num = i;//����queue�±��ѧ����ţ������������
	Node *head = &queue[1];//����Ϊ1��ͬѧ
	sign[1] = 1;
	queue[1].prior = queue[1].next = &queue[1];//��ʱ����һ�ˣ����׵�ǰ��ָ���ָ���Լ�
	for (int i = 2; i <= n; i++) {
		int k, flag;
		scanf("%d%d", &k, &flag);//����ѧ����źͲ��뷽ʽ
		sign[i] = 1;
		Node *mid = &queue[k];//ȡ�������ѧ����ָ��
		Node *p = &queue[i];//ȡ�������ѧ����ָ��
		if (flag) {//����ǲ���ѧ���ұ�
			p->prior = mid;//�����ѧ����priorΪ�����ѧ��
			p->next = mid->next;//�����ѧ����nextΪ�����ѧ����next
			mid->next = p;//���±����ѧ����next
			p->next->prior = p;//��������ָ���ϵ
		} else {//����ǲ���ѧ�����
			p->next = mid;
			p->prior = mid->prior;
			mid = mid->prior;
			mid->next = p;
			p->next->prior = p;
			if (k == head->num)
				head = p;//��������ѧ����Ϊ���ף���ô����head
		}
	}
	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		int x;
		scanf("%d", &x);
		if (sign[x]) {
			sign[x] = 0;
			Node *cur = &queue[x];
			if (cur->num == head->num)
				head = cur->next;
			cur = cur->prior;
			cur->next = cur->next->next;
			cur = cur->next;
			cur->prior = cur->prior->prior;
		}
	}
	int temp = head->num;
	do {
		printf("%d ", head->num);
		head = head->next;
	} while (temp != head->num);
	return 0;
}