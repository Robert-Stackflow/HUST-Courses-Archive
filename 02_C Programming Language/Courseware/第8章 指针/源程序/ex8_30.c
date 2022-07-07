#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#define MAXLINES 500/*最多行数*/
#define MAXLEN 100/*行最多字符数*/
char * lineptr[MAXLINES];/*定义字符指针数组lineptr*/
int readlines(char *[],int);/*读多行函数的原型声明*/
void writelines(char *[],int);/*写一行函数的原型声明*/
void sort(void *[],int,int (*)(void *,void *));/*排序函数的原型声明*/
int numcmp(void *s1,void *s2);/*数字字符串比较函数的原型声明*/
int getline(char *,int);/*读一行函数的原型声明*/
void swap(void *v[],int i,int j);/*交换指针数组元素的函数原型声明*/
int main(int argc, char* argv[])/*带命令行参数的main函数*/
{	int nlines,numeric = 0;
	if(argc > 1 && strcmp(argv[1],"-n")==0)/*有多个参数，且第2个参数是-n*/
		numeric=1;/*置数值比较标志*/
	if((nlines=readlines(lineptr,MAXLINES))>=0){/*读多行,行数赋给nlines,若行数>=0*/
/*调用排序函数，lineptr的类型强制转换为(void **)，numeric非0调用数值比较函数numcmp，
否则调用字符串比较函数strcmp，条件表达式结果的类型要强制转换为(int (*)(void *,void *)) */
	sort((void **)lineptr,nlines,(int (*)(void *,void *)) (numeric ? numcmp:strcmp));
	writelines(lineptr,nlines);/*输出排序后指针数组lineptr指向的nlines行字符串*/
	return 0;
	}
	else {/*若nlines==-1，表明输入行过多*/
		printf("input too big to sort\n");/*输出行数太多，无法排序*/
		return 1;
	}
}
void sort(void *v[],int n,int (*comp)(void *,void *))/*对v中元素按照comp规则排序*/
{	int i,j;/*上面的形参comp是函数指针，所指函数有两个无值型指针形参，返回整型*/
	for(i=0;i<n-1;i++){/*采用冒泡法排序*/
		for(j=0;j<n-i-1;j++)
			if((*comp)(v[j],v[j+1])>0)/*对v中相邻两个指针元素按照comp的规则进行比较*/
				swap(v,j,j+1);/*交换v中相邻两个指针元素的值*/
	}
}
void swap(void *v[],int i,int j)
{	void *t;
	t=v[i],v[i]=v[j],v[j]=t;/*交换v中v[i]和v[j]两个指针元素的值*/
}
int numcmp(void *s1,void *s2)/*对数字字符串进行数值比较的函数*/
{	double v1,v2;
	v1 = atof((const char *)s1);/*调用atof函数将数字串转换为double类型数，*/
	v2 = atof((const char *)s2);/*然后分别赋给v1和v2*/
	return (v1<v2?-1: v1>v2?1:0);/*将v1和v2进行比较，v1小返回-1，大返回1，相等返回0*/
}
int readlines(char *lineptr[],int maxlines)/*读不超过maxlines行字符串的函数*/
{	int len,nlines=0;
	char *p,line[MAXLEN];
	while((len = getline(line,MAXLEN))>0)/*读一行，行长度赋给len*/
		if(nlines>=maxlines || (p=(char *)malloc(len))==NULL)
			return (-1);/*超过最多行或动态存储分配失败，返回-1*/
		else{/*未超过最多行且动态存储分配len个字节成功*/
			line[len-1]='\0';/*尾部加'\0'形成字符串*/
			strcpy(p,line);/*将line字符数组中的字符拷贝到已经分配的动态存储区*/
			lineptr[nlines++] = p;/*将指向动态存储区的指针值赋给指针数组元素*/
		}
	return (nlines);/*返回已经读入的行数*/
}
void writelines(char *lineptr[],int nlines)/*输出指针数组指向的多行字符串函数*/
{	while(nlines-- >0)	/*先判断行数是否大于0，然后行数减1*/
		printf("%s\n",*lineptr++);/*输出*lineptr指向的字符串，然后lineptr减1指向下个串*/
}
int getline(char *s,int lim)/*读不超过lim个字符的一行函数*/
{	int c,i=0;/*下面语句执行lim减1后仍大于0且读入的单个字符非EOF，且非换行符*/
	while(--lim>0 && (c=getchar())!=EOF && c != '\n')
		s[i++]=c;/*将读入字符存放到s数组，然后下标加1指向下个空闲位置*/
	if(c=='\n')/*若读入字符是换行符*/
		s[i++]='\0';/*尾部加'\0'形成字符串*/
	return (i);/*返回字符串的长度*/
}