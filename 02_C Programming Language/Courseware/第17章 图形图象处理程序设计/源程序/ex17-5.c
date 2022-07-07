/************************************************************************************
监听键盘、鼠标和滑动条事件
************************************************************************************/
#include "cv.h"
#include "highgui.h"
#include <stdio.h>

void mouseHandler( int event, int x, int y, int flags, void* zhang);
void trackbarHandler( int pos);
void InvertColors(IplImage * img);

CvScalar color; /*  val[0]=B值,val[1]=G值,val[2]=R值  */
IplImage* img = 0;  /* 图像指针 */
int posR,posG,posB;
CvPoint prev_pt;

int main(void)
{	
	printf( "Hot keys: \n"
            "\tESC - quit the program\n"
            "\tI - Invert Colors\n");        /* 显示菜单项 */       
	color=CV_RGB(255,255,0);   /*  CV_RGB是OPENCV中的一个宏，用于创建一个色彩值：R=255,G=255,B=0 */           
	posR=posG=255; posB=0;    /*  根据色彩值初始化滑块位置变量 */       
	img = cvCreateImage(cvSize(400,400), 8,3 );       /* 分配内存给一幅新图像 */
	cvNamedWindow( "image", 1 );    /* 创建一个窗口 */
	cvMoveWindow("image",700,100);		/* 定位一个窗口 */
    cvShowImage( "image", img );      /* 在创建的窗口中显示一幅图片 */
    cvSetMouseCallback( "image", mouseHandler, NULL);       /* 监听鼠标事件，每次鼠标事件发生时，调用函数 mouseHandler */
	cvCreateTrackbar("R","image",&posR,255,trackbarHandler);  /* 在窗口image创建一个名称为B的滑动条(trackbar) ,  
	                                                             监听是自动的，即每次滑块位置改变时，自动调用函数trackbarHandler */
    cvCreateTrackbar("G","image",&posG,255,trackbarHandler);  /* 创建滑动条G */
    cvCreateTrackbar("B","image",&posB,255,trackbarHandler);  /* 创建滑动条R */
    
	for(;;)  /* 循环等待键盘输入 */
    {
        int key = cvWaitKey(0);  /* 等待输入 */
        int exit=0;
        switch((char)key)   /* 响应菜单选项 */

        {
		   case '\x1b':     /* 如输入Esc，退出程序  */
		     	printf("Exiting...\n");
			    exit=1;
				break;
		   case 'I':   /* 如输入 I，图像反色  */
			    InvertColors(img);
				break;
		}
        if(exit) break;
	}  
    cvReleaseImage( &img );      /* 释放 */
    cvDestroyWindow("image");
    return 0;
}
/************************************************************************************
函数名称： trackbarHandler
函数功能： 响应滑动条事件，即滑块位置被改变时的监听动作，根据3个颜色滑块的位置设置color值。
函数参数： int pos：滑块的位置
函数返回值：无。
************************************************************************************/
void trackbarHandler(int pos)
{
 	color.val[0]=posB;
	color.val[1]=posG;
	color.val[2]=posR;
}
/************************************************************************************
函数名称： mouseHandler
函数功能： 实现鼠标被点击的监听动作和鼠标移动的动作：点击鼠标开始画线。  
函数参数：
        int event：按键的方式,鼠标按下、释放、移动等，其值为 CV_EVENT_* 之一。
		int x, int y ：鼠标在图像坐标系中相对于左上角的像素坐标。
		int flags： 所按键，如左键、ctrl键等，是CV_EVENT_FLAG_* 的组合。
        void *param：是用户定义的传递到cvSetMouseCallback函数调用的参数
函数返回值：无。
************************************************************************************/
void mouseHandler( int event, int x, int y, int flags, void *param)
{
    switch(event)
	{
		case CV_EVENT_LBUTTONDOWN:    /* 点击鼠标左键 */
			prev_pt = cvPoint(x,y);  /* 开始画线的起点坐标 */
			break;
        case CV_EVENT_MOUSEMOVE:     /* 鼠标移动 */
			if(flags & CV_EVENT_FLAG_LBUTTON)  /* 按住鼠标左键 */
			{
				CvPoint pt = cvPoint(x,y);
				cvLine( img, prev_pt, pt, color, 1, 8, 0 );   /* 画线 */
				prev_pt = pt;
                cvShowImage( "image", img );
			}
			break;
        case CV_EVENT_LBUTTONUP:    /* 释放鼠标左键 */
            prev_pt = cvPoint(-1,-1);
	}
}
/************************************************************************************
函数名称： InvertColors
函数功能： 将图像颜色反转。 
函数参数：IplImage * img ：指向待反转图像的指针。
函数返回值：无。
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
			s=cvGet2D(img,i,j);  /*  获取img图像中坐标为（i,j）的像素点的值  */
			for(k=0;k<channel;k++)
				s.val[k]=255-s.val[k];
			cvSet2D(img,i,j,s);  /* 为img图像中坐标为（i,j）的像素点赋予值s */
		}
	}
	cvShowImage( "image", img );
}