#include "stdio.h"
int main(void)
{		
	    char Capital[27],Lowercase[27];
	    int i,delt='a'-'A';            /* 'a'-'A'µÈÓÚ0x20 */
	    Capital[0]= 'A';
	    Lowercase[0]=Capital[0]+delt;      /* 'a'ËÍLowercase[0] */
	    for(i=1;i<26;i++){
		    Capital[i]=Capital[i-1]+1;/* 'B'¡¢'C'¡¢¡­ ËÍCapital[1]¡­*/
		    Lowercase[i]=Lowercase[i-1]+1;/* 'b'¡¢'c'¡¢¡­ ËÍLowercase[1]¡­*/
	    }
	    Capital[26]= '\0';			/* ËÍ×Ö·û´®ÖÕ½á·ûµ½Capital[26] */
	    Lowercase[26]=Capital[26];  /* ËÍ×Ö·û´®ÖÕ½á·ûµ½Lowercase[26] */
	    printf("%s\n",Capital);     /* Êä³ö×Ö·û´®ABCD¡­YZ */
	    printf("%s\n",Lowercase);   /* Êä³ö×Ö·û´®abcd¡­yz */
	    return 0;
}
