#include "stdio.h"
#include "stdlib.h"
#include "string.h"
typedef struct score_tab{
	char	num[5]; /* 学号 */
	char	course[20]; /* 课程名称 */
	int		score; /* 成绩 */
	struct	score_tab	*next;
} courses;
typedef struct student_tab{
	char	num[5]; 		/* 学号 */
	char	name[10]; 		/* 姓名 */
	char	sex; 			/* 性别 */
	int		age; 			/* 年龄 */
	char	addr[30]; 		/* 家庭住址 */
	char	phone[12];		/* 联系电话 */
	char	*memo; 			/* 备注字段 */
	courses	 *head_score;	/* 指向成绩链的头指针 */
	struct	student_tab	 *next; /* 指向下一个结点的自引用指针 */
} studs;
void create_cross_list(studs **head); /* 创建十字交叉链表 */
void save_cross_list(studs *head); 	/* 保存十字交叉链表数据 */
void load_cross_list(studs **head);  	/*读入已经保存的十字交叉链表数据 */
void traverse_cross_list(studs *head);/* 遍历十字交叉链表 */
int main(void)
{	studs *head = NULL;
	char ch;
lop:
	do{ /* 构造提示菜单，供用户选择 */
		printf("\t\t1: input and create the cross list\n");
		printf("\t\t2: save the cross list\n");
		printf("\t\t3: load the cross list\n");
		printf("\t\t4: traverse the cross list\n");
		scanf("%c",&ch);
		getchar();
	}while(ch < '1' || ch > '4');
	switch(ch){		/* 根据用户输入的选择转移 */
	case '1': /* 创建十字交叉链表处理 */
		create_cross_list(&head);
		break;
	case '2': 	/* 保存十字交叉链表处理 */
		save_cross_list(head);
		break;
	case '3': 	/* 读入十字交叉链表处理 */
		load_cross_list(&head);
		break;
	case '4': 	/* 遍历十字交叉链表处理 */
		traverse_cross_list(head);
	}
	printf("coutinue choice? yes or no?\n");
	ch = getchar();	getchar(); /* 是否继续处理 */
	if(ch == 'y' || ch =='Y')
		goto lop;	
	return 0;
}
void create_cross_list(studs **head) /* 创建十字交叉链表的函数 */
{	studs *hp=NULL,*p;
	courses  * pcrs; 
	char s[80]="",ch;
loop:	
	p = (studs *)malloc(sizeof(studs)); /* 创建学生基本信息的第一个结点 */
	printf("input num,name,sex,age,addr,phone\n");
	scanf("%s %s %c %d %s %s",p->num,p->name,&p->sex,&p->age, \
p->addr,p->phone);/* 输入各项基本数据 */
	getchar(); /* 专门用于读scanf 输入中的换行符 */
	p->head_score = NULL; /* 置成绩链头指针为NULL */
	p->next = hp; /* 学生基本信息链头指针值赋给结点的next 域 */
	hp = p; /* 头指针指向新创建的结点 */
	printf("continue input data of students? yes or no\n");
	ch = getchar();	getchar(); /*是否继续创建学生基本信息结点 */
	if(ch == 'y' || ch =='Y')
		goto loop; /* 是，创建下一个学生基本信息结点 */
	(*head) = hp; /* 调用函数中的head 头指针指向新创建的学生基本信息链 */
	p = (*head); /* p指向学生基本信息链的链头 */
	while(p != NULL){ /* 循环创建每个学生的学习成绩链 */
		printf("input %s student's score? yes or no?\n",p->num);
		ch = getchar(); getchar();
		while(ch == 'y' || ch =='Y'){
			pcrs = (courses *)malloc(sizeof(courses));/* 创建成绩结点 */
			printf("input course,score\n");
			scanf("%s %d", pcrs->course,&pcrs->score);/* 输入课程名和成绩 */
			getchar();
			strcpy(pcrs->num,p->num); /* 学号成员赋值 */
			pcrs->next = p->head_score; /* 头指针值赋给新结点的指针域 */ 
			p->head_score = pcrs; /* 头指针指向新结点 */
			printf("input %s student's score? yes or no?\n",p->num);
			ch = getchar(); getchar();/*是否继续创建成绩结点 */
		}
		p = p->next; /* p指向学生基本信息链的下一个学生 */
	}
}
void traverse_cross_list(studs *head) /* 遍历十字交叉链表的函数 */
{	studs * p = head;
	courses  * pcrs;
	while(p != NULL){ /* 遍历学生基本信息链 */
		printf("%s\t%s\t%c\t%d\t%s\t%s\n",p->num,p->name,p->sex, \
 			p->age,p->addr,p->phone);
		pcrs = p->head_score;
		while(pcrs != NULL){ /* 遍历学生成绩链 */
			printf("%s\t%s\t%d\n",pcrs->num,pcrs->course,pcrs->score);
			pcrs = pcrs->next;
		}
		p =p->next;
	}
}
void save_cross_list(studs *head) /* 保存十字交叉链表的函数 */
{	FILE *out1,*out2;
	studs * p = head;
	courses  * pcrs;
	if((out1 = fopen("c:\\student.dat","wb")) == NULL) /* 打开基本信息文件 */
		exit(-1);
	if((out2 = fopen("c:\\score.dat","wb")) == NULL) /* 打开成绩文件 */
		exit(-1);
	while(p != NULL){
		fwrite(p,sizeof(studs),1,out1);/* 写学生基本信息记录 */
		pcrs = p->head_score; /* 成绩遍历指针指向成绩链链头 */
		while(pcrs != NULL){ /* 遍历学生成绩链 */
			fwrite(pcrs,sizeof(courses),1,out2); /* 写成绩记录 */
			pcrs = pcrs->next; /* 指向下一个成绩结点 */
		}
		p =p->next; /* 指向下一个学生基本信息结点 */
	}
	fclose(out1); /* 关闭基本信息文件 */
	fclose(out2); /* 关闭成绩文件 */
}
void load_cross_list(studs **head) /* 读入十字交叉链表的函数 */
{	FILE *in1,*in2;
	studs *hp=NULL,*p;
	courses  * pcrs; 
	if((in1 = fopen("c:\\student.dat","rb")) == NULL) /* 打开基本信息文件 */
		exit(-1);
	if((in2 = fopen("c:\\score.dat","rb")) == NULL) /* 打开成绩文件 */
		exit(-1);
	while(!feof(in1)){
		p = (studs *)malloc(sizeof(studs)); /* 创建基本信息结点 */
		fread(p,sizeof(studs),1,in1); /* 读一条基本信息记录到结点中 */
		if(!feof(in1)){
			p->head_score = NULL; /* 置成绩链头指针为NULL */
			p->next = hp; /* 学生基本信息链头指针值赋给结点的next 域 */
			hp = p;	/* 头指针指向新创建的结点 */
		}
	}
	(*head) = hp; /* 调用函数中的head 头指针指向新创建的学生基本信息链 */
	while(!feof(in2)){
		pcrs = (courses *)malloc(sizeof(courses)); /* 创建新成绩结点 */
		fread(pcrs,sizeof(courses),1,in2); /* 读一条成绩记录到新结点 */
		if(!feof(in2)){
			p = (*head);/*遍历指针p指向学生基本信息链的链头 */
			while(p != NULL){ /*遍历学生基本信息链 */
				if(!strcmp(p->num , pcrs->num)){ /* 查找相同学号的结点 */
					pcrs->next = p->head_score; /* 找到，新结点加入成绩链 */
					p->head_score = pcrs;
					break;
				}
				else
					p = p->next; /* 没找到，转下一结点 */
			}
		}
	}
	fclose(in1); /* 关闭基本信息文件 */
	fclose(in2); /* 关闭成绩文件 */
}
