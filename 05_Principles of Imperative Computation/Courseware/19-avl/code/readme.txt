For compilation with debugging (like cc0 -d) use:
gcc -Wall -Wextra -Werror -std=c99 -pedantic -g -DDEBUG xalloc.c avl.c bst-test.c

For compilation without debugging (like cc0) use:
gcc -Wall -Wextra -Werror -std=c99 -pedantic -g xalloc.c avl.c bst-test.c
