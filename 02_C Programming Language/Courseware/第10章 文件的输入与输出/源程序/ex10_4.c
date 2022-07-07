#include "stdio.h"
#include "stdlib.h"
int main(int argc, char* argv[])
{	int ch;
	if(argc!=3){/*命令行参数数目不等于3，说明命令行格式不对*/
		printf("Arguments error!\n");
		exit(-1);
	}
	if(freopen(argv[1],"r",stdin)==NULL){ /* stdin指向source_file */
		printf("Can't open %s file!\n",argv[1]);
		exit(-1);
	}
	freopen(argv[2],"w",stdout); /* 使stdout指向target_file */
	while((ch=getchar())!=EOF) /* 从source_file中读字符 */
		putchar(ch); /* 向target_file中写字符，实现拷贝复制 */
	fclose(stdin); /* 关闭source_file */
	fclose(stdout); /* 关闭target_file */
	return 0;
}
