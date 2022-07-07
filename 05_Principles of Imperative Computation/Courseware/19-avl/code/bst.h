/*********************/
/* Library interface */
/*********************/

#include "bst-client.h"

#ifndef _BST_H_
#define _BST_H_

typedef struct bst_header *bst;

bst bst_new();
void bst_insert(bst B, elem e); /* e cannot be NULL! */
elem bst_lookup(bst B, key k);  /* return NULL if not in tree */
void bst_free(bst B);

#endif
