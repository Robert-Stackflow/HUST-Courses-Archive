#include "stdio.h"
#include "ctype.h"
#define N 20               /* N表示参与运算数据最长的长度 */
void shift(int *a,int n);
void shift(int *a,int n)/*右对齐移位函数,将个位移到下标为0的元素...*/
{
	  int k,len,sft;
	  len=N-1-n;               /* 数据的长度 */
	  sft=N-len;               /* 右对齐移位的位数 */
	  for(k=0;k<len;k++)       /* 右对齐移位 */
		  *(a+k)=*(a+k+sft); 
	  for(k=len;k<N;k++)       
		  *(a+k)=0;            /* 对没有存放数据的位填充0 */
}
int main(void)
{
	  int x[N],y[N],z[N+1],i,carry=0,flag;
	  for(i=0;i<N;i++)         /* 和数组清零 */
		  *(z+i)=0;
	  i=N-1;	/*计算最高位下标*/
	  while(i>=0 && isdigit(*(x+i)=getchar()))/* 处理被加数 */
		  *(x+i--)-='0';       /* 数字字符转换为对应的十进制数 */
	  if(i>=0) shift(x,i);     /* 数据长度小于N，右对齐移位 */
	  i=N-1;	/*计算最高位下标*/
	  while(i>=0 && isdigit(*(y+i)=getchar()))/* 处理加数 */
		  *(y+i--)-='0';       /* 数字字符转换为对应的十进制数 */
	  if(i>=0) shift(y,i);     /* 数据长度小于N，右对齐移位 */
	  for(i=0;i<N;i++){
		  *(z+i)=*(x+i) + *(y+i)+carry;    /* 带进位的加法运算 */
		  carry=(*(z+i) - *(z+i)%10)/10;   /* 计算新的进位 */
		  *(z+i)%=10,*(z+i)+= '0'; /* 先计算该位，再转换成为对应数字字符 */
	  }
	  *(z+N)=carry+'0';           /* 和的最高位转换成为对应数字字符 */
	  flag=0;
	  for(i=N;i>=0;i--){ /* 输出结果。和中的前导字符'0'不输出 */
		  if(flag==0 && *(z+i)!= '0') flag=1;
		  if(flag==1) putchar(*(z+i));
	  }
	  putchar('\n');
	  return 0;
}
