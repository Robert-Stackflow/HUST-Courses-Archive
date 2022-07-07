#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"
/*#define HASHSIZE 101*//*实际哈希表长度取101更合适*/
#define HASHSIZE 11	/*哈希表长度，故意缩短，以形成链表*/
#define MAXWORD 100
#define BUFSIZE 10000 
typedef struct nlist {			/* 链表结点数据结构*/ 
			char *name;     		/* 宏名指针 */ 
       		char *defn;     		/* 替换文本指针 */
			struct nlist *next;	/* 自引用指针 */ 
		}Hash_tab; 
char buf[BUFSIZE];    /* 可以回退字符的缓冲区 */ 
int bufp = 0;         /* 缓冲区数组的下标 */ 
int getch(void); 
void ungetch(int); 
int getword(char *, int); 
static Hash_tab *hashtab[HASHSIZE];/*Hash_tab类型的指针数组*/ 
unsigned hash(char *s);	/*哈希函数*/
Hash_tab *lookup(char *);/*哈希表查找函数*/
char * strdup(char *);  
Hash_tab *install(char *name, char *defn);/*创建哈希表函数*/
char*n[]={"HASHSIZE","MAXWORD","BUFSIZE","IN","OUT","PI","HASHSIZE1",
"MAXWORD1","BUFSIZE1","IN1","OUT1","PI1" };/*宏名字符指针数组*/
char *def[]={ "11","100","10000","1","2","3.14","101","80",
"10001","11","21","31.14" };/*替换文本字符指针数组*/
int main(void)
{ 	Hash_tab *p; char word[MAXWORD]; int i;	
	for(i=0;i<12;i++)
		install(n[i], def[i]);	/*创建哈希表*/
	for(i=0;i<HASHSIZE;i++){	/*遍历哈希表*/
		p=hashtab[i];
		if(p)	/*哈希表hashtab[i]非空，输出哈希值及链表头指针值*/
			printf("hashvalue=%u hashtab[%u]=%p\n",i,i,p);
		while(p){/*哈希值为多值时，遍历该哈希值对应的链表*/
			printf("hashvalue=%u p=%p\tname=%-10s\tdefn=%-10s\t \
p->next=%p\n",i,p,p->name,p->defn,p->next);
			p=p->next;
		}
	}
	while (getword(word, MAXWORD) != EOF) /*根据宏名查找哈希表，找出替换文本*/
		if (p=lookup(word)) 
			printf("p=%p,name=%s,defn=%s\n",p,p->name,p->defn);
		else
			printf("%s is not in lookup table!\n",word);
	return 0;
}
/* 哈希函数:  根据字符串计算哈希值 */ 
unsigned hash(char *s) 
{ 	unsigned hashval; 
	for (hashval = 0; *s != '\0'; s++) /*按照31乘以先前累加和再加*/
		hashval = *s + 31 * hashval; /*当前字符的ASCII码值求得累加和*/
	return hashval % HASHSIZE; /*取累加和与哈希表长度的余数作为哈希函数值*/
} 
/* 查找函数:  根据宏名查找哈希表，找出替换文本*/ 
Hash_tab *lookup(char *s) /*先通过hash(s)计算哈希值，再以*/
{ 	Hash_tab *np;  /*此为下标访问哈希表指针数组元素，元素值是链表的头指针*/
	for (np = hashtab[hash(s)];  np != NULL; np = np->next) /* 循环遍历链表 */ 
		if (strcmp(s, np->name) == 0) return np; /* 找到，返回该结点地址*/ 
	return NULL; /* 没找到返回空值*/ 
}   
/* 创建哈希表函数:  将宏名和替换文本放进哈希表 */ 
Hash_tab *install(char *name, char *defn) 
{ 	Hash_tab *np; 
	unsigned hashval; 
	if ((np = lookup(name)) == NULL) { /*如果没有查到，即宏名不在哈希表中*/ 
		np = (Hash_tab *) malloc(sizeof(Hash_tab));/* 创建新哈希结点*/
		if (np == NULL || (np->name = strdup(name)) == NULL) 
			return NULL;/*np->name指向宏名字符串；如果为空则返回空值*/
		hashval = hash(name);/*调用哈希函数，计算哈希值*/
		np->next = hashtab[hashval]; /*置新哈希结点的next域为空值*/
		hashtab[hashval] = np; /*以哈希值为下标，将该单元指针指向新哈希结点*/
    } 
	else   /*如果查到，即宏名在哈希表中*/ 
		free((void *) np->defn);   /*释放宏名对应的文本 */ 
	if ((np->defn = strdup(defn)) == NULL) /*更新宏名对应的文本 */ 
		return NULL; /*如果宏名对应的文本为空，返回空值*/ 
	return np; 
}
/* 读一个单词函数getword: 从输入中读一个单词或字符*/ 
int getword(char *word, int lim) 
{ 	int c, getch(void); void ungetch(int); char *w = word; 
	while (isspace(c = getch())) ;/*读字符且去掉前导空格字符*/
	if (c != EOF)  *w++ = c; /*复制字符*/
	if (!isalpha(c)) { 
		*w = '\0'; /*遇到非字母，字符复制结束，添加字符串的终结符*/
		return c; 
	} 
	for ( ; --lim > 0; w++)/*复制字母或数字字符到word数组*/ 
		if (!isalnum(*w = getch())){ /*遇到非字母或数字字符，回退该字符*/  
			ungetch(*w); break; /*退出for循环*/
		} 
	*w = '\0'; 
	return word[0]; 
}
char *strdup(const char *pc)
{	char *p;
		p=(char *)malloc(strlen(pc)+1);
		if(p!=NULL) strcpy(p,pc);
		return (p);
}
int getch(void) /* 缓冲区有字符就从缓冲区中读，否则就调用getchar读*/
{ return ((bufp>0)?buf[--bufp]:getchar()); }
void ungetch(int ch)
{	if(bufp>BUFSIZE)
			printf("ungetch:too many characters\n");
		else
			buf[bufp++]=ch;
}
