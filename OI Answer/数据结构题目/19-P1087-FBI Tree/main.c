#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 10000
int num[MAX];
char s[MAX];

//定义结构体
typedef struct Node {
	struct Node *lchild, *rchild;
	char c;
} Node;

//后序遍历:递归遍历左右子树
void PostTraverse(Node *head) {
	if (head->lchild)
		PostTraverse(head->lchild);
	if (head->rchild)
		PostTraverse(head->rchild);
	printf("%c", head->c);
}

//判断并返回01串是否为全0、全1、混合串
char FBITree(int *num, int begin, int end) {
	int sum = 0;
	for (int i = begin; i <= end; i++) {
		sum += num[i];
	}
	if (sum == 0)
		return 'B';//全0串
	else if (sum == end - begin + 1)
		return 'I';//全1串
	else
		return 'F';//混合串
}

//创建二叉树
Node *CreateTree(int *num, int begin, int end) {
	char c = FBITree(num, begin, end);
	Node *p = (Node *)malloc(sizeof(Node));
	p->c = c;
	if (begin < end) { //说明子串不为空
		int mid = (begin + end) / 2;
		p->lchild = CreateTree(num, begin, mid);
		p->rchild = CreateTree(num, mid + 1, end);
	} else { //若子串为空，左右子树赋NULL
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