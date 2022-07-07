#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//Treap平衡二叉搜索树
typedef int ElemType;

typedef struct TreapNode {
	int value;
	int heap;
	int weight;
	int size;
	int lsize;
	int rsize;
	struct TreapNode *lchild;
	struct TreapNode *rchild;
} TreapNode, *Treap;
void LeftRotate(TreapNode *node);
void RightRotate(TreapNode *node);
void InsertNode(Treap *root, int value);
void RemoveNode(Treap *root, int value);
int RankofNode(Treap root, int value);
Treap SearchNode(Treap root, int rank);
Treap PreofNode(Treap root, int value, TreapNode *optimal);
Treap NextofNode(Treap root, int value, TreapNode *optimal);
void Display(Treap root);

int main(void) {
	int n, op, value;
	scanf("%d", &n);
	Treap treap = NULL;
	for (int i = 1; i <= n; i++) {
		scanf("%d%d", &op, &value);
		switch (op) {
			case (1):
				InsertNode(&treap, value);
				Display(treap);
				break;
			case (2):
				RemoveNode(&treap, value);
				Display(treap);
				break;
			case (3):
				printf("%d", RankofNode(treap, value));
				break;
			case (4):
				printf("%d", SearchNode(treap, value));
				break;
			case (5):
				printf("%d", PreofNode(treap, value, 0)->value);
				break;
			case (6):
				printf("%d", NextofNode(treap, value, 0)->value);
				break;
		}
	}
	return 0;
}

void LeftRotate(TreapNode *node) {
	TreapNode *temp = node->rchild;
	node->rchild = temp->lchild;
	temp->lchild = node;
	node = temp;
}

void RightRotate(TreapNode *node) {
	TreapNode *temp = node->lchild;
	node->lchild = temp->rchild;
	temp->rchild = node;
	node = temp;
}

void InsertNode(Treap *root, int value) {
	if (!(*root)) {
		(*root) = (Treap)malloc(sizeof(TreapNode));
		(*root)->value = value;
		srand((unsigned)time(NULL));
		(*root)->heap = rand(); //生成随机的heap值
	} else if (value <= (*root)->value) {
		InsertNode(&((*root)->lchild), value);
		if ((*root)->lchild->heap < (*root)->heap)
			RightRotate((*root)); //左子节点修正值小于当前节点修正值，右旋当前节点
	} else {
		InsertNode(&((*root)->rchild), value);
		if ((*root)->rchild->heap < (*root)->heap)
			LeftRotate((*root)); //右子节点修正值小于当前节点修正值，左旋当前节点
	}
}

void RemoveNode(Treap *root, int value) {
	if (value == (*root)->value) {
		if (!(*root)->rchild || !(*root)->lchild) {
			TreapNode *temp = (*root);
			if (!(*root)->rchild)
				(*root) = (*root)->lchild;
			if (!(*root)->lchild)
				(*root) = (*root)->rchild;
			free(temp);
		} else {
			if ((*root)->lchild->heap < (*root)->rchild->heap) {
				RightRotate((*root));
				RemoveNode(&((*root)->rchild), value);
			} else {
				LeftRotate((*root));
				RemoveNode(&((*root)->lchild), value);
			}
		}
	} else if (value < (*root)->value)
		RemoveNode(&((*root)->lchild), value);
	else
		RemoveNode(&((*root)->rchild), value);
}

int RankofNode(Treap root, int value) {

}

Treap SearchNode(Treap root, int rank) {
//	if(rank<root)
}

Treap PreofNode(Treap root, int value, TreapNode *optimal) {
	if (!root)
		return optimal;
	if (root->value <= value)
		return PreofNode(root->rchild, value, root);
	else
		return PreofNode(root->lchild, value, optimal);
}

Treap NextofNode(Treap root, int value, TreapNode *optimal) {
	if (!root)
		return optimal;
	if (root->value >= value)
		return NextofNode(root->lchild, value, root);
	else
		return NextofNode(root->rchild, value, optimal);
}

void Display(Treap root) {
	if (!root)
		return;
	else {
		Display(root->lchild);
		printf("%d ", root->value);
		Display(root->rchild);
	}
}