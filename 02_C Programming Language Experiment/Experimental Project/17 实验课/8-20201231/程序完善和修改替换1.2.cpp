#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//Desktop\Operate\Machine_operation\8�ڰ˴��ϻ�20201231\�������ƺ��޸��滻1.2.exe d:\\a.txt
int main(int argc,char * argv[])
{
	char ch,buf[128],cmd;
	int flag=0,cnt=0;
	FILE *fp;
	if(argc!=2&&argc!=3){
		printf("Arguments error!\n");
		exit(-1);
	}
	if((fp=fopen(argv[1],"r"))==NULL)
	{
		printf("Can't open %s file!\n",argv[1]);
		exit(-1);
	}
    if(argc>2&&strcmp(argv[2],"/p")==0)	flag=1;
    fp=fopen(argv[1],"r");
    if(flag==1)
    {
    while(fgets(buf,128,fp))
    {
        printf("%d  %s",++cnt,buf);
        if((cnt%5)==0&&cnt!=0)
        {
//          ��Ҫÿ��������������¼����ô˴���cnt=0;
//			scanf("%c",cmd);
//            while (cmd=='q')
//                continue;
//          ���Ҫ��������������ô˴���system("pause");
        }
    }
	}
	else 
	{
		while(fgets(buf,128,fp))
        	printf("%d  %s",++cnt,buf);
	}
//	while((ch=fgetc(fp))!=EOF)     		
//           putchar(ch);
	fclose(fp);
	return 0;
 } 
