#include "stdio.h"
#include "stdio.h"
char *strstr(char *s,char *t)/*s为源串,t为字串*/
{	char *ps=s,*pt,*pc;/*ps指向源串*/
	while(*ps!='\0'){/*ps依次指向源串中每一个字符*/
		for(pt=t,pc=ps;*pt!='\0'&& *pt==*pc;pt++,pc++)/*pc指向源串,pt指向字串;*/ 
			;/*若源串字符与字串字符匹配且没到字串尾,pt++,pc++，继续*/
		  if(*pt=='\0') return ps;/*到字串尾，说明匹配成功，返回字串出现位置*/
		  ps++;/*ps指向源串中的下一个字符*/
	}
	return 0;
}
int main(void)
{	char s1[]="abcdefghijk",s2[]="fgh",*p;/*定义源串,字串,临时指针p*/
	p=strstr(s1,s2);/*在"abcdefghijk"中查找"fgh",字串出现位置赋给p*/
	printf("%p\t%s\n",&s1[0],s1);/*输出源串起始地址和源串*/
	printf("%p\t%s\n",p,p);/*输出字串出现位置以及从该位置起的源串*/
	return 0;
}

