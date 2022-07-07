/**********************************************************
  ʵ��24λbmpͼƬ�Ŵ���С��
***********************************************************/
#include <windows.h>
#include <stdio.h>

#define FXZOOMRATIO 2        /* x��Ŵ���*/
#define FYZOOMRATIO 0.5     /* y��Ŵ���*/

int ReadBmp(const char *bmpName);
int SaveBmp(char *bmpName, unsigned char *imgBuf, int width, int height, 
             int biBitCount, RGBQUAD *pColorTable);
int ZoomBmp(void);
    
BITMAPFILEHEADER fileHead;  /* �ļ���Ϣͷ*/
BITMAPINFOHEADER infoHead;  /* λͼ��Ϣͷ*/
RGBQUAD    *pColorTable;    /*��ɫ��ָ��*/
unsigned char *pBmpBuf;     /*ָ��Դͼ���ָ��*/
unsigned char *pNewBmpBuf;  /*ָ������ͼ���ָ��*/
int        bmpWidth;       /*Դͼ��Ŀ�*/
int        bmpHeight;      /*Դͼ��ĸ�*/
int        lineByte;       /*Դͼ��ÿ���ֽ��� */
int        biBitCount;     /*ͼ�����ͣ�ÿ����λ��*/
long       newBmpWidth;    /*���ź�ͼ��Ŀ�*/
long       newBmpHeight;   /*���ź�ͼ��ĸ�*/
long       newLineByte;    /*���ź�ͼ��ÿ�е��ֽ���*/
/***********************************************************************
 �������ƣ�main
 ����: ��
 ����ֵ: int
 ������ͼ��仯�ķ���
***************************************************************************/
int main()
{
	char str1[80]; 
	char str2[80];
	printf("����bmp�ļ����ƺ�·��:");
	gets(str1);
	printf("����bmp�ļ���������ƺ�·��:");
	gets(str2); 
	ReadBmp(str1);
	ZoomBmp();
	SaveBmp(str2,pNewBmpBuf,newBmpWidth,newBmpHeight,24,NULL);
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
		pColorTable = (RGBQUAD *)malloc(sizeof(RGBQUAD)*256);
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
    fwrite(&fileHead, sizeof(BITMAPFILEHEADER),1, fp);/*д�ļ�ͷ���ļ�  */
	/*��д��Ϣͷ��Ϣ*/
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

/****************************************************************************
�������ƣ� ZoomBmp
���������� ����ͼƬ�仯����ϵ������FXZOOMRATIO��FYZOOMRATIO ʵ��ͼƬ�Ŵ���С,��֧��24λ��ʽ��
���������� const char* szSrcBmp ԭbmpͼƬ�����ƺ�·��
            const char* szDstBmp �仯�󱣴�bmpͼƬ����ļ�·��
��������ֵ:0Ϊʧ�� 1Ϊ�ɹ�
***************************************************************************/
int ZoomBmp()
{
	long i0,j0;        /*������Դͼ�е�����*/
	long i,j;          /*���������ź�ͼ���е�����*/
	long k;

	newBmpWidth = (long) ((bmpWidth * FXZOOMRATIO) +0.5);
	newBmpHeight = (long) (bmpHeight * FYZOOMRATIO +0.5);
	newLineByte = (newBmpWidth * biBitCount+31)/32*4;
	pNewBmpBuf = (unsigned char *)malloc(sizeof(unsigned char)*newLineByte * newBmpHeight);

	if(biBitCount == 24)/* ��24λͼ�� */
	{
		 for(i = 0;i < newBmpHeight;i++)/*���ͼ��ÿ�н��в���*/
		 {
			  for(j = 0; j<newBmpWidth;j++)/* ���ͼ��ÿ�н��в��� */
					for(k=0;k<3;k++) 
					{   
						i0 = (long)(i/FYZOOMRATIO+0.5); /*�����������Դͼ�е����꣬�˴�ֱ�Ӽ�0.5������ǿ������ת��ʱ���������룬����ֱ�ӽ�ȥС�����֡�*/
						j0 = (long)(j/FXZOOMRATIO+0.5);
						if((j0>=0)&&(j0<bmpWidth)&&(i0>=0)&&(i0<bmpHeight))/* ��Դͼ��Χ�� */
						{
							*(pNewBmpBuf+i*newLineByte+j*3+k) = *(pBmpBuf+i0*lineByte+j0*3+k);
						}
						else /* ����Դͼ��Χ�� */
						{
							 *(pNewBmpBuf+i*newLineByte+j*3+k)=255;
						}
    
					}
		}
		return 1;
	}
	else 
	{
		printf("����24λbmpͼƬ.\n");
	    return 0;
	}
}
