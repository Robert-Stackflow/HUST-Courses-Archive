#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "assert.h"
struct c_score_tab{ 
		char *num;		/* ѧ�� */
		char *name; 		/*���� */
		int	c; 			/* C���Կγ̳ɼ� */
};
void dynamic_input(char *s1,char **s2);
void dynamic_input(char *s1,char **s2)
{ /*�ַ�ָ���β�s1ָ����ʾ�Ե�ʵ���ַ��� */
		char *pc;
		int len;
		pc=(char *)malloc(40*sizeof(char));/* ��̬����40���ֽڣ�����pcָ�� */
		assert(pc); /* �ж�pc�Ƿ�Ϊ�ա�Ϊ�գ��˳�������˳��ִ�� */
		printf(s1); /* ������Ҫ�����ͬ����ʾ */
		gets(pc); /* �Ӽ��̽���������ַ��� */
		len=strlen(pc); /* ����������ַ����ĳ��� */
		(*s2)=(char *)malloc(len*sizeof(char)+1);/*�������봮�����ʵ�����洢*/
		assert((*s2));
		strcpy((*s2),pc); /* �����봮��������̬����Ĵ洢�� */
		free(pc); /* �ͷ�pcָ��Ķ�̬�洢�� */
}
int main(void)
{	int n,i;
		struct c_score_tab *p;
		printf("input the number of students please!\n");
		scanf("%d",&n);
		getchar(); /* getchar���ڶ�����scanf����Ļس��� */
/* ��̬����n����¼��ÿ����¼�Ĵ�СΪsizeof(struct c_score_tab) */
		p=(struct c_score_tab *)malloc(n*sizeof(struct c_score_tab));
		assert(p);
		for(i=0;i<n;i++){
			dynamic_input("input num!\n",&(p+i)->num);/* ����ѧ�Ŵ��� */
			dynamic_input("input name!\n",&(p+i)->name); /* ������������ */
			printf("input score!\n");
			scanf("%d",&(*(p+i)).c); /* ����C���Կγ̳ɼ� */
			getchar();
		}
		printf("\n");
		for(i=0;i<n;i++) /* ��ӡ�ɼ��� */
			printf("unm=%s\tname=%s\tscore=%d\n",(p+i)->num,(p+i)->name,(p+i)->c);
		printf("\n");
		free(p); /* �ͷųɼ���ռ�ݵĴ洢 */
		return 0;
}
