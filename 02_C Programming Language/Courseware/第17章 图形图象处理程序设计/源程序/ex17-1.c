/*  ��ȡָ��ͼ�񣨻Ҷ�ͼ�����ɫͼ����λͼ��Ϣͷ����ɫ���λͼ�������ݡ����ͼ��Ŀ�Ⱥ͸߶���Ϣ��*/
#include<windows.h>
#include<stdio.h>
#include<stdlib.h>

int ReadBmp(const char *bmpName); /* ����ԭ�� */

BITMAPFILEHEADER fileHead; /* �ļ���Ϣͷ    */
BITMAPINFOHEADER infoHead; /* λͼ��Ϣͷ    */
RGBQUAD    *pColorTable;   /* ��ɫ��ָ��    */
unsigned char *pBmpBuf;    /* ͼ�����ݵ�ָ��*/
int bmpWidth;              /* ͼ��Ŀ�      */
int bmpHeight;             /* ͼ��ĸ�      */
int biBitCount;            /* ÿ����λ��    */
int lineByte;              /*ÿ�е��ֽ��� */

int main(int argc,char *argv[])
{
	if(argc<2)  /* δָ��bmp�ļ��� */
	{
		printf("Command line error.\n");
		return -1;
	}
    if(ReadBmp(argv[1]))  /* ���ļ��ɹ� */
	{
		printf("%s�Ŀ�Ⱥ͸߶�Ϊ:%d��%d\n",argv[1],bmpWidth,bmpHeight);
	}
	return 0;
}

/****************************************************************
�������ƣ�ReadBmp
�������ܣ�
      ������ͼ��(�Ҷ�ͼ������ɫͼ�񣩵�λͼ���ݡ����ߡ���ɫ��ÿ����λ�������ݽ��ڴ棬
	  �������Ӧ��ȫ�ֱ�����
����������
          char *bmpName: �ļ����ּ�·��
��������ֵ��0Ϊʧ�ܣ�1Ϊ�ɹ�
****************************************************************/
int ReadBmp(const char *bmpName)
{
    FILE *fp=fopen(bmpName,"rb");/* �����ƶ���ʽ��ָ����ͼ���ļ� */
    if(fp==NULL) return 0;

    fread(&fileHead,sizeof(BITMAPFILEHEADER),1,fp); /* ��ȡ�ļ���Ϣͷ���ڴ棬����ڱ���fileHead��*/
    fread(&infoHead,sizeof(BITMAPINFOHEADER),1,fp);/* ��ȡλͼ��Ϣͷ���ڴ棬����ڱ���head�� */

	bmpWidth = infoHead.biWidth;	/* ��ȡͼ����ߡ�ÿ������ռλ������Ϣ */
    bmpHeight = infoHead.biHeight;
    biBitCount = infoHead.biBitCount;

	lineByte=(bmpWidth * biBitCount/8+3)/4*4; /* ����ͼ��ÿ��������ռ���ֽ�����������4�ı����� */

	if(biBitCount==8) /* �Ҷ�ͼ������ɫ������ɫ�����Ϊ256 */
	{

        pColorTable=(RGBQUAD *)malloc(sizeof(RGBQUAD)*256);  /* ������ɫ������Ҫ�Ŀռ� */
        fread(pColorTable,sizeof(RGBQUAD),256,fp); /* ����ɫ����ڴ� */
    }

    pBmpBuf=(unsigned char *)malloc(sizeof(unsigned char)*lineByte * bmpHeight);  /* ����λͼ��������Ҫ�Ŀռ� */
    fread(pBmpBuf,1,lineByte * bmpHeight,fp);   /* ��λͼ���ݽ��ڴ� */

    fclose(fp);
    return 1;
}
