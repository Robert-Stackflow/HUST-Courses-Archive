#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct queue {
	int team;
	int num;
	int rank;
	struct queue *next;
} Queue;
Queue q[1000005];
Queue *head = NULL, *tail = NULL;

char *str[3] = {"ENQUEUE", "DEQUEUE", "STOP"};

Queue *find(int team, int rank) {
	Queue *p = head;
	while (p) {
		if (p->team == team) {
			if (p->next == NULL || (p->next != NULL && p->next->team != team))
				return p;//如果当前同队伍，而且没有下一个元素或者下一个元素不同队，那么返回p
			while (p->next != NULL && p->next->team == team)
				p = p->next;
			return p;
		}
		p = p->next;
	} //从头开始查找组别为team的成员，如果找到返回其指针，否则返回NULL
	return tail;
}

int main(void) {
	int flag = 1, cnt = 1;
	int i, j;
	scanf("%d", &flag);
	while (flag) {
		for (i = 0; i < 1000005; i++)
			q[i].num = i;
		//初始化队列中与下标对应节点的编号为下标，便于随机访问
		int t;
		t = flag;
		for (i = 1; i <= t; i++) {
			int n;
			scanf("%d", &n);
			int *team = (int *)malloc(sizeof(int) * (n + 5));
			for (j = 1; j <= n; j++)
				scanf("%d", &team[j]), q[team[j]].team = i, q[team[j]].rank = j;
			//读入组员数据，并绑定队列中的成员的组别
		}
		//初始化队列为空队列
		head = NULL;
		char cmd[10];
		int num;
		printf("Scenario #%d\n", cnt++);
		scanf("%s", cmd);
		while (strcmp(cmd, str[2]) != 0) {
			if (strcmp(cmd, str[0]) == 0) {
				scanf("%d", &num);
				if (head == NULL) {
					tail = head = &q[num];
					scanf("%s", cmd);
					continue;
				}
				Queue *pos = find(q[num].team, q[num].rank); //找到和该编号成员同一组的第一个组员
				//如果找到返回该组员的下标，否则返回最后一个成员的下标
				//插入该节点
				q[num].next = pos->next;
				pos->next = &q[num];
				if (pos == tail)
					tail = &q[num];
			} else if (strcmp(cmd, str[1]) == 0) {
				printf("%d\n", head->num) ;
				head = head->next;
			}
			scanf("%s", cmd);
		}
		printf("\n");
		scanf("%d", &flag);
	}
	return 0;
}