#include<stdio.h>

/*********************************************************************************
  完成函数，连接filename1、filename2 和 filename3 三个文件的内容到 filename 文件中
  先连接file1，再连接file2，最后连接file3
  ********************************************************************************/
void connect(char *filename,char *filename1,char *filename2,char *filename3)
{
	// 请在此处编辑您的代码
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

