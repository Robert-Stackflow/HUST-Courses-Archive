#include <windows.h>     
#include <stdio.h>     
#include <stdlib.h>     
#include <malloc.h>  

int gbrToGrey(char *OriginalBMP,char *ResultBMP);
int ReadBmp(const char *bmpName);
int SaveBmp(char *bmpName, unsigned char *imgBuf, int width, int height, 
             int biBitCount, RGBQUAD *pColorTable);

BITMAPFILEHEADER fileHead;      /* 文件信息头*/
BITMAPINFOHEADER infoHead;      /* 位图信息头*/
RGBQUAD    pColorTable[256];    /* 颜色表 */
unsigned char *pBmpBuf;     /* 24位图像数据的指针*/
int        bmpWidth;       /*图像的宽*/
int        bmpHeight;      /*图像的高*/
int        lineByte;      /*每行的字节数 */
int        biBitCount;     /*图像类型，每像素位数*/

int main()  
{  
    gbrToGrey("c.bmp","c_grey.bmp"); 
	return 0;  
} 

/****************************************************************
函数名称：gbrToGrey
函数功能：
      实现将24位BMP图像数据转化成8位BMP图像数据
函数参数：
          char *OriginalBMP： 24位原图像文件名
		  char *ResultBMP :   转换后的8位图像文件名
函数返回值：0为成功，-1为失败
****************************************************************/
int gbrToGrey(char *OriginalBMP,char *ResultBMP)  
{  
	 unsigned char *pNewBmpBuf;  /* 转换后8位图像数据的指针*/
	 unsigned char b,g,r,grey;   /* 颜色分量和灰度级 */ 
	 int nWidth;   /* 图像的实际宽度 */   
	 int i,j;  
 	 ReadBmp(OriginalBMP);
	 if(infoHead.biBitCount != 24 )  /* 不是24位图像 */
	 {  
		puts("This bmp file is not a 24bit."); 
		return -1;
	 } 
     nWidth=(bmpWidth+3)/4*4;     /* 图像的实际宽度（必须是4的倍数） */         
     pNewBmpBuf=(unsigned char *)calloc(nWidth * bmpHeight,sizeof(unsigned char));
	 for(i=0;i<bmpHeight;i++)  
	 {
         for(j=0;j<bmpWidth;j++)  
		 {  
                 b=  pBmpBuf[i*lineByte+j*3];  
	             g = pBmpBuf[i*lineByte+j*3+1]; 
			     r = pBmpBuf[i*lineByte+j*3+2];
			     grey = ( 77 * r + 151 * g + 28 * b) >> 8; /* 真彩色转灰度核心算法 */  
                 pNewBmpBuf[i*nWidth+j]=grey; 
         }  
	 }
	 for(i=0;i<256;i++)    /*  设置调色板  */  
     { 
		 pColorTable[i].rgbBlue=i;  
         pColorTable[i].rgbGreen=i;  
         pColorTable[i].rgbRed=i;  
         pColorTable[i].rgbReserved=0;  
     }
	 SaveBmp(ResultBMP,pNewBmpBuf,bmpWidth,bmpHeight,8,pColorTable); /* 保存8位灰度图像 */
	 return 0; 
} 

/****************************************************************************
函数名称：ReadBmp
函数描述：给定文件的名称和路径 读入图像的位图数据，宽，高，及每个像素的位数进内存，保存在全局变量中
函数参数：const char *bmpName 读入bmp格式文件的名称及路径
函数返回值：0为失败; 1为成功

***************************************************************************/
int ReadBmp(const char *bmpName)
{
	FILE *fp=fopen(bmpName,"rb");
    if(fp==NULL)
	{
		printf("cannot open the file\n");
		return 0;
	}
	fread(&fileHead,sizeof(BITMAPFILEHEADER),1,fp); 
	fread(&infoHead,sizeof(BITMAPINFOHEADER),1,fp);
	bmpWidth = infoHead.biWidth;
	bmpHeight = infoHead.biHeight;
	biBitCount = infoHead.biBitCount;
	lineByte = (bmpWidth *biBitCount/8+3)/4*4;    /*计算图像每行像素所占的字节数*/
	if(biBitCount == 8)  
	{
		fread(pColorTable,sizeof(RGBQUAD),256,fp);
	}
	pBmpBuf = (unsigned char *)malloc(sizeof(unsigned char)*lineByte *bmpHeight);
	fread(pBmpBuf,1,lineByte *bmpHeight,fp);
	fclose(fp);
	return 1;
}

/****************************************************************
函数名称：SaveBmp
函数功能：
       给定一个图像位图(灰度图像或真彩色图像）数据、宽、高、颜色表指针及每像素所占的位数等信息，
       将其写到指定文件中
函数参数：
    char *bmpName-文件名字及路径
    unsigned char *imgBuf-待存盘的位图数据
    int width-以像素为单位待存盘位图的宽
    int  height-以像素为单位待存盘位图高
    int biBitCount-每像素所占位数
    RGBQUAD *pColorTable-颜色表指针
函数返回值：
    0为失败，1为成功
****************************************************************/
int SaveBmp(char *bmpName, unsigned char *imgBuf, int width, int height, 
             int biBitCount, RGBQUAD *pColorTable)
{
	FILE *fp;
    int colorTablesize=0; /*颜色表大小，以字节为单位，灰度图像颜色表为1024字节，彩色图像颜色表大小为0*/
    int lineByte;
   
	if(!imgBuf) return 0; /*如果位图数据指针为0，则没有数据传入，函数返回*/
    if(biBitCount==8)   colorTablesize=1024;
    lineByte=(width * biBitCount/8+3)/4*4;  /*待存储图像数据每行字节数为4的倍数*/   
    fp=fopen(bmpName,"wb");  /*以二进制写的方式打开文件*/
    if(fp==NULL) return 0;  
	/*填写文件头信息*/ 
    fileHead.bfSize= sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+colorTablesize+lineByte*height;/*bfSize是图像文件4个组成部分之和*/ 	
    if(pColorTable) /* 计算灰度图象数据相对文件头的偏移量*/
		fileHead.bfOffBits=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER) +sizeof(RGBQUAD)*256; 
    fwrite(&fileHead, sizeof(BITMAPFILEHEADER),1, fp);/*写文件头到文件  */
	/*填写位图信息头信息*/
	infoHead.biWidth=width;
	infoHead.biHeight=height;
	infoHead.biBitCount=biBitCount;
	infoHead.biSizeImage=lineByte*height;     
    fwrite(&infoHead, sizeof(BITMAPINFOHEADER),1, fp);/*写位图信息头进内存 */
    if(biBitCount==8) /*如果灰度图像，有颜色表，写入文件*/ 
        fwrite(pColorTable, sizeof(RGBQUAD),256, fp);
    fwrite(imgBuf, height*lineByte, 1, fp); /*写位图数据进文件*/
    fclose(fp);
    return 1;
}