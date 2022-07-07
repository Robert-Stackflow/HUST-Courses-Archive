/* Selection Sort
 *
 * Principles of Imperative Computation, Fall 2012
 * Frank Pfenning
 */

#include <stdlib.h>
#include <assert.h>
#include "sort.h"

void swap(elem* A, int i, int j)
{
  assert(A != NULL);
  elem tmp = A[i];
  A[i] = A[j];
  A[j] = tmp;
  return;
}

int min_index(elem* A, int lower, int upper, compare_fun elem_compare)
{
  assert(A != NULL && lower < upper && elem_compare != NULL);
  int m = lower;
  elem min = A[lower];
  for (int i = lower+1; i < upper; i++)
    if ((*elem_compare)(A[i], min) < 0) {
      m = i;
      min = A[i];
    }
  return m;
}

void sort(elem* A, int lower, int upper, compare_fun elem_compare)
{
  assert(A != NULL && lower <= upper && elem_compare != NULL);
  for (int i = lower; i < upper; i++)
    {
      int m = min_index(A, i, upper, elem_compare);
      swap(A, i, m);
    }
  return;
}
