#include<stdio.h>
#include<stdlib.h> 
//d:\\matrix1.in 
//d:\\matrix2.in
//d:\\matrix3.in
int main()
{
	int n,m,i,j;
	char filename[20],ch;
	scanf("%s",filename);
	FILE *fp,*fout;
	fp=fopen(filename,"r");
	fout=fopen("d:\\result.out","w");
	n=fgetc(fp)-'0';
	fgetc(fp);
	m=fgetc(fp)-'0';
//	printf("%d %d\n",n,m);
	int chess[n][m],mid[m][n];
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			fscanf(fp,"%d",&chess[i][j]);
		}		
	}
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			*(*(mid+i)+j)=*(*(chess+j)+m-i-1);
			int temp=*(*(mid+i)+j);
			fprintf(fout,"%d",temp);
			if(j<(n-1))  
			fprintf(fout," ");
		}
		fprintf(fout,"\n");
	}
	fclose(fp);
	fclose(fout);
	fout=fopen("d:\\result.out","r");
	while((ch=fgetc(fout))!=EOF) putchar(ch);
	fclose(fout);
	return 0;
}

