#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"
/*#define HASHSIZE 101*//*ʵ�ʹ�ϣ����ȡ101������*/
#define HASHSIZE 11	/*��ϣ���ȣ��������̣����γ�����*/
#define MAXWORD 100
#define BUFSIZE 10000 
typedef struct nlist {			/* ���������ݽṹ*/ 
			char *name;     		/* ����ָ�� */ 
       		char *defn;     		/* �滻�ı�ָ�� */
			struct nlist *next;	/* ������ָ�� */ 
		}Hash_tab; 
char buf[BUFSIZE];    /* ���Ի����ַ��Ļ����� */ 
int bufp = 0;         /* ������������±� */ 
int getch(void); 
void ungetch(int); 
int getword(char *, int); 
static Hash_tab *hashtab[HASHSIZE];/*Hash_tab���͵�ָ������*/ 
unsigned hash(char *s);	/*��ϣ����*/
Hash_tab *lookup(char *);/*��ϣ����Һ���*/
char * strdup(char *);  
Hash_tab *install(char *name, char *defn);/*������ϣ����*/
char*n[]={"HASHSIZE","MAXWORD","BUFSIZE","IN","OUT","PI","HASHSIZE1",
"MAXWORD1","BUFSIZE1","IN1","OUT1","PI1" };/*�����ַ�ָ������*/
char *def[]={ "11","100","10000","1","2","3.14","101","80",
"10001","11","21","31.14" };/*�滻�ı��ַ�ָ������*/
int main(void)
{ 	Hash_tab *p; char word[MAXWORD]; int i;	
	for(i=0;i<12;i++)
		install(n[i], def[i]);	/*������ϣ��*/
	for(i=0;i<HASHSIZE;i++){	/*������ϣ��*/
		p=hashtab[i];
		if(p)	/*��ϣ��hashtab[i]�ǿգ������ϣֵ������ͷָ��ֵ*/
			printf("hashvalue=%u hashtab[%u]=%p\n",i,i,p);
		while(p){/*��ϣֵΪ��ֵʱ�������ù�ϣֵ��Ӧ������*/
			printf("hashvalue=%u p=%p\tname=%-10s\tdefn=%-10s\t \
p->next=%p\n",i,p,p->name,p->defn,p->next);
			p=p->next;
		}
	}
	while (getword(word, MAXWORD) != EOF) /*���ݺ������ҹ�ϣ���ҳ��滻�ı�*/
		if (p=lookup(word)) 
			printf("p=%p,name=%s,defn=%s\n",p,p->name,p->defn);
		else
			printf("%s is not in lookup table!\n",word);
	return 0;
}
/* ��ϣ����:  �����ַ��������ϣֵ */ 
unsigned hash(char *s) 
{ 	unsigned hashval; 
	for (hashval = 0; *s != '\0'; s++) /*����31������ǰ�ۼӺ��ټ�*/
		hashval = *s + 31 * hashval; /*��ǰ�ַ���ASCII��ֵ����ۼӺ�*/
	return hashval % HASHSIZE; /*ȡ�ۼӺ����ϣ���ȵ�������Ϊ��ϣ����ֵ*/
} 
/* ���Һ���:  ���ݺ������ҹ�ϣ���ҳ��滻�ı�*/ 
Hash_tab *lookup(char *s) /*��ͨ��hash(s)�����ϣֵ������*/
{ 	Hash_tab *np;  /*��Ϊ�±���ʹ�ϣ��ָ������Ԫ�أ�Ԫ��ֵ�������ͷָ��*/
	for (np = hashtab[hash(s)];  np != NULL; np = np->next) /* ѭ���������� */ 
		if (strcmp(s, np->name) == 0) return np; /* �ҵ������ظý���ַ*/ 
	return NULL; /* û�ҵ����ؿ�ֵ*/ 
}   
/* ������ϣ����:  ���������滻�ı��Ž���ϣ�� */ 
Hash_tab *install(char *name, char *defn) 
{ 	Hash_tab *np; 
	unsigned hashval; 
	if ((np = lookup(name)) == NULL) { /*���û�в鵽�����������ڹ�ϣ����*/ 
		np = (Hash_tab *) malloc(sizeof(Hash_tab));/* �����¹�ϣ���*/
		if (np == NULL || (np->name = strdup(name)) == NULL) 
			return NULL;/*np->nameָ������ַ��������Ϊ���򷵻ؿ�ֵ*/
		hashval = hash(name);/*���ù�ϣ�����������ϣֵ*/
		np->next = hashtab[hashval]; /*���¹�ϣ����next��Ϊ��ֵ*/
		hashtab[hashval] = np; /*�Թ�ϣֵΪ�±꣬���õ�Ԫָ��ָ���¹�ϣ���*/
    } 
	else   /*����鵽���������ڹ�ϣ����*/ 
		free((void *) np->defn);   /*�ͷź�����Ӧ���ı� */ 
	if ((np->defn = strdup(defn)) == NULL) /*���º�����Ӧ���ı� */ 
		return NULL; /*���������Ӧ���ı�Ϊ�գ����ؿ�ֵ*/ 
	return np; 
}
/* ��һ�����ʺ���getword: �������ж�һ�����ʻ��ַ�*/ 
int getword(char *word, int lim) 
{ 	int c, getch(void); void ungetch(int); char *w = word; 
	while (isspace(c = getch())) ;/*���ַ���ȥ��ǰ���ո��ַ�*/
	if (c != EOF)  *w++ = c; /*�����ַ�*/
	if (!isalpha(c)) { 
		*w = '\0'; /*��������ĸ���ַ����ƽ���������ַ������ս��*/
		return c; 
	} 
	for ( ; --lim > 0; w++)/*������ĸ�������ַ���word����*/ 
		if (!isalnum(*w = getch())){ /*��������ĸ�������ַ������˸��ַ�*/  
			ungetch(*w); break; /*�˳�forѭ��*/
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
int getch(void) /* ���������ַ��ʹӻ������ж�������͵���getchar��*/
{ return ((bufp>0)?buf[--bufp]:getchar()); }
void ungetch(int ch)
{	if(bufp>BUFSIZE)
			printf("ungetch:too many characters\n");
		else
			buf[bufp++]=ch;
}
