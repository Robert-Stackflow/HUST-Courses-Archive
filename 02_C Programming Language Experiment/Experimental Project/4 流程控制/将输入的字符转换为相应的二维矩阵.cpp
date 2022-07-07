#include<stdio.h> 
int main(void)
{
	char scale_c;
	int scale,flag,j;
	printf("Input the cmd!(a letter):");
	scanf("%c",&scale_c);
	if(scale_c<='z'&&scale_c>='a') {scale=scale_c-'a'+1;flag=1;}
	else if(scale_c<='Z'&&scale_c>='A') {scale=scale_c-'A'+1;flag=0;}
	int limit=scale;
	for(int i=0;i<scale;i++)
	{
		int count=0;
		for(j=0;j<scale;j++)
		{
			printf("%c ",flag?'a'+i+j:'A'+i+j);
			count++;
			if(i+j+2>scale) break;
		}
		scale=scale-count;
		for(int k=0;k<scale;k++)
			printf("%c ",flag?'a'+k:'A'+k);
		printf("\n");
		scale=limit;
	}
	return 0;
}
