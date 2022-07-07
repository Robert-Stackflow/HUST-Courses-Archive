#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void getFloatBin(float num);
//1.25 2.25 3.75 4.465 101.25 102.75 30.68 42.85 58.65 102.25
void store(){
	FILE * fpout; 
	int i; 
	float f[10]; 
	if((fpout=fopen("d:\\float.dat","w"))==NULL) 
	{ 
		printf("Can't open this file!\n"); 
		exit(-1); 
	} 
	for(i=0;i<10;i++) 
	{
	scanf("%f",&f[i]);
	getchar();	
	} 
	fwrite(f,sizeof(float),10,fpout); 
	fclose(fpout);
}
void display()
{
	FILE * fpin;
	float f[10];  
	int i; 
	if((fpin=fopen("d:\\float.dat","r"))==NULL) 
	{ 
	printf("Can't open this file!\n"); 
	exit(-1); 
	} 
	for(i=0;i<10;i++) 	fread(&f[i],sizeof(float),1,fpin); 
	fclose(fpin);  	
	for(i=0;i<10;i++) 	getFloatBin(f[i]);
}
void getFloatBin(float num)
{
    char bin[128];
	int t = 1;//用来按位与操作
    int *f = (int*)(&num);//将float的解释成int，即float的地址转成int*
    for(int i=0;i<32;i++)
    {
    //从最高位开始按位与，如果为1，则bin[i]=1，如果为0，则bin[i]=0
    //这里没有将bin存成字符，而是数字1 0
        bin[i] = (*f)&(t<<31-i)?1:0;
    }
    for(int i=0;i<32;i++)
    {
        printf("%d",bin[i]);
//        if(i==0)
//            printf(", ");
//        if(i==8)
//            printf(", ");
    }
    printf("\n");
}
int main()
{
	store();
	display();
    return 0;
}

