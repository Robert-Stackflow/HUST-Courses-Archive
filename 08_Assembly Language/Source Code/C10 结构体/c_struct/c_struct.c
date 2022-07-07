//#include <stdio.h>
//#pragma  pack(1)
#include <stdio.h>
#include <stddef.h>

typedef  struct {
	int  CID;          // 课程编号
	char CTITLE[20];   // 课程名
	char CHOUR;        // 学时数
	char CTEACHER[10]; // 主讲教师
	char CTERM;       // 开课学期
}COURSE;


typedef  struct {
	char DNAME[10]; // 系名
	char DADDRESS[10]; // 系的办公地址
	COURSE  COURSETABLE; //课表，5 门课
}DEPARTMENT;

typedef  struct {
	char F1;
	int  F2;
}TEMPS;
void f(COURSE x)
{
	printf("%d\n", x.CHOUR);
	return;
}
int main(int argc, char* argv[])
{
	COURSE  temp;
	DEPARTMENT dtemp;
	TEMPS T;
	int  i, j, k;
	i = offsetof(TEMPS, F1);
	j = offsetof(TEMPS, F2);
	k = sizeof(TEMPS);
	temp.CID = 10;
	strcpy(temp.CTITLE, "Chinese");
	dtemp.COURSETABLE.CID = 1010;
	f(temp);
	int  x = offsetof(COURSE, CTITLE);

	printf("sizeof course %d %d\n", sizeof(COURSE), offsetof(COURSE, CTITLE));

	return 0;
}