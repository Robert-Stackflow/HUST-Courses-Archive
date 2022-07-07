#include<stdio.h>
#include<stdlib.h>

void QuickSort( int a[ ], int left , int right ); 
int partition(int a[ ], int left, int right );
void swap(int a[],int i,int j);
char *TempFileName(int id);
int ReadData(FILE* f, int a[], int n);
int MemorySort(char *filename,int n);
void MergeSort(char *filename,int n);

int N=10;  /* 一次读入的数据个数 */

int main()
{
	int d;
	d=MemorySort("unsort",N);
	MergeSort("sort.txt",d);
	return 0;
}


/************************************************************************************
函数名称： ReadData
函数功能： 从磁盘中读入n个整数到内存。 
函数参数：
        f ：指向磁盘文件。
        a ：保存读入数据的数组。
        n ：读入数据的最多个数。
函数返回值：返回实际读到的数据个数。
************************************************************************************/
int ReadData(FILE* f, int a[], int n)
{
	int i = 0;
	while(i<n && (fscanf(f, "%d", &a[i]) != EOF)) 
		i++;
	return i;
}

/************************************************************************************
函数名称： WriteData
函数功能： 将内存的数据写入磁盘文件。 
函数参数：
        f ：指向磁盘文件。
        a ：保存内存数据的数组。
        n ：数据的个数。
函数返回值：无。
************************************************************************************/
void WriteData(FILE* f, int a[], int n)
{
	int i;
	for( i = 0; i < n; ++i)
		fprintf(f, "%d ", a[i]);
}

/************************************************************************************
函数名称：TempFileName
函数功能： 根据文件索引号生成临时文件名。 
函数参数： id ：文件索引号
函数返回值：临时文件名。
************************************************************************************/
char *TempFileName(int id)
{
	static char tempfile[12];
	sprintf(tempfile, "temp%d.txt", id);
	return tempfile;
}

/************************************************************************************
函数名称： MemorySort
函数功能： 每次从磁盘中读入n个数据到内存； 在内存排序； 将排好序的数据写入临时文件； 
           重复上述过程，生成若干临时文件.
函数参数：
        filename ：存有数据的磁盘文件名。
        n ：读入数据的最多个数。
函数返回值：生成的临时文件个数。
************************************************************************************/
int MemorySort(char *filename,int n)
{
	FILE *fin,*ftemp ;
	char *tempfile; /* 指向临时文件名 */
	int *array,filecount = 0,datacount;

	if( (fin=fopen(filename, "r")) ==NULL) {
		printf(" can't open file %s\n ",filename);
	    exit(-1);
	}

	array = (int *)malloc(sizeof(int)*n); /* 动态分配存放n个整数的存储空间 */
	/* 每读入n个整数就在内存中做一次排序，并写入临时文件 */
	for(;;) {
		datacount = ReadData(fin, array, n);  /* 将数据读入内存 */
	    QuickSort(array, 0, datacount-1);   /* 在内存排序 */		
		tempfile=TempFileName(filecount++);  
        if((ftemp=fopen(tempfile, "w"))==NULL) { /* 打开临时文件 */
			printf("can't open file %s\n ",tempfile);
	        exit(-1);
		}
		WriteData(ftemp, array, datacount);  /* 写到临时文件 */
		fclose(ftemp);
		if(datacount!=n) break;  /* 最后一块数据，结束 */
	}
	free(array);
	fclose(fin);
	return filecount;
}

/************************************************************************************
函数名称： MergeSort
函数功能： 使用多路归并将临时文件中的数据按序写入输出文件
函数参数：
        filename ：输出文件名。
        n ：临时文件的个数。
函数返回值：无。
************************************************************************************/
void MergeSort(char *filename,int n)
{
	
	FILE *fout;
	FILE **pf;   /* 存储n个临时文件指针 */
    int *buf;    /* 存储每个文件当前的一个数据 */
    int * tag ;  /* 标记文件是否读完 */
	char *temp;
	int i,min,index,k;

	if((fout=fopen(filename, "w"))==NULL) {  /* 打开输出文件 */
			printf("can't open file %s\n ",filename);
	        exit(-1);
	}
	pf =(FILE **) malloc(sizeof( FILE *)*n); /* 分配存储空间 */
	buf = (int *)malloc(sizeof(int)*n);  
    tag = (int *)malloc(sizeof(int)*n);   
	for(i = 0; i < n; ++i)
	{ 
		temp = TempFileName(i);
		tag[i]= 1;
		pf[i] = fopen(temp, "r");     /* 打开临时文件 */
		if(fscanf(pf[i],"%d",&buf[i])==EOF) tag[i]=0; 
	}
	for(;;) {
		min = buf[0];
		index = 0;
		for (k=0;k<n;k++) {/* 找buf中的最小 */
			if (tag[k]&&buf[k]<min) {
				min=buf[k];
				index = k;
			}
		}
		if(index==0 && !tag[0])  break;
		fprintf(fout, "%d ", min);      /* 写入文件 */
		if (fscanf(pf[index], "%d", &buf[index])==EOF) { 
			tag[index] = 0;
		}
	}

	fclose(fout);  /* 关闭输出文件 */
	for(k=0;k<n;k++) /* 关闭临时文件 */
		fclose(pf[k]);
	free(buf); /* 释放内存 */
    free(tag);
    free(pf);
}

/************************************************************************************
函数名称： QuickSort
函数功能： 用quick排序法对数组a中的元素a[left ] 至a[right]按从小到大的顺序排列。 
函数参数：
        a ：存放排序元素的数组。
        left ：排序元素的起始下标。
        right ：排序元素的结束下标。
函数返回值：无。
************************************************************************************/
void QuickSort(int a[ ],int left,int right)
{
	int split;    /*  分区位置  */
	if(left<right)  
	{
		split=partition(a,left,right); /*  将数组分成两部分 */
		QuickSort(a,left,split-1);  /*  对左部分递归排序  */
		QuickSort(a,split+1,right);  /*   对右部分递归排序  */
	}
}

/************************************************************************************
函数名称： partition
函数功能： 将数组a中的元素a[left ] 至a[right]分成两部分，
           使切分点左边的所有数据都小于等于切分点的值，
           切分点右边的所有数据都大于切分点的值。 
函数参数：
        a ：存放排序元素的数组。
        left ：排序元素的起始下标。
        right ：排序元素的结束下标。
函数返回值：切分点的下标。
************************************************************************************/
int partition(int a[ ],int left,int right )
{
	int  i=left,j=right+1;    
	int  split=(left+right)/2;  /*  选择数组的中间元素作为切分元素  */

    swap(a,left,split);      /*  将切分元素移到数组的开头  */
	for ( ; ; ) 
	{
		while(a[++i]<=a[left] && i <= right);   /*从左至右扫描， 以找到一个大于切分元素的数据  */
		while(a[--j]> a[left]);            /*  从右至左扫描，以发现一个小于等于切分元素的数据  */
		if(i>=j) break;                 /*  扫描相遇（或交叉）结束循环  */
        swap(a,i,j);      /*  交换左右两边的元素  */
	}
    /*  j 是切分元素的位置  */
    swap(a,left,j);        /*  将切分元素重新移到中间  */
	return j;          /*  返回切分元素的下标  */
}

/************************************************************************************
函数名称：swap
函数功能： 将数组a[i]a和[j]交换
函数参数：
        a ：存放数据的数组。
        i ：待交换元素的下标。
        j ：待交换元素的下标。
函数返回值：无。
************************************************************************************/
void swap(int a[],int i,int j)
{
  int  temp ;
  temp = a[i];  
  a[i] = a[j];  
  a[j] = temp;
}