#include<stdio.h>
int main()
{
  int i,j,m,base=1,n;
  int a[10][10]={1};
  scanf("%d",&n);
  for(m=0;m<n/2;m++)
   {
   	//���������ĸ����������С����Ӧѭ����ֵֹҪ��С 
    for(i=m;i<=n-1-m;i++)
    //���������ʱ�в���������
    	a[m][i]=base++;
    for(j=m+1;j<n-1-m;j++)
    //�������ʱ�������в���
        a[j][n-1-m]=base++;
    for(i=n-1-m;i>m;i--)
    //�������ʱ�в����м���
        a[n-1-m][i]=base++;
    for(j=n-1-m;j>m;j--)
    //���������ʱ�м���������
        a[j][m]=base++;
    if(n%2==1)
    //�����һ��ֵʱ������Ϊ����Ҫ������� 
        a[(n-1)/2][(n-1)/2]=base;
   }
   for(i=0;i<n;i++)
   {
    for(j=0;j<n;j++)
    {
    	printf("%2d",a[i][j]);
        if(j!=(n-1))
        printf(" ");
	} 
    printf("\n");
   }
   return 0;
} 
