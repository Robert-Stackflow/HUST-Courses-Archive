#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
int maxn = 1000019, INITIAL = 1e9;
int na;
int ch[maxn][2];//[i][0]代表i左儿子，[i][1]代表i右儿子
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
void pushup(int id) { //和线段树的pushup更新一样
	size[id] = size[ch[id][0]] + size[ch[id][1]] + cnt[id];//本节点子树大小 = 左儿子子树大小 + 右儿子子树大小 + 本节点副本数
}
void build() {
	root = CreateNode(-INITIAL), ch[root][1] = CreateNode(INITIAL);
	size[root] = size[ch[root][0]] + size[ch[root][1]] + cnt[root];
}
void Rotate(int &id, int d) { //id是引用传递，d(irection)为旋转方向，0为左旋，1为右旋
	int temp = ch[id][d ^ 1];//旋转理解：找个动图看一看就好(或参见其他OIer的blog)
	ch[id][d ^ 1] = ch[temp][d];//这里讲一个记忆技巧，这些数据都是被记录后马上修改
	ch[temp][d] = id;//所以像“Z”一样
	id = temp;//比如这个id，在上一行才被记录过，ch[temp][d]、ch[id][d ^ 1]也是一样的
	size[ch[id][d]] = size[ch[ch[id][d]][0]] + size[ch[ch[id][d]][1]] + cnt[ch[id][d]];
	pushup(ch[id][d]), pushup(id); //旋转以后size会改变，看图就会发现只更新自己和转上来的点，pushup一下,注意先子节点再父节点
}//旋转实质是({在满足BST的性质的基础上比较优先级}通过交换本节点和其某个叶子节点)把链叉开成二叉形状(从而控制深度)，可以看图理解一下
void InsertNode(int &id, int v) { //id依然是引用，在新建节点时可以体现
	if (!id) {
		id = CreateNode(v);//若节点为空，则新建一个节点
		return ;
	}
	if (v == val[id])cnt[id]++; //若节点已存在，则副本数++;
	else { //要满足BST性质，小于插到左边，大于插到右边
		int d = v < val[id] ? 0 : 1;//这个d是方向的意思，按照BST的性质，小于本节点则向左，大于向右
		InsertNode(ch[id][d], v); //递归实现
		if (dat[id] < dat[ch[id][d]])Rotate(id, d ^ 1); //(参考一下图)与左节点交换右旋，与右节点交换左旋
	}
	pushup(id);//现在更新一下本节点的信息
}
void DeleteNode(int &id, int v) { //最难de部分了
	if (!id)return ; //到这了发现查不到这个节点，该点不存在，直接返回
	if (v == val[id]) { //检索到了这个值
		if (cnt[id] > 1) {
			cnt[id]--, pushup(id);    //若副本不止一个，减去一个就好
			return ;
		}
		if (ch[id][0] || ch[id][1]) { //发现只有一个值，且有儿子节点,我们只能把值旋转到底部删除
			if (!ch[id][1]
			        || dat[ch[id][0]] >
			        dat[ch[id][1]]) { //当前点被移走之后，会有一个新的点补上来(左儿子或右儿子)，按照优先级，优先级大的补上来
				Rotate(id, 1), DeleteNode(ch[id][1],
				                      v); //我们会发现，右旋是与左儿子交换，当前点变成右节点；左旋则是与右儿子交换，当前点变为左节点
			} else Rotate(id, 0), DeleteNode(ch[id][0], v);
			pushup(id);
		} else id = 0; //发现本节点是叶子节点，直接删除
		return ;//这个return对应的是检索到值de所有情况
	}
	v < val[id] ? DeleteNode(ch[id][0], v) : DeleteNode(ch[id][1], v); //继续BST性质
	pushup(id);
}
int RankofNode(int id, int v) {
	if (!id)return 0; //若查询值不存在，返回；因为最后要减一排除哨兵节点，想要结果为-1这里就返回0
	if (v == val[id])return size[ch[id][0]] +
		                        1; //查询到该值，由BST性质可知：该点左边值都比该点的值(查询值)小，故rank为左儿子大小 + 1
	else if (v < val[id])returnRankofNode(ch[id][0], v); //发现需查询的点在该点左边，往左边递归查询
	else return size[ch[id][0]] + cnt[id] + RankofNode(ch[id][1],
		            v); //若查询值大于该点值。说明询问点在当前点的右侧，且此点的值都小于查询值，所以要加上cnt[id]
}
int SearchNode(int id, int rank) {
	if (!id)return INITIAL; //一直向右找找不到，说明是正无穷
	if (rank <= size[ch[id][0]])returnSearchNode(ch[id][0], rank); //左边排名已经大于rank了，说明rank对应的值在左儿子那里
	else if (rank <= size[ch[id][0]] + cnt[id])return
		    val[id]; //上一步排除了在左区间的情况，若是rank在左与中(目前节点)中，则直接返回目前节点(中区间)的值
	else returnSearchNode(ch[id][1], rank - size[ch[id][0]] -
		                      cnt[id]); //剩下只能在右区间找了，rank减去左区间大小和中区间，继续递归
}
int PreofNode(int v) {
	int id = root, pre; //递归不好返回，以循环求解
	while (id) { //查到节点不存在为止
		if (val[id] < v)pre = val[id], id = ch[id][1]; //满足当前节点比目标小，往当前节点的右侧寻找最优值
		else id = ch[id][0];//无论是比目标节点大还是等于目标节点，都不满足前驱条件，应往更小处靠近
	}
	return pre;
}
int NextofNode(int v) {
	int id = root, next;
	while (id) {
		if (val[id] > v)next = val[id], id = ch[id][0]; //同理，满足条件向左寻找更小解(也就是最优解)
		else id = ch[id][1];//与上方同理
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