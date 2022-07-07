#include "stdio.h"
int main(int num, char* v[])/*用num代替argc,用v代替argv*/
{	int n=0;	/*上面v是字符指针数组的数组名*/
	while(n<num){/*num是命令行参数的个数*/
		printf("&v[%d]=%p\t",n,&v[n]);/*输出指针数组元素的地址*/
		printf("&v[%d][0]=%p\t",n,v[n]);/*输出元素的内容，即字符串参数的地址*/
		printf("v[%d]=%s\n",n,v[n]);/*输出指针数组元素指向的字符串*/
		n++;
  }
  return 0;
}