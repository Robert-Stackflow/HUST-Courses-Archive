#include<stdio.h>
#include<string.h>
int main()
{
	// ���ڴ˴��༭���Ĵ���
	/********** Begin **********/
    char buf[128];
    int flag = 0, cnt = 0;
    FILE * file;
    if (scanf("%s",buf)&&strcmp(buf,"type_c")!=0)
    {
        printf("ָ�����\n");
        return 0;
    }
    if (scanf("%s",buf) && strcmp(buf,"/p")==0)
    {
        flag=1;
        scanf("%s", buf);
    }
    file = fopen("src/step1_1/test1.c", "r");

    while (fgets(buf,128,file))
    {
        printf("%d  %s", ++cnt, buf);
        if (flag&&cnt==10)
        {
            cnt = 0;
            while (scanf("%s", buf) && strcmp(buf, "q"))
                continue;
        }
    }
    fclose(file);
	/********** End **********/
	return 0; 
}

