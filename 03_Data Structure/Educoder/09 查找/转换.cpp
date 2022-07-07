#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(void)
{
	FILE*fin=fopen("d:\\in.txt","r");
	FILE*fout=fopen("d:\\out.txt","w");
	while(!feof(fin))
	{
	int num=0;
	char str[20];
	fscanf(fin,"%s",str);
	for(int i=0;i<strlen(str);i++)
		num=13*num+(str[i]-'A');
	fprintf(fout,"num(%s) = \t%d\th(%s) = \t%d\n",str,num,str,num%16);
	}
	fclose(fin);
	fclose(fout);
	return 0;
}
