#include<stdio.h> 
int main(void)
{
	char c,LineNum,CharNum,flag=1;
	LineNum=0;
	CharNum=0;
	printf("Input a string which is ended with'ctrl+z'\n") ;
	while((c=getchar())!=EOF)
	{
		if(flag==1&&c!='\n')	CharNum++;//�˴��Ի��з��Ƿ�����ַ����й涨�����޸�����flag 
		if(c=='\n')		LineNum++;
	} 
	printf("Char:%d\nLine:%d\n",CharNum,LineNum);
	return 0;
}
