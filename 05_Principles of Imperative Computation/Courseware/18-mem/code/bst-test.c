/*
 * Testing binary search trees
 *
 * 15-122 Principles of Imperative Computation
 * Frank Pfenning
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "xalloc.h"
#include "contracts.h"
#include "bst.h"
#include "bst-client.h"

/******************************/
/* Client-side implementation */
/******************************/

struct count {
  int id;                   /* key */
  int count;                /* data = count */
};

int key_compare(int x, int y) {
  if (x > y) return 1;
  if (x < y) return -1;
  return 0;
}

int elem_key(struct count *c) {
  REQUIRES(c != NULL);
  return c->id;
}

void elem_free(struct count *c) {
  free(c);
  return;
}

/****************/
/* Testing code */
/****************/

elem elem_fromint(int k) {
  struct count *c = xmalloc(sizeof(struct count));
  c->id = k;
  c->count = k*k;
  return c;
}

int main() {
  {
    printf("Testing with Lecture 1's black-box testing code\n");
    elem E1 = elem_fromint(1);
    elem E2 = elem_fromint(15);
    elem E3 = elem_fromint(1);
    elem E4 = elem_fromint(-215);
    
    bst B = bst_new();
    assert(B != NULL);
    assert(bst_lookup(B, 0) == NULL);
    assert(bst_lookup(B, 15) == NULL);
    
    bst_insert(B, E1);
    assert(bst_lookup(B, 1) == E1);
    assert(bst_lookup(B, 15) == NULL);
    assert(bst_lookup(B, 0) == NULL);
    
    bst_insert(B, E2);
    assert(bst_lookup(B, 1) == E1);
    assert(bst_lookup(B, 15) == E2);
    assert(bst_lookup(B, 0) == NULL);
    
    bst_insert(B, E3);
    assert(bst_lookup(B, 1) == E3);
    assert(bst_lookup(B, 15) == E2);

    bst_insert(B, E4);
    assert(bst_lookup(B, -215) == E4);
    assert(bst_lookup(B, 1) == E3);
    
    bst_free(B);

    printf("All tests passed.\n");
  }
  return 0;
}
