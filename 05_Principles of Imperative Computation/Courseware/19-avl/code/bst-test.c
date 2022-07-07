/* Testing binary search trees
 * 15-122 Principles of Imperative Computation, Fall 2010
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

typedef struct elemlist_node elemlist;
struct elemlist_node {
  elem data;
  elemlist* next;
};

elemlist* elems = NULL;

elem elem_fromint(int k) {
  struct count *c = xmalloc(sizeof(struct count));
  c->id = k;
  c->count = k*k;
  
  elemlist* e = xmalloc(sizeof(struct elemlist_node));
  e->data = c;
  e->next = elems;
  elems = e;

  return c;
}

void free_all_elems() {
  while (elems != NULL) {
    elemlist* tmp = elems;
    elems = elems->next;
    free(tmp->data);
    free(tmp);
  }
}

int main() {
  printf("Testing with Lecture 1's black-box testing code\n");
  elem E1 = elem_fromint(42);
  elem E2 = elem_fromint(115);
  elem E3 = elem_fromint(42);
  elem E4 = elem_fromint(-215);
  
  bst B = bst_new();
  assert(B != NULL);
  assert(bst_lookup(B, 0) == NULL);
  assert(bst_lookup(B, 115) == NULL);
  
  bst_insert(B, elem_fromint(98));
  bst_insert(B, elem_fromint(88));
  bst_insert(B, elem_fromint(54));
  bst_insert(B, elem_fromint(67));
  bst_insert(B, elem_fromint(23));
  bst_insert(B, elem_fromint(72));
  bst_insert(B, elem_fromint(39));
  
  bst_insert(B, E1);
  assert(bst_lookup(B, 42) == E1);
  assert(bst_lookup(B, 115) == NULL);
  assert(bst_lookup(B, 0) == NULL);
  
  bst_insert(B, E2);
  assert(bst_lookup(B, 42) == E1);
  assert(bst_lookup(B, 115) == E2);
  assert(bst_lookup(B, 0) == NULL);
  
  bst_insert(B, E3);
  assert(bst_lookup(B, 42) == E3);
  assert(bst_lookup(B, 115) == E2);
  
  bst_insert(B, E4);
  assert(bst_lookup(B, -215) == E4);
  assert(bst_lookup(B, 42) == E3);

  printf("Running some sequential entries\n");
  for(int i = 0; i < 20; i = i+2) 
    bst_insert(B, elem_fromint(i));

  for(int i = 0; i > -20; i = i-2)
    bst_insert(B, elem_fromint(i));

  for (int i = -19; i < 20; i++) {
    if (i % 2 == 0) assert(bst_lookup(B, i) != NULL);
    else assert(bst_lookup(B, i) == NULL);
  }

  printf("Running some random entries\n");
  for (int i = 0; i < 500; i++) {
    bst_insert(B, elem_fromint(rand()));
  }
  
  bst_free(B);
  free_all_elems();

  printf("Tests passed!\n");
  return 0;
}
