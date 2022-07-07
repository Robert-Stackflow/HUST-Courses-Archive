#include "stdio.h"
int main(void)
{	char a[20];
	unsigned char u,i=0;
	FILE *fin,*fout;
	fout=fopen("c:\\abc.dat","w+");
	while(gets(a)!=NULL)
		fprintf(fout,"%s",a); /* 也可以用： fputs(a,fout); */
	fclose(fout);
	fin=fopen("c:\\abc.dat","r+b");
	while(!feof(fin)){
		fread(&u,sizeof(unsigned char),1,fin);
		if(!feof(fin)){
			printf("%04X  %X\t",i++,u);
			if(i%4==0) 
				printf("\n");
		}
	}
	printf("\n");
	fclose(fin);
	return 0;
}
