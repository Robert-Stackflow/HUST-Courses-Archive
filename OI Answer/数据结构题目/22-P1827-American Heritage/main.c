#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char in[30], pre[30];
int cnt, i;

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

//创建二叉树
Node *CreateTree(int l1, int r1, int l2, int r2) {
	if (l1 > r1) {
		return NULL;
	}
	Node *s = (Node *)malloc(sizeof(Node));
	s->lchild = NULL;
	s->rchild = NULL;
	s->c = pre[l1];
	int i;
	for (i = l2; i <= r2; i++) {
		if (pre[l1] == in[i])
			break;
	}
	s->lchild = CreateTree(l1 + 1, l1 + i - l2, l2, i - 1);
	s->rchild = CreateTree(l1 + i - l2 + 1, r1, i + 1, r2);
	return s;
}

int main(void) {
	scanf("%s%s", in, pre);
	Node *head;
	head = CreateTree(0, strlen(in) - 1, 0, strlen(pre) - 1);
	PostTraverse(head);
	return 0;
}