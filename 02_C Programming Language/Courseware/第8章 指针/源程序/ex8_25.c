#include "stdio.h"
int main(int argc, char* argv[])
{	int n=0;
	while(n<argc){
		printf("%s", argv[n]);/*输出命令行中的各个字符串参数*/
		(n<argc-1)?printf(" "):printf("\n");/*若n==argc-1，输出换行*/
		n++;
	}
	printf("the number of command-line arguments are %d\n",argc);
	return 0;
}
