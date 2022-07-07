#include "stdio.h"
#define N 10
int u[10], v[10];
int main(void)
{
   int i, j, n = 0;
   for (i=2; i<N; i++) 
      if (u[i] == 0) {
         v[n++] = i;
         for (j=i*i; j<N; j+=i) 
            u[j] = 1;
      }
   for (i=0; i<n; i++) {
      printf("%d", v[i]);
      if (i==n-1) 
         putchar('\n');
      else 
         putchar(',');
   }
   return 0;
}

