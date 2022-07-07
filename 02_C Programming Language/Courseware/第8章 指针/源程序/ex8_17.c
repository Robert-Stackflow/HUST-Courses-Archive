#include "stdio.h"
#include "ctype.h"
#define N 20               /* N��ʾ��������������ĳ��� */
void shift(int *a,int n);
void shift(int *a,int n)/*�Ҷ�����λ����,����λ�Ƶ��±�Ϊ0��Ԫ��...*/
{
	  int k,len,sft;
	  len=N-1-n;               /* ���ݵĳ��� */
	  sft=N-len;               /* �Ҷ�����λ��λ�� */
	  for(k=0;k<len;k++)       /* �Ҷ�����λ */
		  *(a+k)=*(a+k+sft); 
	  for(k=len;k<N;k++)       
		  *(a+k)=0;            /* ��û�д�����ݵ�λ���0 */
}
int main(void)
{
	  int x[N],y[N],z[N+1],i,carry=0,flag;
	  for(i=0;i<N;i++)         /* ���������� */
		  *(z+i)=0;
	  i=N-1;	/*�������λ�±�*/
	  while(i>=0 && isdigit(*(x+i)=getchar()))/* �������� */
		  *(x+i--)-='0';       /* �����ַ�ת��Ϊ��Ӧ��ʮ������ */
	  if(i>=0) shift(x,i);     /* ���ݳ���С��N���Ҷ�����λ */
	  i=N-1;	/*�������λ�±�*/
	  while(i>=0 && isdigit(*(y+i)=getchar()))/* ������� */
		  *(y+i--)-='0';       /* �����ַ�ת��Ϊ��Ӧ��ʮ������ */
	  if(i>=0) shift(y,i);     /* ���ݳ���С��N���Ҷ�����λ */
	  for(i=0;i<N;i++){
		  *(z+i)=*(x+i) + *(y+i)+carry;    /* ����λ�ļӷ����� */
		  carry=(*(z+i) - *(z+i)%10)/10;   /* �����µĽ�λ */
		  *(z+i)%=10,*(z+i)+= '0'; /* �ȼ����λ����ת����Ϊ��Ӧ�����ַ� */
	  }
	  *(z+N)=carry+'0';           /* �͵����λת����Ϊ��Ӧ�����ַ� */
	  flag=0;
	  for(i=N;i>=0;i--){ /* �����������е�ǰ���ַ�'0'����� */
		  if(flag==0 && *(z+i)!= '0') flag=1;
		  if(flag==1) putchar(*(z+i));
	  }
	  putchar('\n');
	  return 0;
}
