/************************************************************************************
��Ҫ��������ö�ٱ�������ѭ��������洢������weekName�е�Ӣ����������
*************************************************************************************/
#include<stdio.h>
enum week { SUN, MON, TUE, WED, THU, FRI, SAT } ;
int main(void)
{
	enum week day;
    char *weekName[ ]={
		"Sunday",
		"Monday",
		"Tuesday",
		"Wednesday",
		"Thursday",
		"Friday",
		"Saturday"
	};
	for(day=SUN;day<=SAT;day++)
		printf("\n%3d\t%s",day,weekName[day]);
    return 0;
}
