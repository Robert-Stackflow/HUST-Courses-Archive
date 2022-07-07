For compilation with debugging (like cc0 -d) use:

Unsafe code:
% gcc -Wall -Wextra -Werror -std=c99 -pedantic -g -DDEBUG xalloc.c unsafe-inclass.c

BSTs from lecture:
% gcc -Wall -Wextra -Werror -std=c99 -pedantic -g -DDEBUG xalloc.c bst.c bst-test.c

For compilation without debugging (like cc0) use:

BSTs from lecture:
% gcc -Wall -Wextra -Werror -std=c99 -pedantic -g xalloc.c bst.c bst-test.c

