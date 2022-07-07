#include "stdio.h"
#include "stdlib.h"
#include "string.h"
typedef struct score_tab{
	int num;
	char name[20];
	float score[4];
} score_tab;
void empty_tab(int n); /* 创建空成绩单 */
void fill_one_course(int num,float scr,int index);/* 填单科成绩 */
void fill_one_person(score_tab a); /* 填个人完整信息 */
void read_person(int num); /* 读个人各科成绩 */
void print_preson(score_tab a); /* 显示个人各科成绩 */
void print_table(void); /* 显示班级成绩单 */
#define N 6
int main(void)
{	int n;
	score_tab a;
	n=N;
	empty_tab(n);
	a.num=2;strcpy(a.name,"Zhang Jiangou");
	a.score[0]=78;a.score[1]=88;a.score[2]=75;a.score[3]=81;
	fill_one_person(a);
	print_preson(a);
	a.num=0;strcpy(a.name,"Wang Jiangwei");
	fill_one_person(a);
	a.num=4;a.score[0]=67;
	fill_one_course(a.num,a.score[0],0);
	a.num=2;a.score[0]=87;
	fill_one_course(a.num,a.score[0],0);
	print_table();
	return 0;
}
void empty_tab(int n)
{	FILE *out;
	int i;
	score_tab a = {0,"NNNNNNNNNNNN",{-1,-1,-1,-1}};
	if((out = fopen("c:\\score.dat","wb")) == NULL)
		exit(-1);
	for(i=0; i < n; i++){
		a.num = i;
		fwrite(&a,sizeof(score_tab),1,out);
	}
	fclose(out);
}
void fill_one_course(int num,float scr,int index)
{	FILE *fp;
	fpos_t pos,*ptr=&pos;/* 声明fpos_t类型的对象pos和指向pos的指针ptr */
	score_tab a;
	if((fp = fopen("c:\\score.dat","rb+")) == NULL)/* 打开成绩单文件 */
		exit(-1);
	fseek(fp,num*sizeof(score_tab),SEEK_SET); /* 根据学号定位 */
	fgetpos(fp,ptr);/* 保存定位后文件指针的当前值 */
	fread(&a,sizeof(score_tab),1,fp); /* 读一条成绩单记录 */
	a.score[index] = scr; /* 填写成绩 */
	fsetpos(fp,ptr); /* 恢复文件指针的原有指向 */
	fwrite(&a,sizeof(score_tab),1,fp);/* 回写填写成绩记录 */
	fclose(fp); /* 关闭文件，强制存盘 */
}
void fill_one_person(score_tab a)
{	FILE *fp;
	int num;
	if((fp = fopen("c:\\score.dat","rb+")) == NULL) /* 打开成绩单文件 */
		exit(-1);
	num = a.num; /* 获取学号 */
	fseek(fp,num*sizeof(score_tab),SEEK_SET); /* 根据学号定位 */
	fwrite(&a,sizeof(score_tab),1,fp); /* 将a 中记录写入到指定位置 */
	fclose(fp); /* 关闭文件，强制存盘 */
}
void read_person(int num)
{	FILE *fp;
	score_tab a;
	if((fp = fopen("c:\\score.dat","rb+")) == NULL) /* 打开成绩单文件 */
		exit(-1);
	fseek(fp,num*sizeof(score_tab),SEEK_SET); /* 根据学号定位 */
	fread(&a,sizeof(score_tab),1,fp); /* 读指定记录 */
	print_preson(a); /* 显示该记录 */
	fclose(fp); /* 关闭文件 */
}
//print_preson函数先输出成绩单表头，然后显示学生a的各项数据。
void print_preson(score_tab a)
{	printf(" num\t    name\t\t Math\t Phys\t Engl\t   C\n");
	printf(" %04d\t %-16s\t%6.2f\t%6.2f\t%6.2f\t %6.2f\n",a.num,a.name, \
				a.score[0],a.score[1],a.score[2],a.score[3]);
}
//print_table函数显示输出整张班级成绩单。
void print_table(void)
{	FILE *fp;
	score_tab a;
	if((fp = fopen("c:\\score.dat","rb+")) == NULL)
		exit(-1);
	printf(" num\t    name\t\t Math\t Phys\t Engl\t   C\n");
	while(!feof(fp)){
		fread(&a,sizeof(score_tab),1,fp);
		if(!feof(fp))
			printf(" %04d\t %-16s\t%6.2f\t%6.2f\t%6.2f\t%6.2f\n",a.num, \
			a.name,a.score[0],a.score[1],a.score[2],a.score[3]);
	}
	fclose(fp);
}
