#include<stdio.h>

/*********************************************************************************
  ��ɺ���������filename1��filename2 �� filename3 �����ļ������ݵ� filename �ļ���
  ������file1��������file2���������file3
  ********************************************************************************/
void connect(char *filename,char *filename1,char *filename2,char *filename3)
{
	// ���ڴ˴��༭���Ĵ���
	/********** Begin **********/
    FILE * in, *out = fopen(filename, "w");
    char buf[256];
    const char * infiles[3] = { filename1, filename2, filename3 };
    for (int i = 0; i < 3; ++i)
    {
        in = fopen(infiles[i], "r");
        while (fgets(buf, 256, in))
        {
            fputs(buf, out);
        }
//        fputc('\n',out);
        fclose(in);
    }
    fclose(out);
	/********** End **********/
   
}

