#include "stdio.h"
#include "stdlib.h"
#define True 1
void data_write(char * filename);
void data_cal(char * filename,float price);
int main(void)
{	char a[20] = "c:\\data.dat";
	data_write(a);
	data_cal(a,31.4); /* 31.4�ǵ��� */
	return 0;
}
void data_write(char * filename)
{	FILE * out;
	char code[5];
	int number = 1;
	if((out = fopen(filename,"w")) == NULL)
			exit(-1);
	printf("input code and number please!\n");
	while( True ){
		scanf("%s%d",code,&number); /* �������Σ����� */
		if(number == 0) /* �������Ϊ0���������� */
			break;
		fprintf(out,"%s %d ",code,number);
	}
	fclose(out);
}
void data_cal(char * filename,float price)
{	FILE * in;
	char code[5];
	int number;
	if((in = fopen(filename,"r")) == NULL)
			exit(-1);
	printf("batch\tamount\tsum \n");
	while( fscanf(in,"%s %d ",code,&number) != EOF  && in != NULL){
		/* fscanf������inָ������ж����ݵ�code��number�� */
		printf("%s\t%d\t%8.2f\n",code,number,price*number);
	}
	fclose(in);
}
