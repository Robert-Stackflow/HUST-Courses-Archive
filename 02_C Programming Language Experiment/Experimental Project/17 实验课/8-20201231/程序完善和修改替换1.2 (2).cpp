#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//Desktop\Operate\Machine_operation\8�ڰ˴��ϻ�20201231\1.2.Ҫ��.exe d:\\a.txt 
int main(int argc, char* argv[])
{
	FILE * fp;
	char ch,buf[128];
	int flag=0,cnt=0;
	if(argc!=2){ 
		printf("Arguments error!\n");
		exit(-1);
	}
	if((fp=fopen(argv[1],"r"))==NULL){      /* fpָ��filename */
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
//          ��Ҫÿ��������������¼����ô˴���cnt=0;
            while (scanf("%s",buf)&& strcmp(buf, "q"))
                continue;
//          ���Ҫ��������������ô˴���system("pause");
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
	            /* ����ʾ����д��filename�ж�ȡ���ַ� */ 
	fclose(fp);                        /* �ر�filename */ 
	return 0;
}

