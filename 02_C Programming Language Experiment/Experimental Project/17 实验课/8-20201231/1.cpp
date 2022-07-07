#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//Desktop\Study\C_programming\Operate\Machine_operation\8第八次上机20201231\1.exe d:\\a.txt the xuruida
int main(int argc, char*argv[])
{
    FILE *fp1,*fp2;
    char *fileName1,*old,*news;
    char fileName2[20]="d:\\b.txt";
    long len;
    char s[20];
    if (argc==4)
    {
      fileName1=argv[1];
      old=argv[2];
      news=argv[3];  
    }
	else
    {
    	printf("Arguments error!\n");
		exit(-1);
    }
    if((fp1=fopen(argv[1],"r"))==NULL)
	{
		printf("Can't open %s file!\n",fileName1);
		exit(-1);
	}
    if ((fp2=fopen(fileName2,"w"))==NULL)
    {
        printf("Can't open %s file!\n",fileName2);
		exit(-1);
    }
    len=strlen(old);
    int flag=0,count=0,number;
    while(fgets(s,len+1,fp1))
    {
        if (strcmp(s,old)==0)
        {
        	fputs(news,fp2);number=0;
        	count++; 
        }
		else	
		{
			if(number==len)	fputs(s,fp2);number=0;
		}
        flag++;
        number++;
        fseek(fp1,flag,SEEK_SET); 
    }
    printf("%d",count);
    fclose(fp1);
    fclose(fp2);
    return 0;
}
