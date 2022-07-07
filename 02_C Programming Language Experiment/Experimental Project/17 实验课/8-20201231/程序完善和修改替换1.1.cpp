#include<stdio.h>
#include<stdlib.h>
//Desktop\Operate\Machine_operation\8第八次上机20201231\程序完善和修改替换1.1.exe d:\\a.txt
int main(int argc,char * argv[])
{
	char ch;
	FILE *fp;
	if(argc!=2){
		printf("Arguments error!\n");
		exit(-1);
	}
	if((fp=fopen(argv[1],"r"))==NULL)
	{
		printf("Can't open %s file!\n",argv[1]);
		exit(-1);
	}
	while((ch=fgetc(fp))!=EOF)     		
           putchar(ch);
	fclose(fp);
	return 0;
 } 
