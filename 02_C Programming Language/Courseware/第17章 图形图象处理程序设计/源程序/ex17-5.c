/************************************************************************************
�������̡����ͻ������¼�
************************************************************************************/
#include "cv.h"
#include "highgui.h"
#include <stdio.h>

void mouseHandler( int event, int x, int y, int flags, void* zhang);
void trackbarHandler( int pos);
void InvertColors(IplImage * img);

CvScalar color; /*  val[0]=Bֵ,val[1]=Gֵ,val[2]=Rֵ  */
IplImage* img = 0;  /* ͼ��ָ�� */
int posR,posG,posB;
CvPoint prev_pt;

int main(void)
{	
	printf( "Hot keys: \n"
            "\tESC - quit the program\n"
            "\tI - Invert Colors\n");        /* ��ʾ�˵��� */       
	color=CV_RGB(255,255,0);   /*  CV_RGB��OPENCV�е�һ���꣬���ڴ���һ��ɫ��ֵ��R=255,G=255,B=0 */           
	posR=posG=255; posB=0;    /*  ����ɫ��ֵ��ʼ������λ�ñ��� */       
	img = cvCreateImage(cvSize(400,400), 8,3 );       /* �����ڴ��һ����ͼ�� */
	cvNamedWindow( "image", 1 );    /* ����һ������ */
	cvMoveWindow("image",700,100);		/* ��λһ������ */
    cvShowImage( "image", img );      /* �ڴ����Ĵ�������ʾһ��ͼƬ */
    cvSetMouseCallback( "image", mouseHandler, NULL);       /* ��������¼���ÿ������¼�����ʱ�����ú��� mouseHandler */
	cvCreateTrackbar("R","image",&posR,255,trackbarHandler);  /* �ڴ���image����һ������ΪB�Ļ�����(trackbar) ,  
	                                                             �������Զ��ģ���ÿ�λ���λ�øı�ʱ���Զ����ú���trackbarHandler */
    cvCreateTrackbar("G","image",&posG,255,trackbarHandler);  /* ����������G */
    cvCreateTrackbar("B","image",&posB,255,trackbarHandler);  /* ����������R */
    
	for(;;)  /* ѭ���ȴ��������� */
    {
        int key = cvWaitKey(0);  /* �ȴ����� */
        int exit=0;
        switch((char)key)   /* ��Ӧ�˵�ѡ�� */

        {
		   case '\x1b':     /* ������Esc���˳�����  */
		     	printf("Exiting...\n");
			    exit=1;
				break;
		   case 'I':   /* ������ I��ͼ��ɫ  */
			    InvertColors(img);
				break;
		}
        if(exit) break;
	}  
    cvReleaseImage( &img );      /* �ͷ� */
    cvDestroyWindow("image");
    return 0;
}
/************************************************************************************
�������ƣ� trackbarHandler
�������ܣ� ��Ӧ�������¼���������λ�ñ��ı�ʱ�ļ�������������3����ɫ�����λ������colorֵ��
���������� int pos�������λ��
��������ֵ���ޡ�
************************************************************************************/
void trackbarHandler(int pos)
{
 	color.val[0]=posB;
	color.val[1]=posG;
	color.val[2]=posR;
}
/************************************************************************************
�������ƣ� mouseHandler
�������ܣ� ʵ����걻����ļ�������������ƶ��Ķ����������꿪ʼ���ߡ�  
����������
        int event�������ķ�ʽ,��갴�¡��ͷš��ƶ��ȣ���ֵΪ CV_EVENT_* ֮һ��
		int x, int y �������ͼ������ϵ����������Ͻǵ��������ꡣ
		int flags�� ���������������ctrl���ȣ���CV_EVENT_FLAG_* ����ϡ�
        void *param�����û�����Ĵ��ݵ�cvSetMouseCallback�������õĲ���
��������ֵ���ޡ�
************************************************************************************/
void mouseHandler( int event, int x, int y, int flags, void *param)
{
    switch(event)
	{
		case CV_EVENT_LBUTTONDOWN:    /* ��������� */
			prev_pt = cvPoint(x,y);  /* ��ʼ���ߵ�������� */
			break;
        case CV_EVENT_MOUSEMOVE:     /* ����ƶ� */
			if(flags & CV_EVENT_FLAG_LBUTTON)  /* ��ס������ */
			{
				CvPoint pt = cvPoint(x,y);
				cvLine( img, prev_pt, pt, color, 1, 8, 0 );   /* ���� */
				prev_pt = pt;
                cvShowImage( "image", img );
			}
			break;
        case CV_EVENT_LBUTTONUP:    /* �ͷ������� */
            prev_pt = cvPoint(-1,-1);
	}
}
/************************************************************************************
�������ƣ� InvertColors
�������ܣ� ��ͼ����ɫ��ת�� 
����������IplImage * img ��ָ�����תͼ���ָ�롣
��������ֵ���ޡ�
************************************************************************************/
void InvertColors( IplImage * img)
{
    int i,j,k;
    CvScalar s;
    int height     = img->height;
    int width      = img->width;
    int channel    = img->nChannels;  
    for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			s=cvGet2D(img,i,j);  /*  ��ȡimgͼ��������Ϊ��i,j�������ص��ֵ  */
			for(k=0;k<channel;k++)
				s.val[k]=255-s.val[k];
			cvSet2D(img,i,j,s);  /* Ϊimgͼ��������Ϊ��i,j�������ص㸳��ֵs */
		}
	}
	cvShowImage( "image", img );
}