//#include <stdio.h>
//#pragma  pack(1)
#include <stdio.h>
#include <stddef.h>

typedef  struct {
	int  CID;          // �γ̱��
	char CTITLE[20];   // �γ���
	char CHOUR;        // ѧʱ��
	char CTEACHER[10]; // ������ʦ
	char CTERM;       // ����ѧ��
}COURSE;


typedef  struct {
	char DNAME[10]; // ϵ��
	char DADDRESS[10]; // ϵ�İ칫��ַ
	COURSE  COURSETABLE; //�α�5 �ſ�
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