/************************************************************************************
图像的读入显示
************************************************************************************/
#include "cv.h"
#include "highgui.h"
#include <stdio.h>

int main(int argc,char *argv[])
{	
	IplImage *img;
	
  	img = cvLoadImage(argv[1],-1);   /* 加载图像, 默认原通道数 */
	if(!img)		/* 如果加载失败 */
	{
		printf("error: 导入图片出错.\n"); 
		return -1; 
	} 
	cvNamedWindow("pic",CV_WINDOW_AUTOSIZE); /* 创建一个窗口 */
	cvMoveWindow("pic",800,100);		    /* 定位一个窗口 */ 
	cvShowImage("pic",img);			       /* 在创建的窗口中显示一幅图片 */
	cvWaitKey(0);					    /* 等待用户输入，否则一闪而过 , 看不到图片 */
	cvReleaseImage(&img);		      	/* 释放 */ 
	return 0; 
} 
