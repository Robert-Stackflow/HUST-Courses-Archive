#include<stdio.h>
int main(void) {
	char buff[255];
	int count=0;
	FILE* fp=fopen("data.hex","r");
	FILE* fp1=fopen("data3.hex","w");
	FILE* fp2=fopen("data2.hex","w");
	FILE* fp3=fopen("data1.hex","w");
	FILE* fp4=fopen("data0.hex","w");
	fprintf(fp1,"v2.0 raw\n");
	fprintf(fp2,"v2.0 raw\n");
	fprintf(fp3,"v2.0 raw\n");
	fprintf(fp4,"v2.0 raw\n");
	fgets(buff,20,fp);
	while(!feof(fp)) {
		fgets(buff,20,fp);
		fprintf(fp1,"%c%c\n",buff[0],buff[1]);
		fprintf(fp2,"%c%c\n",buff[2],buff[3]);
		fprintf(fp3,"%c%c\n",buff[4],buff[5]);
		fprintf(fp4,"%c%c\n",buff[6],buff[7]);
		count++;
		if(count>1020)
			break;
//		if((count%4)==0) {
//			fprintf(fp1,"\n",buff[0],buff[1]);
//			fprintf(fp2,"\n",buff[2],buff[3]);
//			fprintf(fp3,"\n",buff[4],buff[5]);
//			fprintf(fp4,"\n",buff[6],buff[7]);
//		}
	}
	fclose(fp);
}