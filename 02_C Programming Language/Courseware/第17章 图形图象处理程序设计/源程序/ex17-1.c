/*  读取指定图像（灰度图或真彩色图）的位图信息头，颜色表和位图像素数据。输出图像的宽度和高度信息。*/
#include<windows.h>
#include<stdio.h>
#include<stdlib.h>

int ReadBmp(const char *bmpName); /* 函数原型 */

BITMAPFILEHEADER fileHead; /* 文件信息头    */
BITMAPINFOHEADER infoHead; /* 位图信息头    */
RGBQUAD    *pColorTable;   /* 颜色表指针    */
unsigned char *pBmpBuf;    /* 图像数据的指针*/
int bmpWidth;              /* 图像的宽      */
int bmpHeight;             /* 图像的高      */
int biBitCount;            /* 每像素位数    */
int lineByte;              /*每行的字节数 */

int main(int argc,char *argv[])
{
	if(argc<2)  /* 未指定bmp文件名 */
	{
		printf("Command line error.\n");
		return -1;
	}
    if(ReadBmp(argv[1]))  /* 读文件成功 */
	{
		printf("%s的宽度和高度为:%d×%d\n",argv[1],bmpWidth,bmpHeight);
	}
	return 0;
}

/****************************************************************
函数名称：ReadBmp
函数功能：
      读给定图像(灰度图像或真彩色图像）的位图数据、宽、高、颜色表及每像素位数等数据进内存，
	  存放在相应的全局变量中
函数参数：
          char *bmpName: 文件名字及路径
函数返回值：0为失败，1为成功
****************************************************************/
int ReadBmp(const char *bmpName)
{
    FILE *fp=fopen(bmpName,"rb");/* 二进制读方式打开指定的图像文件 */
    if(fp==NULL) return 0;

    fread(&fileHead,sizeof(BITMAPFILEHEADER),1,fp); /* 读取文件信息头进内存，存放在变量fileHead中*/
    fread(&infoHead,sizeof(BITMAPINFOHEADER),1,fp);/* 读取位图信息头进内存，存放在变量head中 */

	bmpWidth = infoHead.biWidth;	/* 获取图像宽、高、每像素所占位数等信息 */
    bmpHeight = infoHead.biHeight;
    biBitCount = infoHead.biBitCount;

	lineByte=(bmpWidth * biBitCount/8+3)/4*4; /* 计算图像每行像素所占的字节数（必须是4的倍数） */

	if(biBitCount==8) /* 灰度图像有颜色表，且颜色表表项为256 */
	{

        pColorTable=(RGBQUAD *)malloc(sizeof(RGBQUAD)*256);  /* 申请颜色表所需要的空间 */
        fread(pColorTable,sizeof(RGBQUAD),256,fp); /* 读颜色表进内存 */
    }

    pBmpBuf=(unsigned char *)malloc(sizeof(unsigned char)*lineByte * bmpHeight);  /* 申请位图数据所需要的空间 */
    fread(pBmpBuf,1,lineByte * bmpHeight,fp);   /* 读位图数据进内存 */

    fclose(fp);
    return 1;
}
