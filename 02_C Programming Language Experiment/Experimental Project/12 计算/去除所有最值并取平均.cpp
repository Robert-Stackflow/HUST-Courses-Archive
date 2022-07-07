#include <stdio.h>
int main(void)
{
	int number;
	scanf("%d",&number);
	int a[number],n;
	for(n=0;n<=number-1;n++){
		scanf("%d",&a[n]);
	}
	int i,max,min,sum=0,maxNum=0,minNum=0;
	float average;
	sum=0;
	max=a[0];
	min=a[0];
	for(i=0;i<number;i++)
	{
	if(max<a[i])
		max=a[i];
	if(min>a[i])
		min=a[i];
	sum=sum+a[i];
	}
	for(i=0;i<number;i++)
	{
		if(a[i]==max)
		maxNum++;
		if(a[i]==min)
		minNum++;
	} 
	if((max==min)||((minNum +maxNum)==number)){
		printf("\n#DIV/0!\n")	;
	}
	else{
	average=(float)(sum-maxNum*max-minNum*min)/(number-maxNum-minNum);
	printf("\n%.2f\n\n",average);	
	}
	return 0;
}
