#include<stdio.h>
int power_2(int n);
void find(int x,int y,int offset_x,int offset_y,int size);
int main(void)
{
	int k,x,y;
	scanf("%d%d%d",&k,&x,&y);
	find(x,y,1,1,power_2(k));
}
void find(int x,int y,int offset_x,int offset_y,int size)
{
    if(size==1) return;
    if(x-offset_x<=size/2-1 && y-offset_y<=size/2-1)
    {
        printf("%d %d 1\n",offset_x+size/2,offset_y+size/2);
        find(x,y,offset_x,offset_y,size/2);
        find(offset_x+size/2-1,offset_y+size/2,offset_x,offset_y+size/2,size/2);
        find(offset_x+size/2,offset_y+size/2-1,offset_x+size/2,offset_y,size/2);
        find(offset_x+size/2,offset_y+size/2,offset_x+size/2,offset_y+size/2,size/2);
    }
    else if(x-offset_x<=size/2-1 &&y-offset_y>size/2-1)
    {
        printf("%d %d 2\n",offset_x+size/2,offset_y+size/2-1);
        find(offset_x+size/2-1,offset_y+size/2-1,offset_x,offset_y,size/2);
        find(x,y,offset_x,offset_y+size/2,size/2);
        find(offset_x+size/2,offset_y+size/2-1,offset_x+size/2,offset_y,size/2);
        find(offset_x+size/2,offset_y+size/2,offset_x+size/2,offset_y+size/2,size/2);
    }
    else if(x-offset_x>size/2-1&& y-offset_y<=size/2-1)
    {
        printf("%d %d 3\n",offset_x+size/2-1,offset_y+size/2);
        find(offset_x+size/2-1,offset_y+size/2-1,offset_x,offset_y,size/2);
        find(offset_x+size/2-1,offset_y+size/2,offset_x,offset_y+size/2,size/2);
        find(x,y,offset_x+size/2,offset_y,size/2);
        find(offset_x+size/2,offset_y+size/2,offset_x+size/2,offset_y+size/2,size/2);
    }
    else
    {
        printf("%d %d 4\n",offset_x+size/2-1,offset_y+size/2-1);
        find(offset_x+size/2-1,offset_y+size/2-1,offset_x,offset_y,size/2);
        find(offset_x+size/2-1,offset_y+size/2,offset_x,offset_y+size/2,size/2);
        find(offset_x+size/2,offset_y+size/2-1,offset_x+size/2,offset_y,size/2);
        find(x,y,offset_x+size/2,offset_y+size/2,size/2);
    }
}
int power_2(int n)
{
	int sum=1;
	for(int i=1;i<=n;i++) sum*=2;
	return sum;
}
