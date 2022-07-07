Compile with

cc0 -d selectsort.c0 sort-test.c0
./a.out

which will test sorting a random array of about 500 elements and
repeat this 10 times.  This will be slow since contracts are checked
dynamically, testing your code.

cc0 selectsort.c0 sort-time.c0
time ./a.out -n <size> -r <repeat>

times sorting a random array of size <size>, repeating <repeat> times.
Doubling the input size should roughly four-fold increase the running
time, since selecting sort has quadratic asymptotic complexity.