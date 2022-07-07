/* CC0 helper interfacs
 *
 * Primitives used by the cc0 compiler that aren't specificed as part
 * of the cc0 runtime go here.
 * 
 * This header file uses c0runtime.h functions, but does not include
 * the c0runtime.h header because it does not know whether the runtime
 * has defined C0_RUNTIME_IMPELEMENTS_LENGTH or not.
 */

/* avoiding imprecise semantics */
#define CC0 1

// The type of an array of type ty
#define cc0_array(ty) c0_array

// Allocate a value of type ty on the heap
#define cc0_alloc(ty) ((ty*) c0_alloc(sizeof(ty)))

// Dereferences a pointer
#define cc0_deref(ty, p) (*(ty*)c0_deref((p)))

// Allocate an array of type ty with count elements
#define cc0_alloc_array(ty, count) ((cc0_array(ty)) c0_array_alloc(sizeof(ty), (count)))

// Generates an lvalue of type ty for the ith value in A
#define cc0_array_sub(ty, A, i) (*(ty*)c0_array_sub(A, i, sizeof(ty)))

// Aborts with msg if cond evaluates to false (see Wikipedia "C
// preprocessor" for this trick, or "Swallowing the Semicolon" from
// Apple's Developer docs,
// http://developer.apple.com/library/mac/#documentation/DeveloperTools/gcc-4.0.1/cpp/Swallowing-the-Semicolon.html)
#define cc0_assert(cond, msg) do { if (!(cond)) { c0_abort(c0_string_tocstr(msg)); } } while(0)

