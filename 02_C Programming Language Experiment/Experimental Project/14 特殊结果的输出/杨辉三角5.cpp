//�ⷨ��
#include <stdio.h>
int main()
{ 
	int i,j,n=0,a[17]={1},b[17];
	while(n<1||n>16)
	{ 
		printf("��������������ε�����:");
		scanf("%d",&n);
	}
	for(i=0;i<n;i++)
	{ 
		b[0]=a[0];
			for(j=1;j<=i;j++)
				b[j]=a[j-1]+a[j]; /*ÿ��������������֮��*/
					for(j=0;j<=i;j++)
	{ 				a[j]=b[j]; /*����õ����и���a,���ڴ�ӡ����һ�μ���*/
						printf("%5d",a[j]);
	}
		printf("\n");
	}
}

