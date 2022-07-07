#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#define NUM 15
#define N_NODES ('h' - 'a' + 1) 
#define E(a, b, c) add_edge(nodes + (a - 'a'), nodes + (b - 'a'), c)
typedef struct ver_t ver_t, *heap_t;
typedef struct edge_t edge_t;
struct edge_t {	//有向边结构类型
	ver_t *tar;	// 有向边的终点指针 
	edge_t *next;// 指向单向链表的下一条边组成的结点的指针 
	double w;	// 有向边的权值 
};
struct ver_t {	//各个顶点的单向链表构成图的邻接表
	edge_t *edge;//边单向链表的头指针,结点的tar指针指向的顶点为邻接点；
	ver_t *via;	//指向原最短路径上的结点
	double D;	//从单源结点到当前结点的距离
	char name[8];	//边的字符串名
	int heap_index;	//标识顶点在heap中的下标
};
edge_t *e_head = 0, *e_tail = 0;//e_head和e_tail是边数组的头指针和尾指针
void add_edge(ver_t *u, ver_t *v, double d)
{//add_edge增加一条边到e_head指向的动态存储区,e_tail从后向前递减
	if (e_tail == e_head) {//e_tail==e_head,表明尚未动态创建数组，故创建之
		//动态创建edge_t类型的数组,从0到NUM，共NUM+1元素
		e_head = (edge_t *)malloc(sizeof(edge_t) * (NUM + 1));
		e_head[NUM].next = e_tail;//最后一个元素的next域置为空
		e_tail = e_head + NUM;//e_tail指向最后一个元素
	}
	--e_tail;//e_tail递减
	e_tail->tar = v;//tar成员指向有向边的终点
	e_tail->w = d;//权值赋给w成员
	e_tail->next = u->edge;//next域指向起点的edge
	u->edge = e_tail;//起点的edge成员指向动态数组中由e_tail指向的对应元素
}
void free_edges()//释放动态存储区e_head[NUM+1]
{	for (; e_head; e_head = e_tail) {
		e_tail = e_head[NUM].next;
		free(e_head);
	}
} 
heap_t *heap;//heap指向优先级队列动态存储区
int heap_len;//优先级队列长度
void enheap(ver_t *tar, ver_t *via, double d)//入队操作
{	//进队列的顺序a;a的邻接点c,b;c的邻接点f,d;b的邻接点d,...
	int i, j; 
	if (tar->via && d >= tar->D) return;//不形成最短路径，返回 
	tar->D = d;//更新距离
	tar->via = via; //标识该距离的终点
	i = tar->heap_index;//取tar顶点在堆中的下标,0标识未加入队列
	if (!i) i = ++heap_len;//注意：堆不使用位置 0，否则左子树永远为 0
	//下面的代码更新堆,队列中只有根结点时不执行for循环
	for (; i > 1 && tar->D < heap[j = i/2]->D; i = j)//当前距离小
		(heap[i] = heap[j])->heap_index = i; //父结点heap[j]更新子结点heap[i]
	heap[i] = tar;//结点加入优先队列,i=1,更新根结点;i>1,更新父结点或根结点
	tar->heap_index = i;//更新加入顶点在队列中的位置(下标)
}
ver_t * deheap()//出队操作
{
	ver_t *tar, *tmp; int i, j;
	if (!heap_len) return 0;//队列空，返回
	tar = heap[1];//队首出列，heap[1]总是最小距离顶点
	tmp = heap[heap_len--];//取队列的最后那个元素,队列长度减1
	//下面的代码进行队列调整；for循环从根结点开始按照j=i*2向子结点展开
	for (i = 1; i < heap_len && (j = i * 2) <= heap_len; i = j) {
		if (j < heap_len && heap[j]->D > heap[j+1]->D) 
			j++;//heap[j]->D>heap[j+1]->D表示左儿子大于右儿子,取右儿子
		if (heap[j]->D >= tmp->D) 
			break;//tmp->D小，终止循环
		(heap[i] = heap[j])->heap_index = i;//用儿子结点更新父结点
	}
	heap[i] = tmp;//tmp入队
	tmp->heap_index = i;//更新tmp顶点在队列中的位置 
	return tar;
} 
//Dijkstra算法；不可达顶点决不会进入队列
void Dijkstr(ver_t *start)
{	ver_t *lead; edge_t *e;
	enheap(start, start, 0);//将源点a加入队列，等价于将源点加入集合U
	while ((lead = deheap()))//删除a,顶点a的邻接点c,b进队列；
		for (e = lead->edge; e; e = e->next)//广度搜索
			enheap(e->tar, lead, lead->D + e->w);//将每个邻接点入队
} 
void show_path(ver_t *tar)//显示输出从源点a到达某个顶点tar的最短路径
{	if (tar->via == tar)
		printf("%s", tar->name);
	else if (!tar->via)//tar->via=NULL,表示不可达
		printf("%s(unreached)", tar->name);
	else {
		show_path(tar->via);//递归调用
		printf("-> %s(%g) ", tar->name, tar->D);//显示输出顶点名,距离
	}
} 
int main(void)
{	int i;
	ver_t *nodes = (ver_t *)calloc(sizeof(ver_t), N_NODES);//创建顶点数组
	for (i = 0; i < N_NODES; i++)//对('h' - 'a' + 1)9个结点的name赋值
		sprintf(nodes[i].name, "%c", 'a' + i);
	//通过宏调用，调用add_edge函数，生成各个有向边及权值
	E('a', 'b', 10); E('a', 'c', 12); E('b', 'c', 1);  E('b', 'd', 11);
	E('c', 'd', 12); E('c', 'f', 12); E('d', 'b', 2);  E('d', 'e', 6);  
	E('d', 'h', 9);	 E('e', 'f', 9);  E('e', 'h', 2);  E('f', 'a', 15);
	E('f', 'c', 1);  E('f', 'e', 6);  E('f', 'g', 2);  E('g', 'a', 8);  
	E('g', 'e', 6);  E('h', 'd', 3);
	heap = (heap_t *)calloc(sizeof(heap_t), N_NODES + 1);//创建堆队列存储
	heap_len = 0;//初始化堆队列长度为0
	Dijkstr(nodes);//执行Dijkstr算法，求单源结点a到各顶点的最短路径
	for (i = 0; i < N_NODES; i++) {//从源点开始，依次访问每个顶点
		show_path(nodes + i);//输出单源结点a到顶点i的最短路径
		putchar('\n');
	} 
	free_edges();//释放边的动态存储区
	free(heap);//释放堆队列的动态存储区
	free(nodes);//释放顶点的动态存储区
	return 0;
}
