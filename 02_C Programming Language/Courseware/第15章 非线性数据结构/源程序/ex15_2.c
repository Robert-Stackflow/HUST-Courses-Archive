#include "stdio.h"
#include "ctype.h"
#include "stdlib.h"
#include "string.h"
#define MAXWORD 20
#define BUFSIZE 1000
static int bufp=0;            /* ��̬ȫ�ֱ�����buf ��������"ָ��" */
static char buf[BUFSIZE];     /* �ı������� */
typedef struct tree_node{ 
		char *p_word;                	/* ָ���Ѵ洢��ʶ����ָ�� */
		int count;                  	 	/* ��ʶ�����ִ���  */
		struct tree_node *left,*right; 	/* ��ָ�����ָ�� */
} tree_node;                 /* ��������������������Ϊtree_node */
//����ԭ�͵�����
tree_node * add_node(tree_node *p_node,char *w);
void print_tree(tree_node * p_node);
int get_word(char *pc,int n);
char *strdup(const char *pc);
int getch(void);
void ungetch(int ch);
int main(void)
{	tree_node * root;
		char word[MAXWORD]; root=NULL;
		while(get_word(word,MAXWORD)!=EOF)
			if(isalpha(word[0]) || (word[0]=='_' ))
				root=add_node(root,word);
		print_tree(root);
		putchar('\n');
	    return 0;
}
tree_node * add_node(tree_node *p_node,char *w)
{	int n;
		if(p_node==NULL){
			p_node=(tree_node *)malloc(sizeof(tree_node));
			p_node->p_word=strdup(w); p_node->count=1;
			p_node->left=p_node->right=NULL;
		} else if((n=strcmp(w,p_node->p_word))==0)
			p_node->count++;
		else if(n<0)
			p_node->left=add_node(p_node->left,w);
		else
			p_node->right=add_node(p_node->right,w);
		return (p_node);
}
void print_tree(tree_node * p_node)
{	if(p_node!=NULL){
			print_tree(p_node->left);
			printf("\t%p\t%p\t%4d\t%s\t%p\n",p_node,p_node->left, \
p_node->count,p_node->p_word,p_node->right);
			print_tree(p_node->right);
		}
}
int get_word(char *pc,int n)
{	int c; char *w=pc;
		while(isspace(c=getch())) ;
		if(c!=EOF) *w++=c;
		if(!isalpha(c) && !(c=='_')){
			*w='\0'; return (c);
		}
		for(;--n>0;w++)
			if(!isalnum(*w=getch())){
				ungetch(*w); break;
			}
		*w='\0';
		return (pc[0]);
}
char *strdup(const char *pc)
{	char *p;
		p=(char *)malloc(strlen(pc)+1);
		if(p!=NULL) strcpy(p,pc);
		return (p);
}

int getch(void) /* ���������ַ��ʹӻ������ж�������͵���getchar��*/
{ return ((bufp>0)?buf[--bufp]:getchar()); }

void ungetch(int ch)
{	if(bufp>BUFSIZE)
			printf("ungetch:too many characters\n");
		else
			buf[bufp++]=ch;
}
