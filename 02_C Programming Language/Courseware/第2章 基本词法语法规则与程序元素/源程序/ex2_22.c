/************************************************************************************
简要描述：用枚举变量控制循环，输出存储在数组weekName中的英文星期名。
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
