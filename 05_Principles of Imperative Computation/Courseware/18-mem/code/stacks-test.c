/* Testing generic stacks
 * 15-122 Principles of Imperative Computation, Fall 2010
 * Frank Pfenning
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "xalloc.h"
#include "contracts.h"
#include "stacks.h"

int main () {
  stack S = stack_new();
  int* x = (int*)xmalloc(sizeof(int));
  *x = 42;		/* x is heap-allocated */
  push(S, x);
  char* s = "242";		/* s is a constant string */
  push(S, s);			/* mixed-type stack; DON'T DO THIS */
  assert((char*)pop(S) == s);	/* EVER! */
  assert(*(int*)pop(S) == 42);
  printf("All tests passed!\n");
  free(x);			/* free x */
  assert(stack_empty(S));
  //stack_free(S);		/* stack is empty; free */
  return 0;
}
