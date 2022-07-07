#include<stdio.h>
#include<stdlib.h>

void QuickSort( int a[ ], int left , int right ); 
int partition(int a[ ], int left, int right );
void swap(int a[],int i,int j);
char *TempFileName(int id);
int ReadData(FILE* f, int a[], int n);
int MemorySort(char *filename,int n);
void MergeSort(char *filename,int n);

int N=10;  /* һ�ζ�������ݸ��� */

int main()
{
	int d;
	d=MemorySort("unsort",N);
	MergeSort("sort.txt",d);
	return 0;
}


/************************************************************************************
�������ƣ� ReadData
�������ܣ� �Ӵ����ж���n���������ڴ档 
����������
        f ��ָ������ļ���
        a ������������ݵ����顣
        n ���������ݵ���������
��������ֵ������ʵ�ʶ��������ݸ�����
************************************************************************************/
int ReadData(FILE* f, int a[], int n)
{
	int i = 0;
	while(i<n && (fscanf(f, "%d", &a[i]) != EOF)) 
		i++;
	return i;
}

/************************************************************************************
�������ƣ� WriteData
�������ܣ� ���ڴ������д������ļ��� 
����������
        f ��ָ������ļ���
        a �������ڴ����ݵ����顣
        n �����ݵĸ�����
��������ֵ���ޡ�
************************************************************************************/
void WriteData(FILE* f, int a[], int n)
{
	int i;
	for( i = 0; i < n; ++i)
		fprintf(f, "%d ", a[i]);
}

/************************************************************************************
�������ƣ�TempFileName
�������ܣ� �����ļ�������������ʱ�ļ����� 
���������� id ���ļ�������
��������ֵ����ʱ�ļ�����
************************************************************************************/
char *TempFileName(int id)
{
	static char tempfile[12];
	sprintf(tempfile, "temp%d.txt", id);
	return tempfile;
}

/************************************************************************************
�������ƣ� MemorySort
�������ܣ� ÿ�δӴ����ж���n�����ݵ��ڴ棻 ���ڴ����� ���ź��������д����ʱ�ļ��� 
           �ظ��������̣�����������ʱ�ļ�.
����������
        filename ���������ݵĴ����ļ�����
        n ���������ݵ���������
��������ֵ�����ɵ���ʱ�ļ�������
************************************************************************************/
int MemorySort(char *filename,int n)
{
	FILE *fin,*ftemp ;
	char *tempfile; /* ָ����ʱ�ļ��� */
	int *array,filecount = 0,datacount;

	if( (fin=fopen(filename, "r")) ==NULL) {
		printf(" can't open file %s\n ",filename);
	    exit(-1);
	}

	array = (int *)malloc(sizeof(int)*n); /* ��̬������n�������Ĵ洢�ռ� */
	/* ÿ����n�����������ڴ�����һ�����򣬲�д����ʱ�ļ� */
	for(;;) {
		datacount = ReadData(fin, array, n);  /* �����ݶ����ڴ� */
	    QuickSort(array, 0, datacount-1);   /* ���ڴ����� */		
		tempfile=TempFileName(filecount++);  
        if((ftemp=fopen(tempfile, "w"))==NULL) { /* ����ʱ�ļ� */
			printf("can't open file %s\n ",tempfile);
	        exit(-1);
		}
		WriteData(ftemp, array, datacount);  /* д����ʱ�ļ� */
		fclose(ftemp);
		if(datacount!=n) break;  /* ���һ�����ݣ����� */
	}
	free(array);
	fclose(fin);
	return filecount;
}

/************************************************************************************
�������ƣ� MergeSort
�������ܣ� ʹ�ö�·�鲢����ʱ�ļ��е����ݰ���д������ļ�
����������
        filename ������ļ�����
        n ����ʱ�ļ��ĸ�����
��������ֵ���ޡ�
************************************************************************************/
void MergeSort(char *filename,int n)
{
	
	FILE *fout;
	FILE **pf;   /* �洢n����ʱ�ļ�ָ�� */
    int *buf;    /* �洢ÿ���ļ���ǰ��һ������ */
    int * tag ;  /* ����ļ��Ƿ���� */
	char *temp;
	int i,min,index,k;

	if((fout=fopen(filename, "w"))==NULL) {  /* ������ļ� */
			printf("can't open file %s\n ",filename);
	        exit(-1);
	}
	pf =(FILE **) malloc(sizeof( FILE *)*n); /* ����洢�ռ� */
	buf = (int *)malloc(sizeof(int)*n);  
    tag = (int *)malloc(sizeof(int)*n);   
	for(i = 0; i < n; ++i)
	{ 
		temp = TempFileName(i);
		tag[i]= 1;
		pf[i] = fopen(temp, "r");     /* ����ʱ�ļ� */
		if(fscanf(pf[i],"%d",&buf[i])==EOF) tag[i]=0; 
	}
	for(;;) {
		min = buf[0];
		index = 0;
		for (k=0;k<n;k++) {/* ��buf�е���С */
			if (tag[k]&&buf[k]<min) {
				min=buf[k];
				index = k;
			}
		}
		if(index==0 && !tag[0])  break;
		fprintf(fout, "%d ", min);      /* д���ļ� */
		if (fscanf(pf[index], "%d", &buf[index])==EOF) { 
			tag[index] = 0;
		}
	}

	fclose(fout);  /* �ر�����ļ� */
	for(k=0;k<n;k++) /* �ر���ʱ�ļ� */
		fclose(pf[k]);
	free(buf); /* �ͷ��ڴ� */
    free(tag);
    free(pf);
}

/************************************************************************************
�������ƣ� QuickSort
�������ܣ� ��quick���򷨶�����a�е�Ԫ��a[left ] ��a[right]����С�����˳�����С� 
����������
        a ���������Ԫ�ص����顣
        left ������Ԫ�ص���ʼ�±ꡣ
        right ������Ԫ�صĽ����±ꡣ
��������ֵ���ޡ�
************************************************************************************/
void QuickSort(int a[ ],int left,int right)
{
	int split;    /*  ����λ��  */
	if(left<right)  
	{
		split=partition(a,left,right); /*  ������ֳ������� */
		QuickSort(a,left,split-1);  /*  ���󲿷ֵݹ�����  */
		QuickSort(a,split+1,right);  /*   ���Ҳ��ֵݹ�����  */
	}
}

/************************************************************************************
�������ƣ� partition
�������ܣ� ������a�е�Ԫ��a[left ] ��a[right]�ֳ������֣�
           ʹ�зֵ���ߵ��������ݶ�С�ڵ����зֵ��ֵ��
           �зֵ��ұߵ��������ݶ������зֵ��ֵ�� 
����������
        a ���������Ԫ�ص����顣
        left ������Ԫ�ص���ʼ�±ꡣ
        right ������Ԫ�صĽ����±ꡣ
��������ֵ���зֵ���±ꡣ
************************************************************************************/
int partition(int a[ ],int left,int right )
{
	int  i=left,j=right+1;    
	int  split=(left+right)/2;  /*  ѡ��������м�Ԫ����Ϊ�з�Ԫ��  */

    swap(a,left,split);      /*  ���з�Ԫ���Ƶ�����Ŀ�ͷ  */
	for ( ; ; ) 
	{
		while(a[++i]<=a[left] && i <= right);   /*��������ɨ�裬 ���ҵ�һ�������з�Ԫ�ص�����  */
		while(a[--j]> a[left]);            /*  ��������ɨ�裬�Է���һ��С�ڵ����з�Ԫ�ص�����  */
		if(i>=j) break;                 /*  ɨ���������򽻲棩����ѭ��  */
        swap(a,i,j);      /*  �����������ߵ�Ԫ��  */
	}
    /*  j ���з�Ԫ�ص�λ��  */
    swap(a,left,j);        /*  ���з�Ԫ�������Ƶ��м�  */
	return j;          /*  �����з�Ԫ�ص��±�  */
}

/************************************************************************************
�������ƣ�swap
�������ܣ� ������a[i]a��[j]����
����������
        a ��������ݵ����顣
        i ��������Ԫ�ص��±ꡣ
        j ��������Ԫ�ص��±ꡣ
��������ֵ���ޡ�
************************************************************************************/
void swap(int a[],int i,int j)
{
  int  temp ;
  temp = a[i];  
  a[i] = a[j];  
  a[j] = temp;
}