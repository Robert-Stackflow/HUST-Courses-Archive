#include "stdio.h"
/*日期类型声明如下：*/
struct date{
char		month[10];
int  	day;
int  	year;
};
/*声明大学生基本信息嵌套结构类型struct stu_info：*/
struct stu_info{ 		
char		num[12]; 			/* 学号 */
	char		name[9]; 			/* 姓名 */
	char		sex;				    /* 性别 */
	struct	date		birthday;	/* 出生日期 */
	char		address[60];		    /* 家庭住址 */
	double	income;				/* 家庭收入 */ 
	char		phone_number[16];	/* 联系电话 */
	char		email[40];			/* 电子邮箱 */
};

int main(void)
{	struct date d;/*声明日期类型结构变量*/
	struct stu_info s,*p=&s;/*声明struct stu_info类型结构变量和结构指针*/
	FILE *in,*out;
	int x=1;
	if((out = fopen("c:\\stu_info_table.dat","wb")) == NULL)
		exit(-1);
	while(x!=-1){
		printf("输入出生日期，格式：月日年\n");
		scanf("%s%d%d",d.month,&d.day,&d.year);/*输入出生日期*/	
		getchar();/*读scanf输入后的换行符*/ 
		s.birthday=d;
		printf("输入学号、姓名、家庭住址、联系电话、电子邮箱\n");
		scanf("%s%s%s%s%s",s.num,s.name,s.address,s.phone_number,s.email);
		getchar();/*读scanf输入后的换行符*/
		printf("输入性别\n");
		scanf("%c",&s.sex);
		getchar();/*读scanf输入后的换行符*/ 
		printf("输入家庭收入\n");
		scanf("%lf",&s.income); getchar();/*读scanf输入后的换行符*/
		fwrite(&s,sizeof(struct stu_info),1,out); 
		printf("继续输入吗？-1结束\n");
		scanf("%d",&x);	getchar();/*读scanf输入后的换行符*/ 
	}
	fclose(out);
	if((in = fopen("c:\\stu_info_table.dat","rb")) == NULL)
		exit(-1);
	while(!feof(in)){
		fread(&s,sizeof(struct stu_info),1,in); 
		if(!feof(in)){
			printf("学号=%s\t姓名=%s\t性别=%c\t", s.num,s.name,s.sex);
			printf("出生日期=%4d-%s-%d\n", s.birthday.year,s.birthday.month,s.birthday.day);
			printf("家庭住址=%s\n家庭收入=%lf\n", s.address,s.income);
			printf("联系电话=%s\n电子邮箱=%s\n", s.phone_number,s.email);
		}
	}
	fclose(in);
}
