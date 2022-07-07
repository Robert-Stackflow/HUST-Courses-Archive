Programming 4 (Clac)

Files you won't modify:
   lib/stacks_int.c0     - Stacks containing integers
   lib/queues_string.c0  - Queues containing strings
   lib/tokenize.c0       - Library for populating queues of strings
   clac-main.c0          - Runs clac

Files you will modify:
   clac.c0               - Clac interpreter
   clac-test.c0          - Testing the clac implementation (Optional)

Data:
   def/demo-fail.clac    - An example program that should call to error()
   def/demo-print.clac   - An example program that should print things out

==========================================================

The code that you're given will already compile and pass the given
tests in clac-test.c0.

Running the reference implementation of the Claculator (Andrew Linux only):
   % clac-ref def/demo-print.clac
   clac>> 8 5 4 - + dup
   clac>> print print
   clac>> quit

Compiling and running the Claculator:
   % cc0 -d -w -o claculator lib/*.c0 clac.c0 clac-main.c0
   % ./claculator
   % ./claculator def/demo-print.clac

Testing your Clac implementation:
   % cc0 -d -w -o clac-test lib/*.c0 clac.c0 clac-test.c0
   % ./clac-test
   % ./clac-test err1
   % ./clac-test err2
   % ./clac-test err3
   ...

==========================================================

Submitting with Andrew handin script:
   % handin hw4 clac.c0 bonus.clac bonus.txt

Creating a tarball to submit with Autolab web interface:
   % tar -czvf hw4sol.tgz clac.c0 bonus.clac bonus.txt

On autolab: https://autolab.cs.cmu.edu/15122-f13/clac
