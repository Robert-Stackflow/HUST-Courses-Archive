// file : float_associativity.c   example from standford cs107
# include "stdio.h"

int main ( int argc , char ** argv )
{
float a = 3.14;
float b = 1e20;
printf (" (3.14 + 1e20 ) - 1e20 = %f\n", (a + b) - b);
printf (" 3.14 + (1 e20 - 1e20 ) = %f\n", a + (b - b));
return 0;
}
