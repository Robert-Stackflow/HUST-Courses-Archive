#ifndef __UNSAFE_H__
#define __UNSAFE_H__

#define C0_HAVE_CONCRETE_RUNTIME
#include <c0runtime.h>

#undef C0_RUNTIME_IMPLEMENTS_LENGTH
#include <c0runtime.h>

// Inline versions of most of the runtime for the generated code

#define c0_idiv(x,y) ((x)/(y))
#define c0_imod(x,y) ((x)%(y))
#define c0_sal(x,y) ((x)<<(y))
#define c0_sar(x,y) ((x)>>(y))

#define c0_char_equal(a,b) ((a) == (b))
#define c0_char_compare(a,b) ((a) - (b))
#define c0_string_empty() ""
#define c0_string_length(s) strlen(s)
#define c0_string_equal(a,b) (0 == c0_string_compare((a),(b)))
#define c0_string_compare(a,b) (strcmp((a),(b)))
#define c0_string_charat(s,i) ((s)[(i)])
#define c0_string_fromliteral(s) (s)

// This is a dirty trick, but we can modify the definitions used by
// the cc0 compiler in order to completely inline memory accesses.
// The trick is to give each array the type ty* rather than the type
// c0_array, which is just a generic pointer; then we can dereference
// it with the subscript operation.

#ifdef CC0

#undef cc0_array
#define cc0_array(ty) ty*

#undef cc0_array_sub
#define cc0_array_sub(ty, A, i) ((A)[(i)])

#undef cc0_deref
#define cc0_deref(ty, p) (*((ty *)p))

#endif // CC0

#endif // __UNSAFE_H__

