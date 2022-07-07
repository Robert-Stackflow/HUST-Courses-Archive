#include<stdio.h>
int main(void)
{
	char value[4][4]={{1,2,3,4},{5,6,7,8},{8,7,6,5},{4,3,2,1}};
	printf("value:         0x%x\n",value);
	printf("value:         0x%x\n",&value);
	for(int i=0;i<4;i++)
	{
	for(int j=0;j<4;j++)
	printf("value[%d][%d]:   0x%x\n",i,j,&value[i][j]);
	}
} 
