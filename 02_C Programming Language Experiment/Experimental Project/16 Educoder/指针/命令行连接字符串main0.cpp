#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char *p;         //  ��ָ��ָ�����Ӻ���ַ���
#define SIZE_INPUT 100
#define SIZE 51

int main0(int argc,char* argv[]); // ����main0����ԭ�ͣ��൱�ڱ��ش���main

int main()
{
    char *inputStr[SIZE_INPUT]; // ָ�������е�ÿ������
    int n=0;           // �洢��������
     
    char bufferStr[SIZE];
    char in;
    int state=0,i;    
   /*******************************************************************
       ���� Begin ... End  ֮��Ĵ���ģ�������е�����Ͳ������Ĵ洢  
   ***************  Begin  ********************************************/
    do {
	    in=getchar();  
    	switch(state){
    		case 0:          // ��ǰ״̬�ǿո�
			   if(in!=' '){   // �������ĵ�1���ַ�
			        i=0;
					bufferStr[i++]=in;
					state=1;
				}
				break;
			case 1:      // ��ǰ״̬���ַ�
			   if(in==' '||in=='\n'){   // ���յ�һ�����������洢�ò���
			        bufferStr[i++]='\0';
			        inputStr[n]=(char*)malloc(sizeof(char)*i);
					strcpy(inputStr[n++],bufferStr);
					state=0;
				}
				else 	bufferStr[i++]=in;
				break;
        } 
	} while(in!='\n');
   /****************   End *****************************************/
   
    main0(n,inputStr);     //  ���ô���main0����
    
    printf("%s",p);        //  ������Ӻ���ַ���

    for(i=0;i<n;i++){
    	free(inputStr[i]);
	}
}

