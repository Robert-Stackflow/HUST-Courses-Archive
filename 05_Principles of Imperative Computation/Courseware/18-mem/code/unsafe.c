#include <stdlib.h>
#include <stdio.h>

int main() {
  int* A = malloc(sizeof(int));
  A[0] = 0;    /* ok - A[0] is like *A */
  A[1] = 1;    /* error - not allocated */
  A[317] = 29; /* error - not allocated */
  A[-1] = 32;  /* error - not allocated(!) */
  printf("A[-1] = %d\n", A[-1]);
  return 0;
}
