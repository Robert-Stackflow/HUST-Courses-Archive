/*
 * Interface for sort
 * 
 * 15-122 Principles of Imperative Computation, Fall 2012
 * Rob Simmons
 */

#ifndef _SORT_H_
#define _SORT_H_

typedef void* elem;
typedef int (*compare_fun)(elem e1, elem e2);

/*
These three are all equivalent:
void sort(void** A, int lower, int upper, int (*compare)(void* e1, void* e2));
void sort(elem* A, int lower, int upper, int (*compare)(elem e1, elem e2));
void sort(elem* A, int lower, int upper, compare_fun compare)
*/

void sort(elem* A, int lower, int upper, compare_fun compare);

#endif
