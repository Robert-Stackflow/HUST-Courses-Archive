//file:  get_var_size.c
#include "stdio.h"
# include "stdlib.h"
int main ()
{
int iarray [] = {5 , 4 , 3 , 2 , 1};
char * iarr = ( char *) iarray ;
printf (" sizeof ( char ): %d\n", ( int) sizeof ( char ) ) ;
printf (" sizeof ( short ): %d\n", ( int ) sizeof ( short ) ) ;
printf (" sizeof (int ): %d\n", ( int) sizeof (int ) ) ;
printf (" sizeof ( unsigned int ): %d\n", (int ) sizeof ( unsigned int ) ) ;
printf (" sizeof ( long ): %d\n", ( int) sizeof ( long ) ) ;
printf (" sizeof ( long long ): %d\n", (int ) sizeof ( long long ) ) ;
printf (" sizeof ( size_t ): %d\n", (int ) sizeof ( size_t ) ) ;
printf (" sizeof ( void *): %d\n", (int ) sizeof ( void *) ) ;
printf (" sizeof ( iarray ): %d\n", (int ) sizeof ( iarray ) ) ;
printf (" sizeof ( iarr ): %d\n", ( int) sizeof ( iarr ) ) ;
return 0;
}
