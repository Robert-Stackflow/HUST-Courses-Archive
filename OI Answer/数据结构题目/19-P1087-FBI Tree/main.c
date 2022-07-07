#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 10000
int num[MAX];
char s[MAX];

//����ṹ��
typedef struct Node {
	struct Node *lchild, *rchild;
	char c;
} Node;

//�������:�ݹ������������
void PostTraverse(Node *head) {
	if (head->lchild)
		PostTraverse(head->lchild);
	if (head->rchild)
		PostTraverse(head->rchild);
	printf("%c", head->c);
}

//�жϲ�����01���Ƿ�Ϊȫ0��ȫ1����ϴ�
char FBITree(int *num, int begin, int end) {
	int sum = 0;
	for (int i = begin; i <= end; i++) {
		sum += num[i];
	}
	if (sum == 0)
		return 'B';//ȫ0��
	else if (sum == end - begin + 1)
		return 'I';//ȫ1��
	else
		return 'F';//��ϴ�
}

//����������
Node *CreateTree(int *num, int begin, int end) {
	char c = FBITree(num, begin, end);
	Node *p = (Node *)malloc(sizeof(Node));
	p->c = c;
	if (begin < end) { //˵���Ӵ���Ϊ��
		int mid = (begin + end) / 2;
		p->lchild = CreateTree(num, begin, mid);
		p->rchild = CreateTree(num, mid + 1, end);
	} else { //���Ӵ�Ϊ�գ�����������NULL
		p->lchild = NULL;
		p->rchild = NULL;
	}
	return p;
}

int main() {
	int n;
	scanf("%d", &n);
	getchar();
	getchar();
	gets(s);
	int len = pow(2, n);
	for (int i = 0; i < len; i++)
		num[i] = s[i] - '0';
	Node *head = CreateTree(num, 0, len - 1);
	PostTraverse(head);
	return 0;
}