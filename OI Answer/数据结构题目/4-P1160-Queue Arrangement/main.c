#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
	struct Node *next, *prior;
	int num;
} Node;
Node queue[100005];
int sign[100005];//标识是否在队列中
int main(void) {
	int n, top = 0, m;
	scanf("%d", &n);
	for (int i = 1; i < 100005; i++)
		queue[i].num = i;//捆绑queue下标和学生编号，便于随机访问
	Node *head = &queue[1];//队首为1号同学
	sign[1] = 1;
	queue[1].prior = queue[1].next = &queue[1];//此时仅有一人，队首的前后指针均指向自己
	for (int i = 2; i <= n; i++) {
		int k, flag;
		scanf("%d%d", &k, &flag);//读入学生编号和插入方式
		sign[i] = 1;
		Node *mid = &queue[k];//取出被插队学生的指针
		Node *p = &queue[i];//取出待插队学生的指针
		if (flag) {//如果是插在学生右边
			p->prior = mid;//待插队学生的prior为被插队学生
			p->next = mid->next;//待插队学生的next为被插队学生的next
			mid->next = p;//更新被插队学生的next
			p->next->prior = p;//更新其余指针关系
		} else {//如果是插在学生左边
			p->next = mid;
			p->prior = mid->prior;
			mid = mid->prior;
			mid->next = p;
			p->next->prior = p;
			if (k == head->num)
				head = p;//如果被插队学生即为队首，那么更新head
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