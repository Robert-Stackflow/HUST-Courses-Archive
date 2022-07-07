/* �����ӵ����  */   
#include <cxcore.h>   
#include <cv.h>   
#include <highgui.h>   
#include <time.h>  
#include <math.h>
#include <windows.h> 

#define  PI  3.1415926
#define  X0  300
#define  Y0  240        /* ʱ�ӵ����ĵ�ָ�� */
#define  R   200        /* ʱ�ӵİ뾶 */
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
	   img=cvCreateImage(Size,IPL_DEPTH_8U,3); /*�����ڴ��һ����ͼ��*/
       init(img);
       
       t=time(NULL);                       /* ���ϵͳʱ�� */
       local=localtime(&t);
       h=local->tm_hour; 
       m=local->tm_min;
       s=local->tm_sec;

	   colour=cvScalar(200,200,200,0);
	   i=local->tm_min/12;
	   d(130,h+i/5.0,30);  /*   ʱָ��  */
	  
	   colour=cvScalar(0,255,255,0);
	   d(160,m,6);  /*  ��ָ��  */
       
	   colour=cvScalar(0,255,0,0);
	   d(190,s,6);  /*  ��ָ��  */

	  
	   cvNamedWindow("clock",1);   /* ����һ���´��� */
	   cvShowImage("clock",img);  /* ��ʾͼ��  */
       
	   while(cvWaitKey(100)==-1)  /*  �����������ѭ��  */ 
	   { 
		   while (local->tm_sec==s)  
		   {   time(&t);
		       local=localtime(&t);
		   } 
		   Beep(500,10);              /* ���� */
		   img0 = cvCloneImage(img);  /* ����ͼ��img��img0 */
           cvZero(img);               /* ͼ��img��������  */  		   
           d(190,s,6);                /* ��ָ��ת�� */
           s=local->tm_sec;
           d(190,s,6); 
           cvXor(img0, img, img, NULL);
		   if (local->tm_min!=m)     /* ��ָ��ת�� */          
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
		   if (flag&&local->tm_min%12==0)   /* ʱָ��ת�� */
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
 �������ƣ�init
 �������ܣ���������
 ����: img��ʾָ������ͼ�����ݵ�ָ��
 ����ֵ: ��
***************************************************************************/
void init(IplImage *img) 
{
     
 	 CvFont  font;
	 int i,l,x1,x2,y1,y2;
     char *n[12]={ "3","4","5","6","7","8","9","10","11","12","1","2"};   /* ʱ������ʾ��12������ */
 
	 cvCircle(img,cvPoint(X0,Y0),R,cvScalar(0,255,0,0),1,8,0); 
     cvCircle(img,cvPoint(X0,Y0),R+5,cvScalar(0,255,255,0),1,8,0); 
     cvCircle(img,cvPoint(X0,Y0),5,cvScalar(0,0,255,0),1,8,0); 
    
     /* font--��ʾ����ʼ��������ṹ�塣
	    font_face--�������Ʊ�ʶ����Ŀǰ��֧��CV_FONT_HERSHEY_SIMPLEX�������������塣 
	    hscale--��ʾ�����ȵķŴ�ϵ��������0.5f��ʾ���Ϊԭ����һ�룬
	    shear--���屪���ݵ�б�ʣ�1��ʾ������б45�ȡ�
	    thickness--��ʾ�� ��ʻ��Ĵ�ϸ�̶ȡ�
	    line_type-- ��ʾ����ʻ������ͣ�����μ�cvLine��
	 */
      cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX,0.5f,0.5f,0,1,8);

     for(i=0;i<60;i++) 
	 {
		 
		 if(i%5==0) l=15;
		 else l=8;
         x1=(int)(R*cos(i*6*PI/180)+X0);       /* �����ʵ���λ�� */
         y1=(int)(R*sin(i*6*PI/180)+Y0);
         x2=(int)((R-l)*cos(i*6*PI/180)+X0);
         y2=(int)((R-l)*sin(i*6*PI/180)+Y0);
         cvLine(img,cvPoint(x1,y1),cvPoint(x2,y2),cvScalar(0,0,255,0),1,8,0);
         if(i%5==0) 
		 {
			 x1=(int)((R-25)*cos(i*6*PI/180)+X0);
             y1=(int)((R-25)*sin(i*6*PI/180)+Y0);
             /*
	         img--��ʾͼ��
	         text--����Ҫ�ϸ��ASCII�ַ������ܽ�����GB2312��˫�ֽڱ��롣
	         org--��ʾ��1���ַ����½ǵ����ꡣ
	         font--��ʾ����ṹ�塣 
	         color--��ʾ�ı���������ɫ��
	         */
             cvPutText(img,n[i/5],cvPoint(x1-5,y1+5),&font,cvScalar(0,0,255,0)); 
       }
	 }
}
