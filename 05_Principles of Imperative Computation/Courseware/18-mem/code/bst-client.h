/*************************/
/* Client-side interface */
/*************************/

#include <string.h>

#ifndef _BST_CLIENT_H_
#define _BST_CLIENT_H_

typedef struct count *elem;
typedef int key;

key elem_key(elem e);            /* e cannot be NULL! */
int key_compare(key k1, key k2); /* returns -1, 0, or 1 */
void elem_free(elem e);

#endif
