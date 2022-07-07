#include <windows.h>     
#include <stdio.h>     
#include <stdlib.h>     
#include <malloc.h>  

int gbrToGrey(char *OriginalBMP,char *ResultBMP);
int ReadBmp(const char *bmpName);
int SaveBmp(char *bmpName, unsigned char *imgBuf, int width, int height, 
             int biBitCount, RGBQUAD *pColorTable);

BITMAPFILEHEADER fileHead;      /* �ļ���Ϣͷ*/
BITMAPINFOHEADER infoHead;      /* λͼ��Ϣͷ*/
RGBQUAD    pColorTable[256];    /* ��ɫ�� */
unsigned char *pBmpBuf;     /* 24λͼ�����ݵ�ָ��*/
int        bmpWidth;       /*ͼ��Ŀ�*/
int        bmpHeight;      /*ͼ��ĸ�*/
int        lineByte;      /*ÿ�е��ֽ��� */
int        biBitCount;     /*ͼ�����ͣ�ÿ����λ��*/

int main()  
{  
    gbrToGrey("c.bmp","c_grey.bmp"); 
	return 0;  
} 

/****************************************************************
�������ƣ�gbrToGrey
�������ܣ�
      ʵ�ֽ�24λBMPͼ������ת����8λBMPͼ������
����������
          char *OriginalBMP�� 24λԭͼ���ļ���
		  char *ResultBMP :   ת�����8λͼ���ļ���
��������ֵ��0Ϊ�ɹ���-1Ϊʧ��
****************************************************************/
int gbrToGrey(char *OriginalBMP,char *ResultBMP)  
{  
	 unsigned char *pNewBmpBuf;  /* ת����8λͼ�����ݵ�ָ��*/
	 unsigned char b,g,r,grey;   /* ��ɫ�����ͻҶȼ� */ 
	 int nWidth;   /* ͼ���ʵ�ʿ�� */   
	 int i,j;  
 	 ReadBmp(OriginalBMP);
	 if(infoHead.biBitCount != 24 )  /* ����24λͼ�� */
	 {  
		puts("This bmp file is not a 24bit."); 
		return -1;
	 } 
     nWidth=(bmpWidth+3)/4*4;     /* ͼ���ʵ�ʿ�ȣ�������4�ı����� */         
     pNewBmpBuf=(unsigned char *)calloc(nWidth * bmpHeight,sizeof(unsigned char));
	 for(i=0;i<bmpHeight;i++)  
	 {
         for(j=0;j<bmpWidth;j++)  
		 {  
                 b=  pBmpBuf[i*lineByte+j*3];  
	             g = pBmpBuf[i*lineByte+j*3+1]; 
			     r = pBmpBuf[i*lineByte+j*3+2];
			     grey = ( 77 * r + 151 * g + 28 * b) >> 8; /* ���ɫת�ҶȺ����㷨 */  
                 pNewBmpBuf[i*nWidth+j]=grey; 
         }  
	 }
	 for(i=0;i<256;i++)    /*  ���õ�ɫ��  */  
     { 
		 pColorTable[i].rgbBlue=i;  
         pColorTable[i].rgbGreen=i;  
         pColorTable[i].rgbRed=i;  
         pColorTable[i].rgbReserved=0;  
     }
	 SaveBmp(ResultBMP,pNewBmpBuf,bmpWidth,bmpHeight,8,pColorTable); /* ����8λ�Ҷ�ͼ�� */
	 return 0; 
} 

/****************************************************************************
�������ƣ�ReadBmp
���������������ļ������ƺ�·�� ����ͼ���λͼ���ݣ����ߣ���ÿ�����ص�λ�����ڴ棬������ȫ�ֱ�����
����������const char *bmpName ����bmp��ʽ�ļ������Ƽ�·��
��������ֵ��0Ϊʧ��; 1Ϊ�ɹ�

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
	lineByte = (bmpWidth *biBitCount/8+3)/4*4;    /*����ͼ��ÿ��������ռ���ֽ���*/
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
�������ƣ�SaveBmp
�������ܣ�
       ����һ��ͼ��λͼ(�Ҷ�ͼ������ɫͼ�����ݡ����ߡ���ɫ��ָ�뼰ÿ������ռ��λ������Ϣ��
       ����д��ָ���ļ���
����������
    char *bmpName-�ļ����ּ�·��
    unsigned char *imgBuf-�����̵�λͼ����
    int width-������Ϊ��λ������λͼ�Ŀ�
    int  height-������Ϊ��λ������λͼ��
    int biBitCount-ÿ������ռλ��
    RGBQUAD *pColorTable-��ɫ��ָ��
��������ֵ��
    0Ϊʧ�ܣ�1Ϊ�ɹ�
****************************************************************/
int SaveBmp(char *bmpName, unsigned char *imgBuf, int width, int height, 
             int biBitCount, RGBQUAD *pColorTable)
{
	FILE *fp;
    int colorTablesize=0; /*��ɫ���С�����ֽ�Ϊ��λ���Ҷ�ͼ����ɫ��Ϊ1024�ֽڣ���ɫͼ����ɫ���СΪ0*/
    int lineByte;
   
	if(!imgBuf) return 0; /*���λͼ����ָ��Ϊ0����û�����ݴ��룬��������*/
    if(biBitCount==8)   colorTablesize=1024;
    lineByte=(width * biBitCount/8+3)/4*4;  /*���洢ͼ������ÿ���ֽ���Ϊ4�ı���*/   
    fp=fopen(bmpName,"wb");  /*�Զ�����д�ķ�ʽ���ļ�*/
    if(fp==NULL) return 0;  
	/*��д�ļ�ͷ��Ϣ*/ 
    fileHead.bfSize= sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+colorTablesize+lineByte*height;/*bfSize��ͼ���ļ�4����ɲ���֮��*/ 	
    if(pColorTable) /* ����Ҷ�ͼ����������ļ�ͷ��ƫ����*/
		fileHead.bfOffBits=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER) +sizeof(RGBQUAD)*256; 
    fwrite(&fileHead, sizeof(BITMAPFILEHEADER),1, fp);/*д�ļ�ͷ���ļ�  */
	/*��дλͼ��Ϣͷ��Ϣ*/
	infoHead.biWidth=width;
	infoHead.biHeight=height;
	infoHead.biBitCount=biBitCount;
	infoHead.biSizeImage=lineByte*height;     
    fwrite(&infoHead, sizeof(BITMAPINFOHEADER),1, fp);/*дλͼ��Ϣͷ���ڴ� */
    if(biBitCount==8) /*����Ҷ�ͼ������ɫ��д���ļ�*/ 
        fwrite(pColorTable, sizeof(RGBQUAD),256, fp);
    fwrite(imgBuf, height*lineByte, 1, fp); /*дλͼ���ݽ��ļ�*/
    fclose(fp);
    return 1;
}