#include<stdio.h>
int main(void) {
	char buff[255];
	char fpFileName[6]="x.txt";
	char foutFileName[6]="x.hex";
	char foutFileName2[10]="split.hex";
	char foutFileName3[10]="clear.hex";
	for(int i=1; i<=9; i++) {
		fpFileName[0]=(i+'0');
		foutFileName[0]=(i+'0');
		FILE* fp=fopen(fpFileName,"r");
		FILE* fout=fopen(foutFileName,"w");
		fprintf(fout,"v2.0 raw\n");
		while(!feof(fp)) {
			char ch1,ch2;
			int x=0,y1=0,y2=0;
			fscanf(fp,"%d%c%d%c%d",&x,&ch1,&y1,&ch2,&y2);
			if(x==0&&y1==0&&y2==0)
				break;
			x+=10;
			for(int i=y1; i<=y2; i++) 
				fprintf(fout,"%02x%02x\n",x,i);
		}
		fclose(fp);
		fclose(fout);
	}
	{
		FILE* fout=fopen(foutFileName2,"w");
		fprintf(fout,"v2.0 raw\n");
		for(int x=0; x<=128; x++) {
			fprintf(fout,"%02x29\n",x);
			fprintf(fout,"%02x2a\n",x);
			fprintf(fout,"%02x2b\n",x);
			fprintf(fout,"%02x2c\n",x);
			fprintf(fout,"%02x59\n",x);
			fprintf(fout,"%02x56\n",x);
			fprintf(fout,"%02x57\n",x);
			fprintf(fout,"%02x58\n",x);
		}
		for(int x=0; x<=128; x++) {
			fprintf(fout,"29%02x\n",x);
			fprintf(fout,"2a%02x\n",x);
			fprintf(fout,"2b%02x\n",x);
			fprintf(fout,"2c%02x\n",x);
			fprintf(fout,"59%02x\n",x);
			fprintf(fout,"56%02x\n",x);
			fprintf(fout,"57%02x\n",x);
			fprintf(fout,"58%02x\n",x);
		}
		fclose(fout);
	}
	{
		FILE* fout=fopen(foutFileName3,"w");
		fprintf(fout,"v2.0 raw\n");
		for(int x=10; x<=30; x++)
			for(int y=5; y<=35; y++)
			fprintf(fout,"%02x%02x\n",x,y);
		fclose(fout);
	}
}