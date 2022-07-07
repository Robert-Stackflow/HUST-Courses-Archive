#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
int maxn = 1000019, INITIAL = 1e9;
int na;
int ch[maxn][2];//[i][0]����i����ӣ�[i][1]����i�Ҷ���
int val[maxn], dat[maxn];
int size[maxn], cnt[maxn];
int tot, root;
int CreateNode(int v) {
	val[++tot] = v;
	dat[tot] = rand();
	size[tot] = 1;
	cnt[tot] = 1;
	return tot;
}
void pushup(int id) { //���߶�����pushup����һ��
	size[id] = size[ch[id][0]] + size[ch[id][1]] + cnt[id];//���ڵ�������С = �����������С + �Ҷ���������С + ���ڵ㸱����
}
void build() {
	root = CreateNode(-INITIAL), ch[root][1] = CreateNode(INITIAL);
	size[root] = size[ch[root][0]] + size[ch[root][1]] + cnt[root];
}
void Rotate(int &id, int d) { //id�����ô��ݣ�d(irection)Ϊ��ת����0Ϊ������1Ϊ����
	int temp = ch[id][d ^ 1];//��ת��⣺�Ҹ���ͼ��һ���ͺ�(��μ�����OIer��blog)
	ch[id][d ^ 1] = ch[temp][d];//���ｲһ�����似�ɣ���Щ���ݶ��Ǳ���¼�������޸�
	ch[temp][d] = id;//������Z��һ��
	id = temp;//�������id������һ�вű���¼����ch[temp][d]��ch[id][d ^ 1]Ҳ��һ����
	size[ch[id][d]] = size[ch[ch[id][d]][0]] + size[ch[ch[id][d]][1]] + cnt[ch[id][d]];
	pushup(ch[id][d]), pushup(id); //��ת�Ժ�size��ı䣬��ͼ�ͻᷢ��ֻ�����Լ���ת�����ĵ㣬pushupһ��,ע�����ӽڵ��ٸ��ڵ�
}//��תʵ����({������BST�����ʵĻ����ϱȽ����ȼ�}ͨ���������ڵ����ĳ��Ҷ�ӽڵ�)�����濪�ɶ�����״(�Ӷ��������)�����Կ�ͼ���һ��
void InsertNode(int &id, int v) { //id��Ȼ�����ã����½��ڵ�ʱ��������
	if (!id) {
		id = CreateNode(v);//���ڵ�Ϊ�գ����½�һ���ڵ�
		return ;
	}
	if (v == val[id])cnt[id]++; //���ڵ��Ѵ��ڣ��򸱱���++;
	else { //Ҫ����BST���ʣ�С�ڲ嵽��ߣ����ڲ嵽�ұ�
		int d = v < val[id] ? 0 : 1;//���d�Ƿ������˼������BST�����ʣ�С�ڱ��ڵ������󣬴�������
		InsertNode(ch[id][d], v); //�ݹ�ʵ��
		if (dat[id] < dat[ch[id][d]])Rotate(id, d ^ 1); //(�ο�һ��ͼ)����ڵ㽻�����������ҽڵ㽻������
	}
	pushup(id);//���ڸ���һ�±��ڵ����Ϣ
}
void DeleteNode(int &id, int v) { //����de������
	if (!id)return ; //�����˷��ֲ鲻������ڵ㣬�õ㲻���ڣ�ֱ�ӷ���
	if (v == val[id]) { //�����������ֵ
		if (cnt[id] > 1) {
			cnt[id]--, pushup(id);    //��������ֹһ������ȥһ���ͺ�
			return ;
		}
		if (ch[id][0] || ch[id][1]) { //����ֻ��һ��ֵ�����ж��ӽڵ�,����ֻ�ܰ�ֵ��ת���ײ�ɾ��
			if (!ch[id][1]
			        || dat[ch[id][0]] >
			        dat[ch[id][1]]) { //��ǰ�㱻����֮�󣬻���һ���µĵ㲹����(����ӻ��Ҷ���)���������ȼ������ȼ���Ĳ�����
				Rotate(id, 1), DeleteNode(ch[id][1],
				                      v); //���ǻᷢ�֣�������������ӽ�������ǰ�����ҽڵ㣻�����������Ҷ��ӽ�������ǰ���Ϊ��ڵ�
			} else Rotate(id, 0), DeleteNode(ch[id][0], v);
			pushup(id);
		} else id = 0; //���ֱ��ڵ���Ҷ�ӽڵ㣬ֱ��ɾ��
		return ;//���return��Ӧ���Ǽ�����ֵde�������
	}
	v < val[id] ? DeleteNode(ch[id][0], v) : DeleteNode(ch[id][1], v); //����BST����
	pushup(id);
}
int RankofNode(int id, int v) {
	if (!id)return 0; //����ѯֵ�����ڣ����أ���Ϊ���Ҫ��һ�ų��ڱ��ڵ㣬��Ҫ���Ϊ-1����ͷ���0
	if (v == val[id])return size[ch[id][0]] +
		                        1; //��ѯ����ֵ����BST���ʿ�֪���õ����ֵ���ȸõ��ֵ(��ѯֵ)С����rankΪ����Ӵ�С + 1
	else if (v < val[id])returnRankofNode(ch[id][0], v); //�������ѯ�ĵ��ڸõ���ߣ�����ߵݹ��ѯ
	else return size[ch[id][0]] + cnt[id] + RankofNode(ch[id][1],
		            v); //����ѯֵ���ڸõ�ֵ��˵��ѯ�ʵ��ڵ�ǰ����Ҳ࣬�Ҵ˵��ֵ��С�ڲ�ѯֵ������Ҫ����cnt[id]
}
int SearchNode(int id, int rank) {
	if (!id)return INITIAL; //һֱ�������Ҳ�����˵����������
	if (rank <= size[ch[id][0]])returnSearchNode(ch[id][0], rank); //��������Ѿ�����rank�ˣ�˵��rank��Ӧ��ֵ�����������
	else if (rank <= size[ch[id][0]] + cnt[id])return
		    val[id]; //��һ���ų���������������������rank��������(Ŀǰ�ڵ�)�У���ֱ�ӷ���Ŀǰ�ڵ�(������)��ֵ
	else returnSearchNode(ch[id][1], rank - size[ch[id][0]] -
		                      cnt[id]); //ʣ��ֻ�������������ˣ�rank��ȥ�������С�������䣬�����ݹ�
}
int PreofNode(int v) {
	int id = root, pre; //�ݹ鲻�÷��أ���ѭ�����
	while (id) { //�鵽�ڵ㲻����Ϊֹ
		if (val[id] < v)pre = val[id], id = ch[id][1]; //���㵱ǰ�ڵ��Ŀ��С������ǰ�ڵ���Ҳ�Ѱ������ֵ
		else id = ch[id][0];//�����Ǳ�Ŀ��ڵ���ǵ���Ŀ��ڵ㣬��������ǰ��������Ӧ����С������
	}
	return pre;
}
int NextofNode(int v) {
	int id = root, next;
	while (id) {
		if (val[id] > v)next = val[id], id = ch[id][0]; //ͬ��������������Ѱ�Ҹ�С��(Ҳ�������Ž�)
		else id = ch[id][1];//���Ϸ�ͬ��
	}
	return next;
}
int main() {
	build();
	int n, op, value;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d%d", &op, &value);
		switch (op) {
			case (1):
				Insert(root, x);
				break;
			case (2):
				DeleteNode(root, x);
				break;
			case (3):
				printf("%d\n", RankofNode(root, x) - 1);
				break;
			case (4):
				printf("%d\n", SearchNode(root, x + 1));
				break;
			case (5):
				printf("%d\n", PreofNode(x));
				break;
			case (6):
				printf("%d\n", NextofNode(x));
				break;
		}
	}
	return 0;
}