/* Allocation utilities
 * Implement versions of malloc and free that abort
 * when allocation fails instead of returning NULL.
 *
 * 15-122 Principles of Imperative Computation, Fall 2010
 * Frank Pfenning
 */

#include <stdio.h>
#include <stdlib.h>

/* xcalloc(nobj, size) returns a non-NULL pointer to
 * array of nobj objects, each of size size and
 * exits if the allocation fails.  Like calloc, the
 * array is initialized with zeroes.
 */
void* xcalloc(size_t nobj, size_t size) {
  void* p = calloc(nobj, size);
  if (p == NULL) {
    fprintf(stderr, "allocation failed\n");
    abort();
  }
  return p;
}

/* xmalloc(size) returns a non-NULL pointer to
 * an object of size size and exits if the allocation
 * fails.  Like malloc, no initialization is guaranteed.
 */
void* xmalloc(size_t size) {
  void* p = malloc(size);
  if (p == NULL) {
    fprintf(stderr, "allocation failed\n");
    abort();
  }
  return p;
}
