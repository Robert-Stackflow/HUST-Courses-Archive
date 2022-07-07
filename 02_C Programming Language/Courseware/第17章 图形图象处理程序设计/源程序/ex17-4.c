/************************************************************************************
ͼ��Ķ�����ʾ
************************************************************************************/
#include "cv.h"
#include "highgui.h"
#include <stdio.h>

int main(int argc,char *argv[])
{	
	IplImage *img;
	
  	img = cvLoadImage(argv[1],-1);   /* ����ͼ��, Ĭ��ԭͨ���� */
	if(!img)		/* �������ʧ�� */
	{
		printf("error: ����ͼƬ����.\n"); 
		return -1; 
	} 
	cvNamedWindow("pic",CV_WINDOW_AUTOSIZE); /* ����һ������ */
	cvMoveWindow("pic",800,100);		    /* ��λһ������ */ 
	cvShowImage("pic",img);			       /* �ڴ����Ĵ�������ʾһ��ͼƬ */
	cvWaitKey(0);					    /* �ȴ��û����룬����һ������ , ������ͼƬ */
	cvReleaseImage(&img);		      	/* �ͷ� */ 
	return 0; 
} 
