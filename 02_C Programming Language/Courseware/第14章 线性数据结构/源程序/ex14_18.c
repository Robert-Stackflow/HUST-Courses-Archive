#include "stdio.h"
#include "stdlib.h"
#include "string.h"
typedef struct score_tab{
	char	num[5]; /* ѧ�� */
	char	course[20]; /* �γ����� */
	int		score; /* �ɼ� */
	struct	score_tab	*next;
} courses;
typedef struct student_tab{
	char	num[5]; 		/* ѧ�� */
	char	name[10]; 		/* ���� */
	char	sex; 			/* �Ա� */
	int		age; 			/* ���� */
	char	addr[30]; 		/* ��ͥסַ */
	char	phone[12];		/* ��ϵ�绰 */
	char	*memo; 			/* ��ע�ֶ� */
	courses	 *head_score;	/* ָ��ɼ�����ͷָ�� */
	struct	student_tab	 *next; /* ָ����һ������������ָ�� */
} studs;
void create_cross_list(studs **head); /* ����ʮ�ֽ������� */
void save_cross_list(studs *head); 	/* ����ʮ�ֽ����������� */
void load_cross_list(studs **head);  	/*�����Ѿ������ʮ�ֽ����������� */
void traverse_cross_list(studs *head);/* ����ʮ�ֽ������� */
int main(void)
{	studs *head = NULL;
	char ch;
lop:
	do{ /* ������ʾ�˵������û�ѡ�� */
		printf("\t\t1: input and create the cross list\n");
		printf("\t\t2: save the cross list\n");
		printf("\t\t3: load the cross list\n");
		printf("\t\t4: traverse the cross list\n");
		scanf("%c",&ch);
		getchar();
	}while(ch < '1' || ch > '4');
	switch(ch){		/* �����û������ѡ��ת�� */
	case '1': /* ����ʮ�ֽ��������� */
		create_cross_list(&head);
		break;
	case '2': 	/* ����ʮ�ֽ��������� */
		save_cross_list(head);
		break;
	case '3': 	/* ����ʮ�ֽ��������� */
		load_cross_list(&head);
		break;
	case '4': 	/* ����ʮ�ֽ��������� */
		traverse_cross_list(head);
	}
	printf("coutinue choice? yes or no?\n");
	ch = getchar();	getchar(); /* �Ƿ�������� */
	if(ch == 'y' || ch =='Y')
		goto lop;	
	return 0;
}
void create_cross_list(studs **head) /* ����ʮ�ֽ�������ĺ��� */
{	studs *hp=NULL,*p;
	courses  * pcrs; 
	char s[80]="",ch;
loop:	
	p = (studs *)malloc(sizeof(studs)); /* ����ѧ��������Ϣ�ĵ�һ����� */
	printf("input num,name,sex,age,addr,phone\n");
	scanf("%s %s %c %d %s %s",p->num,p->name,&p->sex,&p->age, \
p->addr,p->phone);/* �������������� */
	getchar(); /* ר�����ڶ�scanf �����еĻ��з� */
	p->head_score = NULL; /* �óɼ���ͷָ��ΪNULL */
	p->next = hp; /* ѧ��������Ϣ��ͷָ��ֵ��������next �� */
	hp = p; /* ͷָ��ָ���´����Ľ�� */
	printf("continue input data of students? yes or no\n");
	ch = getchar();	getchar(); /*�Ƿ��������ѧ��������Ϣ��� */
	if(ch == 'y' || ch =='Y')
		goto loop; /* �ǣ�������һ��ѧ��������Ϣ��� */
	(*head) = hp; /* ���ú����е�head ͷָ��ָ���´�����ѧ��������Ϣ�� */
	p = (*head); /* pָ��ѧ��������Ϣ������ͷ */
	while(p != NULL){ /* ѭ������ÿ��ѧ����ѧϰ�ɼ��� */
		printf("input %s student's score? yes or no?\n",p->num);
		ch = getchar(); getchar();
		while(ch == 'y' || ch =='Y'){
			pcrs = (courses *)malloc(sizeof(courses));/* �����ɼ���� */
			printf("input course,score\n");
			scanf("%s %d", pcrs->course,&pcrs->score);/* ����γ����ͳɼ� */
			getchar();
			strcpy(pcrs->num,p->num); /* ѧ�ų�Ա��ֵ */
			pcrs->next = p->head_score; /* ͷָ��ֵ�����½���ָ���� */ 
			p->head_score = pcrs; /* ͷָ��ָ���½�� */
			printf("input %s student's score? yes or no?\n",p->num);
			ch = getchar(); getchar();/*�Ƿ���������ɼ���� */
		}
		p = p->next; /* pָ��ѧ��������Ϣ������һ��ѧ�� */
	}
}
void traverse_cross_list(studs *head) /* ����ʮ�ֽ�������ĺ��� */
{	studs * p = head;
	courses  * pcrs;
	while(p != NULL){ /* ����ѧ��������Ϣ�� */
		printf("%s\t%s\t%c\t%d\t%s\t%s\n",p->num,p->name,p->sex, \
 			p->age,p->addr,p->phone);
		pcrs = p->head_score;
		while(pcrs != NULL){ /* ����ѧ���ɼ��� */
			printf("%s\t%s\t%d\n",pcrs->num,pcrs->course,pcrs->score);
			pcrs = pcrs->next;
		}
		p =p->next;
	}
}
void save_cross_list(studs *head) /* ����ʮ�ֽ�������ĺ��� */
{	FILE *out1,*out2;
	studs * p = head;
	courses  * pcrs;
	if((out1 = fopen("c:\\student.dat","wb")) == NULL) /* �򿪻�����Ϣ�ļ� */
		exit(-1);
	if((out2 = fopen("c:\\score.dat","wb")) == NULL) /* �򿪳ɼ��ļ� */
		exit(-1);
	while(p != NULL){
		fwrite(p,sizeof(studs),1,out1);/* дѧ��������Ϣ��¼ */
		pcrs = p->head_score; /* �ɼ�����ָ��ָ��ɼ�����ͷ */
		while(pcrs != NULL){ /* ����ѧ���ɼ��� */
			fwrite(pcrs,sizeof(courses),1,out2); /* д�ɼ���¼ */
			pcrs = pcrs->next; /* ָ����һ���ɼ���� */
		}
		p =p->next; /* ָ����һ��ѧ��������Ϣ��� */
	}
	fclose(out1); /* �رջ�����Ϣ�ļ� */
	fclose(out2); /* �رճɼ��ļ� */
}
void load_cross_list(studs **head) /* ����ʮ�ֽ�������ĺ��� */
{	FILE *in1,*in2;
	studs *hp=NULL,*p;
	courses  * pcrs; 
	if((in1 = fopen("c:\\student.dat","rb")) == NULL) /* �򿪻�����Ϣ�ļ� */
		exit(-1);
	if((in2 = fopen("c:\\score.dat","rb")) == NULL) /* �򿪳ɼ��ļ� */
		exit(-1);
	while(!feof(in1)){
		p = (studs *)malloc(sizeof(studs)); /* ����������Ϣ��� */
		fread(p,sizeof(studs),1,in1); /* ��һ��������Ϣ��¼������� */
		if(!feof(in1)){
			p->head_score = NULL; /* �óɼ���ͷָ��ΪNULL */
			p->next = hp; /* ѧ��������Ϣ��ͷָ��ֵ��������next �� */
			hp = p;	/* ͷָ��ָ���´����Ľ�� */
		}
	}
	(*head) = hp; /* ���ú����е�head ͷָ��ָ���´�����ѧ��������Ϣ�� */
	while(!feof(in2)){
		pcrs = (courses *)malloc(sizeof(courses)); /* �����³ɼ���� */
		fread(pcrs,sizeof(courses),1,in2); /* ��һ���ɼ���¼���½�� */
		if(!feof(in2)){
			p = (*head);/*����ָ��pָ��ѧ��������Ϣ������ͷ */
			while(p != NULL){ /*����ѧ��������Ϣ�� */
				if(!strcmp(p->num , pcrs->num)){ /* ������ͬѧ�ŵĽ�� */
					pcrs->next = p->head_score; /* �ҵ����½�����ɼ��� */
					p->head_score = pcrs;
					break;
				}
				else
					p = p->next; /* û�ҵ���ת��һ��� */
			}
		}
	}
	fclose(in1); /* �رջ�����Ϣ�ļ� */
	fclose(in2); /* �رճɼ��ļ� */
}
