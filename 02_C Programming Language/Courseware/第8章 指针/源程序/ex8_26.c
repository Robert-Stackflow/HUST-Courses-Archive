#include "stdio.h"
int main(int argc, char* argv[])
{	int n=0;
    while(n<argc){
		printf("&argv[%d]=%p\t",n,&argv[n]);/*输出指针数组元素的地址*/
		printf("argv[%d]=%p\t",n,argv[n]);/*输出指针数组元素的内容，即字符串参数的地址*/
		printf("argv[%d]->%s\n",n,argv[n]);/*输出指针数组元素指向的字符串*/
		n++;
    }
    return 0;
}
