/*
 * AVL Trees
 * 
 * 15-122 Principles of Imperative Computation */

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
  unsigned int height;
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

/* Get the stored tree height */
static inline int height(tree *T) {
  return T == NULL ? 0 : T->height;
}

bool is_specified_height(tree *T) {
  if (T == NULL) return true;
  int h = T->height;
  int hl = height(T->left);
  int hr = height(T->right);
  if (hl > hr) {
    if (!(h == hl + 1)) return false;
  } else {
    if (!(h == hr + 1)) return false;
  } 
  return is_specified_height(T->left) && is_specified_height(T->right);
} 

bool is_balanced(tree *T) {
  if (T == NULL) return true;
  if (height(T->left) < height(T) - 2) return false;
  if (height(T->right) < height(T) - 2) return false;
  return is_balanced(T->left) && is_balanced(T->right);
}

bool is_avl(tree *T) {
  return is_ordtree(T) && is_specified_height(T) && is_balanced(T);
}

bool is_bst(bst B) {
  if (B == NULL) return false;
  return is_avl(B->root);
}

bst bst_new()
{
  bst B = xmalloc(sizeof(struct bst_header));
  B->root = NULL;
  ENSURES(is_bst(B));
  return B;
}

/* fix_height(T) calculates the height of T and stores it in
 * T->height, assuming the height of the subtrees is correct. */
void fix_height(tree *T) {
  REQUIRES(T != NULL);
  REQUIRES(is_specified_height(T->left) && is_specified_height(T->right));
  int hl = height(T->left);
  int hr = height(T->right);
  T->height = (hl > hr ? hl+1 : hr+1);
  ENSURES(is_specified_height(T));
}

tree *rotate_right(tree *T) {
  REQUIRES(is_ordtree(T));
  REQUIRES(T != NULL && T->left != NULL);
  REQUIRES(is_specified_height(T->left) && is_specified_height(T->right));
  tree *root = T->left;
  T->left = root->right;
  root->right = T;
  fix_height(root->right);	/* must be first */
  fix_height(root);
  ENSURES(is_ordtree(root));
  REQUIRES(is_specified_height(T));
  ENSURES(root != NULL && root->right != NULL);
  return root;
}

tree *rotate_left(tree *T) {
  REQUIRES(is_ordtree(T));
  REQUIRES(T != NULL && T->right != NULL);
  REQUIRES(is_specified_height(T->left) && is_specified_height(T->right));
  tree *root = T->right;
  T->right = root->left;
  root->left = T;
  fix_height(root->left);	/* must be first */
  fix_height(root);
  ENSURES(is_ordtree(root));
  REQUIRES(is_specified_height(T));
  ENSURES(root != NULL && root->left != NULL);
  return root;
}

tree *rebalance_left(tree *T) {
  REQUIRES(T != NULL);
  REQUIRES(is_avl(T->left) && is_avl(T->right));
  REQUIRES(T->left != NULL);

  tree *l = T->left;
  tree *r = T->right;
  int hl = height(l);
  int hr = height(r);
  if (hl > hr+1) {
    ASSERT(hl == hr+2);
    if (height(l->left) > height(l->right)) {
      ASSERT(height(l->left) == hr+1);
      T = rotate_right(T);
      ASSERT(height(T) == hr+2);
    } else {
      ASSERT(height(l->right) == hr+1);
      /* double rotate right */
      T->left = rotate_left(T->left);
      T = rotate_right(T);
      ASSERT(height(T) == hr+2);
    }
  } else { 
    ASSERT(!(hl > hr+1));
    fix_height(T);
  }
  ENSURES(is_avl(T));
  return T;
}

tree *rebalance_right(tree *T) {
  REQUIRES(T != NULL);
  REQUIRES(is_avl(T->left) && is_avl(T->right));
  REQUIRES(T->right != NULL);

  tree *l = T->left;
  tree *r = T->right;
  int hl = height(l);
  int hr = height(r);
  if (hr > hl+1) {
    ASSERT(hr == hl+2);
    if (height(r->right) > height(r->left)) {
      ASSERT(height(r->right) == hl+1);
      T = rotate_left(T);
      ASSERT(height(T) == hl+2);
    } else {
      ASSERT(height(r->left) == hl+1);
      /* double rotate left */
      T->right = rotate_right(T->right);
      T = rotate_left(T);
      ASSERT(height(T) == hl+2);
    }
  } else { 
    ASSERT(!(hr > hl+1));
    fix_height(T);
  }
  ENSURES(is_avl(T));
  return T;
}

/* tree_insert(T, e) returns the modified tree
 * this avoids some complications in case T = NULL
 * 
 * Additional postcondition: Given a tree of height h, the height of
 * the returned tree is either h or h+1. */
tree *tree_insert(tree *T, elem e)
{
  REQUIRES(is_ordtree(T));
  REQUIRES(is_specified_height(T));
  REQUIRES(e != NULL);

  if (T == NULL) { 
    /* create new leaf with the data e */
    T = xmalloc(sizeof(struct tree_node));
    T->data = e;
    T->height = 1;
    T->left = NULL; 
    T->right = NULL;
  } else {
    int r = key_compare(elem_key(e), elem_key(T->data));
    if (r == 0) {
      T->data = e;		/* modify in place */
    } else if (r < 0) {
      T->left = tree_insert(T->left, e);
      T = rebalance_left(T);    /* also fixes height */
    } else {
      ASSERT(r > 0);
      T->right = tree_insert(T->right, e);
      T = rebalance_right(T);   /* also fixes height */
    }
  }

  ENSURES(is_ordtree(T));
  ENSURES(is_specified_height(T));
  return T;
}

void bst_insert(bst B, elem e)
{
  REQUIRES(is_bst(B));
  REQUIRES(e != NULL);
  B->root = tree_insert(B->root, e);
  ENSURES(is_bst(B));
  return;
}

elem tree_lookup(tree *T, key k)
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
    ASSERT(r > 0);
    retval = tree_lookup(T->right, k);
  }
  ENSURES(retval == NULL || key_compare(elem_key(retval), k) == 0);
  return retval;
}

elem bst_lookup(bst B, key k)
{
  REQUIRES(is_bst(B));
  elem retval = tree_lookup(B->root, k);
  ENSURES(retval == NULL || key_compare(elem_key(retval), k) == 0);
  return retval;
}

void tree_free(tree *T) {
  REQUIRES(is_ordtree(T));
  if(T != NULL) {
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

