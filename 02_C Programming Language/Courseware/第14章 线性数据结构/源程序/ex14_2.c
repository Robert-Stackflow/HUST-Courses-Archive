#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "assert.h"
struct c_score_tab{ 
		char *num;		/* 学号 */
		char *name; 		/*姓名 */
		int	c; 			/* C语言课程成绩 */
};
void dynamic_input(char *s1,char **s2);
void dynamic_input(char *s1,char **s2)
{ /*字符指针形参s1指向提示性的实参字符串 */
		char *pc;
		int len;
		pc=(char *)malloc(40*sizeof(char));/* 动态分配40个字节，并由pc指向 */
		assert(pc); /* 判断pc是否为空。为空，退出；否则顺序执行 */
		printf(s1); /* 根据需要输出不同的提示 */
		gets(pc); /* 从键盘接收输入的字符串 */
		len=strlen(pc); /* 计算输入的字符串的长度 */
		(*s2)=(char *)malloc(len*sizeof(char)+1);/*根据输入串长度适当分配存储*/
		assert((*s2));
		strcpy((*s2),pc); /* 将输入串拷贝到动态申请的存储区 */
		free(pc); /* 释放pc指向的动态存储区 */
}
int main(void)
{	int n,i;
		struct c_score_tab *p;
		printf("input the number of students please!\n");
		scanf("%d",&n);
		getchar(); /* getchar用于读结束scanf输入的回车符 */
/* 动态申请n条记录，每条记录的大小为sizeof(struct c_score_tab) */
		p=(struct c_score_tab *)malloc(n*sizeof(struct c_score_tab));
		assert(p);
		for(i=0;i<n;i++){
			dynamic_input("input num!\n",&(p+i)->num);/* 输入学号处理 */
			dynamic_input("input name!\n",&(p+i)->name); /* 输入姓名处理 */
			printf("input score!\n");
			scanf("%d",&(*(p+i)).c); /* 输入C语言课程成绩 */
			getchar();
		}
		printf("\n");
		for(i=0;i<n;i++) /* 打印成绩单 */
			printf("unm=%s\tname=%s\tscore=%d\n",(p+i)->num,(p+i)->name,(p+i)->c);
		printf("\n");
		free(p); /* 释放成绩单占据的存储 */
		return 0;
}
