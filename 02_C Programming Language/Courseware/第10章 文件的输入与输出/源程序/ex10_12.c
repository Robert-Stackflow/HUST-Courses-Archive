#include "stdio.h"
/*���������������£�*/
struct date{
char		month[10];
int  	day;
int  	year;
};
/*������ѧ��������ϢǶ�׽ṹ����struct stu_info��*/
struct stu_info{ 		
char		num[12]; 			/* ѧ�� */
	char		name[9]; 			/* ���� */
	char		sex;				    /* �Ա� */
	struct	date		birthday;	/* �������� */
	char		address[60];		    /* ��ͥסַ */
	double	income;				/* ��ͥ���� */ 
	char		phone_number[16];	/* ��ϵ�绰 */
	char		email[40];			/* �������� */
};

int main(void)
{	struct date d;/*�����������ͽṹ����*/
	struct stu_info s,*p=&s;/*����struct stu_info���ͽṹ�����ͽṹָ��*/
	FILE *in,*out;
	int x=1;
	if((out = fopen("c:\\stu_info_table.dat","wb")) == NULL)
		exit(-1);
	while(x!=-1){
		printf("����������ڣ���ʽ��������\n");
		scanf("%s%d%d",d.month,&d.day,&d.year);/*�����������*/	
		getchar();/*��scanf�����Ļ��з�*/ 
		s.birthday=d;
		printf("����ѧ�š���������ͥסַ����ϵ�绰����������\n");
		scanf("%s%s%s%s%s",s.num,s.name,s.address,s.phone_number,s.email);
		getchar();/*��scanf�����Ļ��з�*/
		printf("�����Ա�\n");
		scanf("%c",&s.sex);
		getchar();/*��scanf�����Ļ��з�*/ 
		printf("�����ͥ����\n");
		scanf("%lf",&s.income); getchar();/*��scanf�����Ļ��з�*/
		fwrite(&s,sizeof(struct stu_info),1,out); 
		printf("����������-1����\n");
		scanf("%d",&x);	getchar();/*��scanf�����Ļ��з�*/ 
	}
	fclose(out);
	if((in = fopen("c:\\stu_info_table.dat","rb")) == NULL)
		exit(-1);
	while(!feof(in)){
		fread(&s,sizeof(struct stu_info),1,in); 
		if(!feof(in)){
			printf("ѧ��=%s\t����=%s\t�Ա�=%c\t", s.num,s.name,s.sex);
			printf("��������=%4d-%s-%d\n", s.birthday.year,s.birthday.month,s.birthday.day);
			printf("��ͥסַ=%s\n��ͥ����=%lf\n", s.address,s.income);
			printf("��ϵ�绰=%s\n��������=%s\n", s.phone_number,s.email);
		}
	}
	fclose(in);
}
