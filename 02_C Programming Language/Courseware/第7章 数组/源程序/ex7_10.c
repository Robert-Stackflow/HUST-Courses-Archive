#include "stdio.h"
int main(void)
{		
	    char Capital[27],Lowercase[27];
	    int i,delt='a'-'A';            /* 'a'-'A'����0x20 */
	    Capital[0]= 'A';
	    Lowercase[0]=Capital[0]+delt;      /* 'a'��Lowercase[0] */
	    for(i=1;i<26;i++){
		    Capital[i]=Capital[i-1]+1;/* 'B'��'C'���� ��Capital[1]��*/
		    Lowercase[i]=Lowercase[i-1]+1;/* 'b'��'c'���� ��Lowercase[1]��*/
	    }
	    Capital[26]= '\0';			/* ���ַ����ս����Capital[26] */
	    Lowercase[26]=Capital[26];  /* ���ַ����ս����Lowercase[26] */
	    printf("%s\n",Capital);     /* ����ַ���ABCD��YZ */
	    printf("%s\n",Lowercase);   /* ����ַ���abcd��yz */
	    return 0;
}
