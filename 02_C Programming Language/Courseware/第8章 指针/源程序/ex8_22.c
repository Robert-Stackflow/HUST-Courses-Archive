#include "stdio.h"
void error_prompt(int err_code);
int main(void)
{	int n;
	while(1){
		scanf("%d",&n);
		if(n ==-1)	break;
		error_prompt(n);/*根据出错编号调用出错提示函数*/
	}
	return 0;
}
void error_prompt(int err_code)/*定义出错提示函数*/
{	char *perror[]={ /* perror中的每个元素都指向特定的出错提示字符串。 */
		"can't open file!","read error!",
		"write error!","illegal access exception!"};
	printf("error code:%d :%s\n",err_code,perror[err_code]);/*根据编号输出提示信息*/
}

