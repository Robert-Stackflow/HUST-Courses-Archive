#include "stdio.h"
#include "fcntl.h"
#include "io.h"
#include "stdlib.h"
/* 没有包含stat.h，自己定义S_IREAD 和S_IWRITE */
#define S_IREAD	0x0100	/* 只读方式 */
#define S_IWRITE  0x0080	/*只写方式*/
#define BUF_SIZE  512 /* 缓冲大小为512字节 */
int main(int argc,char *argv[])
{	int in,out,num,i;
	unsigned char s[BUF_SIZE];
	if((in = open(argv[1],O_RDONLY)) == -1){/* 以只读方式打开源文件*/
		printf("open source file failed!\n");
		exit(-1);
	} /* 下面以读写方式打开目标文件 */
	if((out = creat(argv[2],S_IREAD | S_IWRITE)) == -1){
		printf("create target file failed!\n");
		exit(-1);
	}
	while((num = read(in,s,BUF_SIZE))>0){ /* 读源文件 */
		if(write(out,s,num) != num){ /* 写目标文件 */
			printf("write error on %s\n",argv[2]);
			exit(-1);
		}
	}
	close(in); /* 关闭源文件 */
	close(out); /* 关闭目标文件 */
	in = open(argv[2],O_RDONLY); /* 重新打开已拷贝文件 */
	while((num = read(in,s,BUF_SIZE))>0){ /* 读已拷贝文件 */
		i=0;
		while(i<=num) /* 循环输出已读入的num 的字符 */
			putchar(s[i++]);
	}
	putchar('\n');
	close(in); 
	return 0;
}
