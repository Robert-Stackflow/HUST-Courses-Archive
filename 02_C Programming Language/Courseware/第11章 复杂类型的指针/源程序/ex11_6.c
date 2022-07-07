#include "stdio.h"
char *(*(*p)(void))(char *,char *);/*f1是一个指针函数，返回的指针指向有两个*/
char *(*f1(void))(char *,char *);/*字符指针形参，且返回值为字符指针值的函数*/
char *strcpy(char *,char *);/*有两个字符指针形参，且返回值为字符指针值的函数*/
int main(void)
{
	char a[80],b[]="aaa,bbb,ccc",*str;
	p=f1;/*p指向f1*/
	str=(*p)()(a,b);/*先计算(*p)()，即f1函数，返回strcpy；然后调用strcpy(a,b)*/
	printf("%s\n",str);
	return 0;
}
char *(*f1(void))(char *,char *)
{/*f1(void)表示f1是无参函数，其余部分都是描述它的返回值的类型*/
	return strcpy;/*f1返回指向有两个字符指针形参，且返回值为字符指针值的函数*/
}
char *strcpy(char *t,char *s)
{
	char *p=t;
	while((*t++=*s++)!='\0') ;
	return p;
}
