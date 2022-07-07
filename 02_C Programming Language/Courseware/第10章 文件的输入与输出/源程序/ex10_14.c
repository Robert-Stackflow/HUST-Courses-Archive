#include "stdio.h"
#include "stdlib.h"
#include "string.h"
typedef struct score_tab{
	int num;
	char name[20];
	float score[4];
} score_tab;
void empty_tab(int n); /* �����ճɼ��� */
void fill_one_course(int num,float scr,int index);/* ��Ƴɼ� */
void fill_one_person(score_tab a); /* �����������Ϣ */
void read_person(int num); /* �����˸��Ƴɼ� */
void print_preson(score_tab a); /* ��ʾ���˸��Ƴɼ� */
void print_table(void); /* ��ʾ�༶�ɼ��� */
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
	fpos_t pos,*ptr=&pos;/* ����fpos_t���͵Ķ���pos��ָ��pos��ָ��ptr */
	score_tab a;
	if((fp = fopen("c:\\score.dat","rb+")) == NULL)/* �򿪳ɼ����ļ� */
		exit(-1);
	fseek(fp,num*sizeof(score_tab),SEEK_SET); /* ����ѧ�Ŷ�λ */
	fgetpos(fp,ptr);/* ���涨λ���ļ�ָ��ĵ�ǰֵ */
	fread(&a,sizeof(score_tab),1,fp); /* ��һ���ɼ�����¼ */
	a.score[index] = scr; /* ��д�ɼ� */
	fsetpos(fp,ptr); /* �ָ��ļ�ָ���ԭ��ָ�� */
	fwrite(&a,sizeof(score_tab),1,fp);/* ��д��д�ɼ���¼ */
	fclose(fp); /* �ر��ļ���ǿ�ƴ��� */
}
void fill_one_person(score_tab a)
{	FILE *fp;
	int num;
	if((fp = fopen("c:\\score.dat","rb+")) == NULL) /* �򿪳ɼ����ļ� */
		exit(-1);
	num = a.num; /* ��ȡѧ�� */
	fseek(fp,num*sizeof(score_tab),SEEK_SET); /* ����ѧ�Ŷ�λ */
	fwrite(&a,sizeof(score_tab),1,fp); /* ��a �м�¼д�뵽ָ��λ�� */
	fclose(fp); /* �ر��ļ���ǿ�ƴ��� */
}
void read_person(int num)
{	FILE *fp;
	score_tab a;
	if((fp = fopen("c:\\score.dat","rb+")) == NULL) /* �򿪳ɼ����ļ� */
		exit(-1);
	fseek(fp,num*sizeof(score_tab),SEEK_SET); /* ����ѧ�Ŷ�λ */
	fread(&a,sizeof(score_tab),1,fp); /* ��ָ����¼ */
	print_preson(a); /* ��ʾ�ü�¼ */
	fclose(fp); /* �ر��ļ� */
}
//print_preson����������ɼ�����ͷ��Ȼ����ʾѧ��a�ĸ������ݡ�
void print_preson(score_tab a)
{	printf(" num\t    name\t\t Math\t Phys\t Engl\t   C\n");
	printf(" %04d\t %-16s\t%6.2f\t%6.2f\t%6.2f\t %6.2f\n",a.num,a.name, \
				a.score[0],a.score[1],a.score[2],a.score[3]);
}
//print_table������ʾ������Ű༶�ɼ�����
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
