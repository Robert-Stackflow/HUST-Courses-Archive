#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#define NUM 15
#define N_NODES ('h' - 'a' + 1) 
#define E(a, b, c) add_edge(nodes + (a - 'a'), nodes + (b - 'a'), c)
typedef struct ver_t ver_t, *heap_t;
typedef struct edge_t edge_t;
struct edge_t {	//����߽ṹ����
	ver_t *tar;	// ����ߵ��յ�ָ�� 
	edge_t *next;// ָ�����������һ������ɵĽ���ָ�� 
	double w;	// ����ߵ�Ȩֵ 
};
struct ver_t {	//��������ĵ���������ͼ���ڽӱ�
	edge_t *edge;//�ߵ��������ͷָ��,����tarָ��ָ��Ķ���Ϊ�ڽӵ㣻
	ver_t *via;	//ָ��ԭ���·���ϵĽ��
	double D;	//�ӵ�Դ��㵽��ǰ���ľ���
	char name[8];	//�ߵ��ַ�����
	int heap_index;	//��ʶ������heap�е��±�
};
edge_t *e_head = 0, *e_tail = 0;//e_head��e_tail�Ǳ������ͷָ���βָ��
void add_edge(ver_t *u, ver_t *v, double d)
{//add_edge����һ���ߵ�e_headָ��Ķ�̬�洢��,e_tail�Ӻ���ǰ�ݼ�
	if (e_tail == e_head) {//e_tail==e_head,������δ��̬�������飬�ʴ���֮
		//��̬����edge_t���͵�����,��0��NUM����NUM+1Ԫ��
		e_head = (edge_t *)malloc(sizeof(edge_t) * (NUM + 1));
		e_head[NUM].next = e_tail;//���һ��Ԫ�ص�next����Ϊ��
		e_tail = e_head + NUM;//e_tailָ�����һ��Ԫ��
	}
	--e_tail;//e_tail�ݼ�
	e_tail->tar = v;//tar��Աָ������ߵ��յ�
	e_tail->w = d;//Ȩֵ����w��Ա
	e_tail->next = u->edge;//next��ָ������edge
	u->edge = e_tail;//����edge��Աָ��̬��������e_tailָ��Ķ�ӦԪ��
}
void free_edges()//�ͷŶ�̬�洢��e_head[NUM+1]
{	for (; e_head; e_head = e_tail) {
		e_tail = e_head[NUM].next;
		free(e_head);
	}
} 
heap_t *heap;//heapָ�����ȼ����ж�̬�洢��
int heap_len;//���ȼ����г���
void enheap(ver_t *tar, ver_t *via, double d)//��Ӳ���
{	//�����е�˳��a;a���ڽӵ�c,b;c���ڽӵ�f,d;b���ڽӵ�d,...
	int i, j; 
	if (tar->via && d >= tar->D) return;//���γ����·�������� 
	tar->D = d;//���¾���
	tar->via = via; //��ʶ�þ�����յ�
	i = tar->heap_index;//ȡtar�����ڶ��е��±�,0��ʶδ�������
	if (!i) i = ++heap_len;//ע�⣺�Ѳ�ʹ��λ�� 0��������������ԶΪ 0
	//����Ĵ�����¶�,������ֻ�и����ʱ��ִ��forѭ��
	for (; i > 1 && tar->D < heap[j = i/2]->D; i = j)//��ǰ����С
		(heap[i] = heap[j])->heap_index = i; //�����heap[j]�����ӽ��heap[i]
	heap[i] = tar;//���������ȶ���,i=1,���¸����;i>1,���¸���������
	tar->heap_index = i;//���¼��붥���ڶ����е�λ��(�±�)
}
ver_t * deheap()//���Ӳ���
{
	ver_t *tar, *tmp; int i, j;
	if (!heap_len) return 0;//���пգ�����
	tar = heap[1];//���׳��У�heap[1]������С���붥��
	tmp = heap[heap_len--];//ȡ���е�����Ǹ�Ԫ��,���г��ȼ�1
	//����Ĵ�����ж��е�����forѭ���Ӹ���㿪ʼ����j=i*2���ӽ��չ��
	for (i = 1; i < heap_len && (j = i * 2) <= heap_len; i = j) {
		if (j < heap_len && heap[j]->D > heap[j+1]->D) 
			j++;//heap[j]->D>heap[j+1]->D��ʾ����Ӵ����Ҷ���,ȡ�Ҷ���
		if (heap[j]->D >= tmp->D) 
			break;//tmp->DС����ֹѭ��
		(heap[i] = heap[j])->heap_index = i;//�ö��ӽ����¸����
	}
	heap[i] = tmp;//tmp���
	tmp->heap_index = i;//����tmp�����ڶ����е�λ�� 
	return tar;
} 
//Dijkstra�㷨�����ɴﶥ�������������
void Dijkstr(ver_t *start)
{	ver_t *lead; edge_t *e;
	enheap(start, start, 0);//��Դ��a������У��ȼ��ڽ�Դ����뼯��U
	while ((lead = deheap()))//ɾ��a,����a���ڽӵ�c,b�����У�
		for (e = lead->edge; e; e = e->next)//�������
			enheap(e->tar, lead, lead->D + e->w);//��ÿ���ڽӵ����
} 
void show_path(ver_t *tar)//��ʾ�����Դ��a����ĳ������tar�����·��
{	if (tar->via == tar)
		printf("%s", tar->name);
	else if (!tar->via)//tar->via=NULL,��ʾ���ɴ�
		printf("%s(unreached)", tar->name);
	else {
		show_path(tar->via);//�ݹ����
		printf("-> %s(%g) ", tar->name, tar->D);//��ʾ���������,����
	}
} 
int main(void)
{	int i;
	ver_t *nodes = (ver_t *)calloc(sizeof(ver_t), N_NODES);//������������
	for (i = 0; i < N_NODES; i++)//��('h' - 'a' + 1)9������name��ֵ
		sprintf(nodes[i].name, "%c", 'a' + i);
	//ͨ������ã�����add_edge���������ɸ�������߼�Ȩֵ
	E('a', 'b', 10); E('a', 'c', 12); E('b', 'c', 1);  E('b', 'd', 11);
	E('c', 'd', 12); E('c', 'f', 12); E('d', 'b', 2);  E('d', 'e', 6);  
	E('d', 'h', 9);	 E('e', 'f', 9);  E('e', 'h', 2);  E('f', 'a', 15);
	E('f', 'c', 1);  E('f', 'e', 6);  E('f', 'g', 2);  E('g', 'a', 8);  
	E('g', 'e', 6);  E('h', 'd', 3);
	heap = (heap_t *)calloc(sizeof(heap_t), N_NODES + 1);//�����Ѷ��д洢
	heap_len = 0;//��ʼ���Ѷ��г���Ϊ0
	Dijkstr(nodes);//ִ��Dijkstr�㷨����Դ���a������������·��
	for (i = 0; i < N_NODES; i++) {//��Դ�㿪ʼ�����η���ÿ������
		show_path(nodes + i);//�����Դ���a������i�����·��
		putchar('\n');
	} 
	free_edges();//�ͷűߵĶ�̬�洢��
	free(heap);//�ͷŶѶ��еĶ�̬�洢��
	free(nodes);//�ͷŶ���Ķ�̬�洢��
	return 0;
}
