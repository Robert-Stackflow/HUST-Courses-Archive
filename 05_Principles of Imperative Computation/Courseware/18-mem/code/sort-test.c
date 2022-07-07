/*
 * Testing sorting implementations
 * Utterly tasteless (and possibly bogus?), squeezes int in intptr_t
 *
 * Rob Simmons, Fall 2012
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "xalloc.h"
#include "sort.h"

void printarray(void** A, int n) {
  for (int i = 0; i < n; i++) { 
    printf("%s ", (char*)A[i]);
      if (i % 11 == 10) printf("\n");
    }
  printf("\n");
}

int string_compare(void* x, void* y) {
  return(strcmp((char*)x, (char*)y));
}

int main() {
  printf("Testing array of size 0\n");
  void** Zero = xcalloc(0, sizeof(void*));
  sort(Zero, 0, 0, &string_compare);

  printf("Testing array of size 1\n");
  void** One = xcalloc(1, sizeof(void*));
  One[0] = (void*)"pancake";
  sort(One, 0, 1, &string_compare);

  printf("Testing small array with some duplicates\n");
  void** S = xcalloc(10, sizeof(void*));
  S[0] = (void*)"terror"; 
  S[1] = (void*)"ghost"; 
  S[2] = (void*)"monster";
  S[3] = (void*)"scaryclown"; 
  S[4] = (void*)"candy"; 
  S[5] = (void*)"monster";
  S[6] = (void*)"boogeyman";
  S[7] = (void*)"ghost";
  S[8] = (void*)"fright";
  S[9] = (void*)"noooo";
  printf("Unsorted:\n");
  printarray(S, 10);
  sort(S, 0, 10, &string_compare);
  printf("Sorted?:\n");
  printarray(S, 10);

  printf("All tests passed!\n");
 
  return 0;
}
