/* writes return result to a file specified by env var C0_RESULT_FILE */
/* pseudocode:
 *  - first, getenv("C0_RESULT_FILE")
 *  - if result file specified open it for writing
 *  - if opened successfully, write a 0 byte to it
 *  - run _c0_main (), capture int
 *  - if result file opened successfully, write the int to it
 */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <c0runtime.h>  /* for c0_runtime_init(), c0_runtime_cleanup() */

int _c0_main();
int c0_argc;
char **c0_argv;

FILE *really_fopen(const char *filename, const char *mode,
                   char *error)
{
  FILE *f = fopen(filename, mode);
  if (f == NULL) {
    perror(error);
    exit(1);
  }
  return f;
}

void really_fwrite(const void *ptr, size_t size, size_t nitems, FILE *stream,
                    char *error) 
{
  if (fwrite(ptr, size, nitems, stream) < nitems) {
    perror(error);
    exit(1);
  }
}

void really_fclose(FILE *stream, char *error)
{
  if (fclose(stream) != 0) {
    perror(error);
    exit(1);
  }
}

int int_max() {
  return INT_MAX;
}

int int_min() {
  return INT_MIN;
}

int main(int argc, char **argv) {
  c0_argc = argc;
  c0_argv = argv;

  /* static_assert is not part of C99 standard */
  /* use manual, runtime checks to verify machine parameters */
  /* gcc must be called with -fwrapv for correct implementation
   * of two's complement arithmetic prescribed in C0
   */
  if (sizeof(int) != 4) {
    fprintf(stderr, "Error: sizeof(int) == %zd != 4\n", sizeof(int));
    exit(1);
  }
  if (~(-1) != 0 || int_max()+1 != int_min() || int_min()-1 != int_max()) {
    fprintf(stderr, "Error: not a two's complement machine\n");
  }
  if ((-1 >> 31) != -1) {
    fprintf(stderr, "Error: arithmetic right shift does not sign-extend\n");
  }

  char *filename = getenv("C0_RESULT_FILE");

  /* initialize the runtime -- possibly initializing the GC */
  c0_runtime_init();

  if (filename == NULL) {
    int x = _c0_main();
    /* if (getenv("C0_PRINT_RESULT") != NULL) */  printf("%d\n", x);
  } else {
    FILE *f = really_fopen(filename, "w", "Couldn't open $C0_RESULT_FILE");
    really_fwrite("\0", 1, 1, f, "Couldn't write to $C0_RESULT_FILE");
    int x = _c0_main();
    /* if (getenv("C0_PRINT_RESULT") != NULL) */  printf("%d\n", x);
    really_fwrite(&x, sizeof(int), 1, f, "Couldn't write to $C0_RESULT_FILE");
    really_fclose(f, "Couldn't close $C0_RESULT_FILE");
  }

  c0_runtime_cleanup();

  return 0;
}
