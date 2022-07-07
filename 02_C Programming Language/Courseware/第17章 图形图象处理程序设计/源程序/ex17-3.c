/**********************************************************
  实现24位bmp图片放大缩小。
***********************************************************/
#include <windows.h>
#include <stdio.h>

#define FXZOOMRATIO 2        /* x轴放大倍数*/
#define FYZOOMRATIO 0.5     /* y轴放大倍数*/

int ReadBmp(const char *bmpName);
int SaveBmp(char *bmpName, unsigned char *imgBuf, int width, int height, 
             int biBitCount, RGBQUAD *pColorTable);
int ZoomBmp(void);
    
BITMAPFILEHEADER fileHead;  /* 文件信息头*/
BITMAPINFOHEADER infoHead;  /* 位图信息头*/
RGBQUAD    *pColorTable;    /*颜色表指针*/
unsigned char *pBmpBuf;     /*指向源图像的指针*/
unsigned char *pNewBmpBuf;  /*指向缩放图像的指针*/
int        bmpWidth;       /*源图像的宽*/
int        bmpHeight;      /*源图像的高*/
int        lineByte;       /*源图像每行字节数 */
int        biBitCount;     /*图像类型，每像素位数*/
long       newBmpWidth;    /*缩放后图像的宽*/
long       newBmpHeight;   /*缩放后图像的高*/
long       newLineByte;    /*缩放后图像每行的字节数*/
/***********************************************************************
 函数名称：main
 参数: 空
 返回值: int
 描述：图像变化的访问
***************************************************************************/
int main()
{
	char str1[80]; 
	char str2[80];
	printf("输入bmp文件名称和路径:");
	gets(str1);
	printf("输入bmp文件保存的名称和路径:");
	gets(str2); 
	ReadBmp(str1);
	ZoomBmp();
	SaveBmp(str2,pNewBmpBuf,newBmpWidth,newBmpHeight,24,NULL);
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
		pColorTable = (RGBQUAD *)malloc(sizeof(RGBQUAD)*256);
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
    fwrite(&fileHead, sizeof(BITMAPFILEHEADER),1, fp);/*写文件头到文件  */
	/*填写信息头信息*/
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

/****************************************************************************
函数名称： ZoomBmp
函数描述： 传入图片变化比例系数参数FXZOOMRATIO和FYZOOMRATIO 实现图片放大缩小,仅支持24位格式。
函数参数： const char* szSrcBmp 原bmp图片的名称和路径
            const char* szDstBmp 变化后保存bmp图片后的文件路径
函数返回值:0为失败 1为成功
***************************************************************************/
int ZoomBmp()
{
	long i0,j0;        /*象素在源图中的坐标*/
	long i,j;          /*象素在缩放后图像中的坐标*/
	long k;

	newBmpWidth = (long) ((bmpWidth * FXZOOMRATIO) +0.5);
	newBmpHeight = (long) (bmpHeight * FYZOOMRATIO +0.5);
	newLineByte = (newBmpWidth * biBitCount+31)/32*4;
	pNewBmpBuf = (unsigned char *)malloc(sizeof(unsigned char)*newLineByte * newBmpHeight);

	if(biBitCount == 24)/* 是24位图像 */
	{
		 for(i = 0;i < newBmpHeight;i++)/*针对图像每行进行操作*/
		 {
			  for(j = 0; j<newBmpWidth;j++)/* 针对图像每列进行操作 */
					for(k=0;k<3;k++) 
					{   
						i0 = (long)(i/FYZOOMRATIO+0.5); /*计算该象素在源图中的坐标，此处直接加0.5是由于强制类型转换时不四舍五入，而是直接截去小数部分。*/
						j0 = (long)(j/FXZOOMRATIO+0.5);
						if((j0>=0)&&(j0<bmpWidth)&&(i0>=0)&&(i0<bmpHeight))/* 在源图范围内 */
						{
							*(pNewBmpBuf+i*newLineByte+j*3+k) = *(pBmpBuf+i0*lineByte+j0*3+k);
						}
						else /* 不在源图范围内 */
						{
							 *(pNewBmpBuf+i*newLineByte+j*3+k)=255;
						}
    
					}
		}
		return 1;
	}
	else 
	{
		printf("不是24位bmp图片.\n");
	    return 0;
	}
}
