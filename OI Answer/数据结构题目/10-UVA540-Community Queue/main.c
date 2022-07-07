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
				return p;//�����ǰͬ���飬����û����һ��Ԫ�ػ�����һ��Ԫ�ز�ͬ�ӣ���ô����p
			while (p->next != NULL && p->next->team == team)
				p = p->next;
			return p;
		}
		p = p->next;
	} //��ͷ��ʼ�������Ϊteam�ĳ�Ա������ҵ�������ָ�룬���򷵻�NULL
	return tail;
}

int main(void) {
	int flag = 1, cnt = 1;
	int i, j;
	scanf("%d", &flag);
	while (flag) {
		for (i = 0; i < 1000005; i++)
			q[i].num = i;
		//��ʼ�����������±��Ӧ�ڵ�ı��Ϊ�±꣬�����������
		int t;
		t = flag;
		for (i = 1; i <= t; i++) {
			int n;
			scanf("%d", &n);
			int *team = (int *)malloc(sizeof(int) * (n + 5));
			for (j = 1; j <= n; j++)
				scanf("%d", &team[j]), q[team[j]].team = i, q[team[j]].rank = j;
			//������Ա���ݣ����󶨶����еĳ�Ա�����
		}
		//��ʼ������Ϊ�ն���
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
				Queue *pos = find(q[num].team, q[num].rank); //�ҵ��͸ñ�ų�Աͬһ��ĵ�һ����Ա
				//����ҵ����ظ���Ա���±꣬���򷵻����һ����Ա���±�
				//����ýڵ�
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