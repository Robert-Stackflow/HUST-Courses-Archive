/* 电子钟的设计  */   
#include <cxcore.h>   
#include <cv.h>   
#include <highgui.h>   
#include <time.h>  
#include <math.h>
#include <windows.h> 

#define  PI  3.1415926
#define  X0  300
#define  Y0  240        /* 时钟的中心点指标 */
#define  R   200        /* 时钟的半径 */
#define  x(len,time,angle)  x=(len)*cos((time)*(angle)*PI/180-PI/2)+X0
#define  y(len,time,angle)  y=(len)*sin((time)*(angle)*PI/180-PI/2)+Y0
#define  d(len,time,angle)  {x(len,time,angle);y(len,time,angle);cvLine(img,cvPoint(X0,Y0),cvPoint(x,y),colour,1,8,0);}

void init(IplImage *img);

int main(void)
{
	   IplImage *img,*img0;
	   CvScalar colour;
	   int x,y,flag=0;
       unsigned char h,m,s,i;
       time_t t;
	   struct tm *local;
       CvSize Size=cvSize(600,480);
	   img=cvCreateImage(Size,IPL_DEPTH_8U,3); /*分配内存给一幅新图像*/
       init(img);
       
       t=time(NULL);                       /* 获得系统时间 */
       local=localtime(&t);
       h=local->tm_hour; 
       m=local->tm_min;
       s=local->tm_sec;

	   colour=cvScalar(200,200,200,0);
	   i=local->tm_min/12;
	   d(130,h+i/5.0,30);  /*   时指针  */
	  
	   colour=cvScalar(0,255,255,0);
	   d(160,m,6);  /*  分指针  */
       
	   colour=cvScalar(0,255,0,0);
	   d(190,s,6);  /*  秒指针  */

	  
	   cvNamedWindow("clock",1);   /* 创建一个新窗口 */
	   cvShowImage("clock",img);  /* 显示图像  */
       
	   while(cvWaitKey(100)==-1)  /*  按任意键结束循环  */ 
	   { 
		   while (local->tm_sec==s)  
		   {   time(&t);
		       local=localtime(&t);
		   } 
		   Beep(500,10);              /* 发声 */
		   img0 = cvCloneImage(img);  /* 复制图像img给img0 */
           cvZero(img);               /* 图像img数据清零  */  		   
           d(190,s,6);                /* 秒指针转动 */
           s=local->tm_sec;
           d(190,s,6); 
           cvXor(img0, img, img, NULL);
		   if (local->tm_min!=m)     /* 分指针转动 */          
		   {                      
			   img0 = cvCloneImage(img);   
               cvZero(img);
               colour=cvScalar(0,255,255,0);
               d(160,m,6);                     
               m=local->tm_min;
               d(160,m,6); 
               cvXor(img0, img, img, NULL);
			   flag=1;
			   colour=cvScalar(0,255,0,0);  
		   }
		   if (flag&&local->tm_min%12==0)   /* 时指针转动 */
		   {                         
			   img0 = cvCloneImage(img);
               cvZero(img);
               colour=cvScalar(200,200,200,0);
			   d(130,h+i/5.0,30);                     
               h=local->tm_hour;
			   m=local->tm_min;
			   i=m/12;
               d(130,h+i/5.0,30); 
               cvXor(img0, img, img, NULL);
			   flag=0;
		   }
		   cvShowImage("clock",img);  
	   }
	   cvReleaseImage(&img);   
	   cvReleaseImage(&img0);   
	   return 0;
}

/***********************************************************************
 函数名称：init
 函数功能：绘制钟面
 参数: img表示指向所绘图形数据的指针
 返回值: 无
***************************************************************************/
void init(IplImage *img) 
{
     
 	 CvFont  font;
	 int i,l,x1,x2,y1,y2;
     char *n[12]={ "3","4","5","6","7","8","9","10","11","12","1","2"};   /* 时钟上显示的12个数字 */
 
	 cvCircle(img,cvPoint(X0,Y0),R,cvScalar(0,255,0,0),1,8,0); 
     cvCircle(img,cvPoint(X0,Y0),R+5,cvScalar(0,255,255,0),1,8,0); 
     cvCircle(img,cvPoint(X0,Y0),5,cvScalar(0,0,255,0),1,8,0); 
    
     /* font--表示被初始化的字体结构体。
	    font_face--字体名称标识符，目前仅支持CV_FONT_HERSHEY_SIMPLEX等少数几种字体。 
	    hscale--表示字体宽度的放大系数，例如0.5f表示宽度为原来的一半，
	    shear--字体豹裁瘦的斜率，1表示字体倾斜45度。
	    thickness--表示字 体笔划的粗细程度。
	    line_type-- 表示字体笔划的类型，具体参见cvLine。
	 */
      cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX,0.5f,0.5f,0,1,8);

     for(i=0;i<60;i++) 
	 {
		 
		 if(i%5==0) l=15;
		 else l=8;
         x1=(int)(R*cos(i*6*PI/180)+X0);       /* 计算适当的位置 */
         y1=(int)(R*sin(i*6*PI/180)+Y0);
         x2=(int)((R-l)*cos(i*6*PI/180)+X0);
         y2=(int)((R-l)*sin(i*6*PI/180)+Y0);
         cvLine(img,cvPoint(x1,y1),cvPoint(x2,y2),cvScalar(0,0,255,0),1,8,0);
         if(i%5==0) 
		 {
			 x1=(int)((R-25)*cos(i*6*PI/180)+X0);
             y1=(int)((R-25)*sin(i*6*PI/180)+Y0);
             /*
	         img--表示图像。
	         text--这里要严格的ASCII字符，不能接受像GB2312等双字节编码。
	         org--表示第1个字符左下角的坐标。
	         font--表示字体结构体。 
	         color--表示文本的字体颜色。
	         */
             cvPutText(img,n[i/5],cvPoint(x1-5,y1+5),&font,cvScalar(0,0,255,0)); 
       }
	 }
}
