/* 
 * A little example of an array of strings
 *
 * 15-122 Principles of Imperative Computation
 *
 * Penny Anderson 6/2013
 *
 * compile with 
 * gcc -Wall -Wextra -Werror -std=c99 -pedantic -g -DDEBUG xalloc.c string-array.c
 *
 */

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

#include "contracts.h"
#include "xalloc.h"

int main() {
  // allocate room for ten pointers to characters (strings)
  char **heap_strings = xcalloc(6, sizeof(char*));
  // initialize an array of (constant) strings
  char *const_strings[] = { "able", "baker", "charlie", "dog", "easy", "fox" };

  for ( int i = 0 ; i < 6 ; i++ ) {
    ASSERT(0 <= i);
    heap_strings[i] = xcalloc(1 + strlen(const_strings[i]), sizeof(char));
    strcpy(heap_strings[i], const_strings[i]);
    ASSERT(strcmp(heap_strings[i], const_strings[i]) == 0);
    int len = strlen(const_strings[i]);
    ASSERT(heap_strings[i][len+1] == '\0');
  }

  for ( int i = 0 ; i < 6 ; i++ ) {
    ASSERT(0 <= i);
    printf("%s\n",heap_strings[i]);
    // run valgrind before uncommenting next line, then run again
    free(heap_strings[i]); 
  }
  // run valgrind before uncommenting next line, then run again
  free(heap_strings);

  return 0;
}
