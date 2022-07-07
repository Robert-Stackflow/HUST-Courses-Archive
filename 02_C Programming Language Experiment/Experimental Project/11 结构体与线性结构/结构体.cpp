#include<stdio.h>
#define N 3
//结构体的定义与赋值及初始化
//存储空间分配，把占字节数最大的变量放到最前或最后定义
//定义指针并用指针对结构体进行访问(->箭头运算符) 
//访问结构体的三种方式
//定义函数对结构体进行操作（并利用指针使用箭头再次尝试操作）
//利用typedef定义结构型类名（系统的数据类型和自己定义的数据类型都可）
//例如typedef int integer 
//再例如typedef struct person{...}myperson;
//typedef struct person myperson; 
//另外也可以给指向结构体或者其他类型的指针取别名
//把多个相同结构体类型的元素存入一个数组中（结构数组）,并利用指针对其进行操作
//嵌套结构体的定义与使用（如一个人的出生日期的年/月/日/时/分/秒)
//再例如家庭住址的省/市/县/乡/村/组别
//对商品的名称与商品识别码及价格进行排序，用要求实现菜单与查找功能并尽量用函数封装功能
struct person{
	char name[18];
	int age;
	double height;	
};//定义一个结构体同时初始化 
typedef struct result{
	char name[18];
	int programming;
	double math;
}result;//将结构体进行再命名 
struct stu_study{
	char num[6];
	char name[18];
	char sex;
	int English;
	int Math,Physics,C_programming;
}XRD={"15533","Xu Ruida",'m',81,92,76,85};
//定义结构体变量XRD同时对其进行初始化
struct date{
	int year;
	int month;
	int day;
	int hour;
}; //定义日期结构体 
struct address{
	char province[10];
	char city[10];
	char county[10];
	char villege[10];
	int  group; 
};//定义地址结构体 
struct information
{
	char name[18];
	struct date birthday;
	struct address house;
};//嵌套结构体表述学生的姓名，出生日期，家庭住址 
int main(void)
{
	printf("stu_study类型的结构体变量XRD的各项内容如下：%s\t%s\t%c\t%d\t%d\t%d\t%d\n",XRD.num,XRD.name,XRD.sex,XRD.English,XRD.Math,XRD.Physics,XRD.C_programming);
	struct person a,*pa=&a;
	printf("请依次输入姓名，年龄，身高：");
	scanf("%s%d%lf",&a.name,&a.age,&a.height); 
	printf("person类型的结构体a的姓名、年龄与身高分别如下：%s\t%d\t%.1lf\n",a.name,a.age,a.height);
	result b={"hust",89,92},*pb=&b;
	printf("result类型的结构体b的姓名、编程成绩和数学成绩分别如下：%s\t%d\t%.1lf",pb->name,pb->programming,pb->math);
	struct person grade[N];//定义结构数组用于存储至多N个人的信息 
	for(int i=0;i<N;i++)
		scanf("%s%d%lf",&grade[i].name,&grade[i].age,&grade[i].height);
	for(int i=0;i<N;i++)
		printf("第%d个人的信息为%s\t%d\t%lf\n",i+1,grade[i].name,grade[i].age,grade[i].height);
}
