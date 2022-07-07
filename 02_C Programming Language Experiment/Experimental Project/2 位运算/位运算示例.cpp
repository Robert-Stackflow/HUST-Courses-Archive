#include <stdio.h>
#include <string.h>
int main( )
{
//--------------------1------------------------ 
//    short x[ ]={ -1,0,1}, *p=x;		
//	unsigned short y=8;
//	y=~x[1];
//	printf("%hu\n",y);
//	y>>=x[2];
//	printf("%hu\n",y);
//	short z=~(*p<<3);
//	printf("%hd\n",z);
//--------------------2------------------------
//	char c1=16, c2=0x61; 
//	short h1=0x10 ,h2=0xFF01; 
//	unsigned long lu=0x12345678;
//	c1= lu;
//	printf("%d\n",c1);
//	int m=c2&h2>>4;
//	printf("%d\n",m);
//	char c; 
//	short x=0x80ff;
//	c=x>>8;
//	printf("%hd\t%hd\t%d\n",x,x>>8,c);
//	unsigned i=0,j=1; 、
//	int b; 
//	a=~i>j;//是大于而不是右移！！！ 
//	b=~i^j;
//	printf("%d\t%u\t%u\t%d\n",~i,~i,~i>j,a);
//	printf("%d\n",b);
//	printf("%u\n",-i>>15&&-j<<15);
//--------------------3------------------------
//	char a=4, b=6, c; 
//	short x=0x80ff, y=10;
//	c=x>>8;	
//	printf("%u\n",c);	
//	y=y&x<<4;
//	printf("%hd\n",y);		
//	b=~b|x;
//	printf("%d\n",b);
//--------------------4------------------------
//	unsigned short int a=65535;
//	printf("%hd,%d\n",-a,-a); 
//--------------------5------------------------
//	char a[20]={'a','s','d','f','\0'}, b[]="1234";
//	//此处‘\0’删去有何影响？ 
//	printf("%s\t%s\n",a,b);
//	strcat(a,b);
//	printf("%s\t%s\n",a,b); 
//--------------------6------------------------
//	typedef unsigned short int UINT16;
//	UINT16 u=1,v=2,w=4,x=8,y=16,z=32;
//	printf("%d",x+y+z>-1ul);
//--------------------7------------------------
//	int a[3]={6,-20,8};   
//	printf("%d",a[1]>0U?1:0); 
//--------------------8------------------------
//	char a[]="c:\\file\\";
//	int b[9];
//	float c[9]; 
//	printf("%d %d %d",sizeof(a),sizeof(b),sizeof(c));
//--------------------9------------------------
//	int a=8,b=5,c;
//	c=a/b+0.4;
//	printf("%d",c);
//--------------------10------------------------
//	char a[20];
//	char *t=a;
//	t=(char *)malloc(20);
//	scanf("%s",t);
//	printf("%s",t);
//	printf("\n\x10");
//--------------------11------------------------
//	int x=3,y=4,z=5;
//	printf("%d",!(x+y)+z-1&&y+z/2); 
}

