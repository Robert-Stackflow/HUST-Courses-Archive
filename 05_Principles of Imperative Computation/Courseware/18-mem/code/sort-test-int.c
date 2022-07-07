/*
 * Testing sorting implementations
 * Utterly tasteless (and possibly bogus?), squeezes int in intptr_t
 *
 * Rob Simmons, Fall 2012
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "xalloc.h"
#include "contracts.h"
#include "sort.h"

void printarray(void** A, int n) {
  for (int i = 0; i < n; i++) { 
    printf("%d ", (int)(intptr_t)A[i]);
      if (i % 20 == 19) printf("\n");
    }
  printf("\n");
}

int int_compare(void* x, void* y) {
  int a = (int)(intptr_t)x;
  int b = (int)(intptr_t)y;
  if(a < b) return -1;
  if(a > b) return 1;
  return 0;
}

bool is_sorted_is_int(void** A, int lower, int upper) {
  REQUIRES(0 <= lower && lower <= upper); /* && upper <= \length(A) */
  if(lower == upper) return true;
  int max = (int)(intptr_t)A[lower];
  for(int i = lower+1; i < upper; i++) {
    int newmax = (int)(intptr_t)A[i];
    if (max > newmax) return false;
    max = newmax; 
  }
  return true;
}

int main() {
  printf("Testing array of size 0\n");
  void** Zero = xcalloc(0, sizeof(void*));
  sort(Zero, 0, 0, &int_compare);
  //assert(is_sorted(Zero, 0, 0));

  printf("Testing array of size 1\n");
  void** One = xcalloc(1, sizeof(void*));
  One[0] = (void*)(intptr_t)89;
  sort(One, 0, 1, &int_compare);
  //assert(is_sorted(One, 0, 1));

  printf("Testing small array with some duplicates\n");
  void** S = xcalloc(5, sizeof(void*));
  S[0] = (void*)(intptr_t)5; 
  S[1] = (void*)(intptr_t)3; 
  S[2] = (void*)(intptr_t)5; 
  S[3] = (void*)(intptr_t)2; 
  S[4] = (void*)(intptr_t)2;
  printarray(S, 5);
  sort(S, 0, 5, &int_compare);
  printarray(S, 5);


  int n = (1<<10)-3; // start with 1<<10 for timing; 1<<9 for -d
  int num_tests = 1000; // start with 1000 for timing; 10 for -d
  void** A = xcalloc(sizeof(int), n);
  printf("Testing random array of size %d, %d times\n", n, num_tests);
  for (int j = 0; j < num_tests; j++) {
    for (int i = 0; i < n; i++)
      A[i] = (void*)(intptr_t)rand();
    sort(A, 0, n, &int_compare);
    assert(is_sorted_is_int(A, 0, n));
  }
  printf("All tests passed!\n");
 
  return 0;
}
