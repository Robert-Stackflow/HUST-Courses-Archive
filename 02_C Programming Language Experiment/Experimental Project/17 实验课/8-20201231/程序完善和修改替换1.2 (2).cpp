#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//Desktop\Operate\Machine_operation\8第八次上机20201231\1.2.要求.exe d:\\a.txt 
int main(int argc, char* argv[])
{
	FILE * fp;
	char ch,buf[128];
	int flag=0,cnt=0;
	if(argc!=2){ 
		printf("Arguments error!\n");
		exit(-1);
	}
	if((fp=fopen(argv[1],"r"))==NULL){      /* fp指向filename */
		printf("Can't open %s file!\n",argv[1]);
		exit(-1);
	}
	if(argc>2)	flag=1;
	if(flag==1)
    {
    while(fgets(buf,128,fp))
    {
        printf("%d  %s",++cnt,buf);
        if((cnt%5)==0&&cnt!=0)
        {
//          如要每次输出代码行重新计数用此代码cnt=0;
            while (scanf("%s",buf)&& strcmp(buf, "q"))
                continue;
//          如果要按任意键继续可用此代码system("pause");
        }
    }
	}
	else 
	{
		while(ch!=EOF)
		{
			printf("%d  ",++cnt);
			while((ch=fgetc(fp))!=EOF&&fgetc(fp)!='\n')
			{
				putchar(fgetc(fp));
			}
			printf("\n");
		}	             
	}
	            /* 向显示器中写从filename中读取的字符 */ 
	fclose(fp);                        /* 关闭filename */ 
	return 0;
}

