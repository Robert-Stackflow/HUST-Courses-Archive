/*
 * Binary search tree without balancing
 * 
 * 15-122 Principles of Imperative Computation
 * Frank Pfenning
 */

/**************************/
/* Library implementation */
/**************************/

#include <stdlib.h>
#include <stdbool.h>
#include "bst-client.h"
#include "bst.h"
#include "contracts.h"
#include "xalloc.h"

struct tree_node {
  elem data;
  struct tree_node *left;
  struct tree_node *right;
};
typedef struct tree_node tree;

struct bst_header {
  tree *root;
};

/* is_ordered(T, lower, upper) checks if all elements in T
 * are strictly in the interval (elem_key(lower),elem_key(kupper)).
 * lower = NULL represents -infinity; upper = NULL represents +infinity
 */
bool is_ordered(tree *T, elem lower, elem upper) {
  if (T == NULL) return true;
  if (T->data == NULL) return false;
  key k = elem_key(T->data);
  if (!(lower == NULL || key_compare(elem_key(lower),k) < 0))
    return false;
  if (!(upper == NULL || key_compare(k,elem_key(upper)) < 0))
    return false;
  return is_ordered(T->left, lower, T->data)
    && is_ordered(T->right, T->data, upper);
}

bool is_ordtree(tree *T) {
  /* initially, we have no bounds - pass in NULL */
  return is_ordered(T, NULL, NULL);
}

bool is_bst(bst B) {
  if (B == NULL) return false;
  return is_ordtree(B->root);
}

bst bst_new()
{
  bst B = xmalloc(sizeof(struct bst_header));
  B->root = NULL;
  ENSURES(is_bst(B));
  return B;
}

elem tree_lookup(tree *T, key k)
//@requires is_ordtree(T);
//@ensures \result == NULL || key_compare(elem_key(\result), k) == 0;
{
  REQUIRES(is_ordtree(T));
  if (T == NULL) return NULL;
  int r = key_compare(k, elem_key(T->data));
  elem retval;

  if (r == 0)
    retval = T->data;
  else if (r < 0)
    retval = tree_lookup(T->left, k);
  else {
    //@assert r > 0;
    ASSERT(r > 0);
    retval = tree_lookup(T->right, k);
  }
  ENSURES(retval == NULL || key_compare(elem_key(retval), k) == 0);
  return retval;
}

elem bst_lookup(bst B, key k)
//@requires is_bst(B);
//@ensures \result == NULL || key_compare(elem_key(\result), k) == 0;
{
  REQUIRES(is_bst(B));
  elem retval = tree_lookup(B->root, k);
  ENSURES(retval == NULL || key_compare(elem_key(retval), k) == 0);
  return retval;
}

/* tree_insert(T, e) returns the modified tree
 * this avoids some complications in case T = NULL
 */
tree *tree_insert(tree *T, elem e)
//@requires is_ordtree(T);
//@requires e != NULL;
//@ensures is_ordtree(\result);
{
  REQUIRES(is_ordtree(T));
  REQUIRES(e != NULL);
  if (T == NULL) {
    /* create new node and return it */
    T = xmalloc(sizeof(struct tree_node));
    T->data = e;
    T->left = NULL; T->right = NULL;
    ENSURES(is_ordtree(T));
    return T;
  }
  int r = key_compare(elem_key(e), elem_key(T->data));
  if (r == 0) {
    elem_free(T->data);
    T->data = e;		/* modify in place */
  }
  else if (r < 0)
    T->left = tree_insert(T->left, e);
  else //@assert r > 0;
    T->right = tree_insert(T->right, e);

  ENSURES(is_ordtree(T));
  return T;
}

void bst_insert(bst B, elem e)
//@requires is_bst(B);
//@requires e != NULL;
//@ensures is_bst(B);
{
  REQUIRES(is_bst(B));
  REQUIRES(e != NULL);
  B->root = tree_insert(B->root, e);
  ENSURES(is_bst(B));
  return;
}

void tree_free(tree *T) {
  REQUIRES(is_ordtree(T));
  if(T != NULL) {
    elem_free(T->data);
    tree_free(T->left);
    tree_free(T->right);
    free(T);
  }
  return;
}

void bst_free(bst B) {
  REQUIRES(is_bst(B));
  tree_free(B->root);
  free(B);
  return;
}

