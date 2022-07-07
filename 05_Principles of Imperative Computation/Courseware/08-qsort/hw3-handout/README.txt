Programming 3 (DosLingos)

Files you won't modify:
   lib/arrayutil.c0     - A version of arrayutil.c0 for strings
   lib/readfile.c0      - File reading library (Part 2, page 4)
   lib/stringsearch.c0  - String searching library (Part 2, pages 4-5)
   sort.c0              - Example of a correct sort() and sortcopy()
   sort-awful.c0        - Example of an incorrect sort() 
   sortcopy-awful.c0    - Example of an incorrect sortcopy()

Files that don't exist yet:
   duplicates.c0        - Code for part 1, tasks 1-3
   duplicates-test.c0   - Testing duplicates.c0 (Optional, highly recommended)
   doslingos.c0         - Code for part 2, task 4
   doslingos-test.c0    - Testing doslingos.c0 (Optional, highly recommended)
   sort-test.c0         - Testing the sort() function
   sortcopy-test.c0     - Testing the sortcopy() function

Data: (described on page 4 of the handout)
   texts/news_vocab_sorted.txt 
   texts/scotttweet.txt
   texts/twitter_1k.txt
   texts/twitter_200k.txt

   You can create more data files if you would like to use them in
   your tests: just hand these in along with your other files.

==========================================================

Loading the readfile.c0 library in coin to play with it:
   % coin lib/readfile.c0

Loading the stringsearch.c0 library in coin to play with it:
   % coin lib/stringsearch.c0

Compiling duplicates.c0 and tests (Part 1):
   % cc0 -d -w -o duplicates lib/*.c0 duplicates.c0 duplicates-test.c0
   % ./duplicates
 
Compiling doslingos.c0 and tests (Part 2):
   % cc0 -d -w -o doslingos lib/*.c0 duplicates.c0 doslingos.c0 doslingos-test.c0
   % ./doslingos 
   
Compiling sort tests against the correct implementations (Part 3):
   % cc0 -d -w lib/*.c0 sort.c0 sort-test.c0
   % ./a.out
      (This should run successfully)
 
   % cc0 -d -w lib/*.c0 sort.c0 sortcopy-test.c0
   % ./a.out
      (This should run successfully)

Compiling sort tests against the  implementations (Part 3):
   % cc0 -d -w lib/*.c0 sort-awful.c0 sort-test.c0
   % ./a.out
      (This should cause an assertion to fail)

   % cc0 -d -w lib/*.c0 sortcopy-awful.c0 sortcopy-test.c0
   % ./a.out
      (This should cause an assertion to fail)

==========================================================

Submitting with Andrew handin script:
   % handin hw3 duplicates.c0 duplicates-test.c0 doslingos.c0 doslingos-test.c0 sort-test.c0 sortcopy-test.c0

Creating a tarball to submit with Autolab web interface:
   % tar -czvf hw3sol.tgz duplicates.c0 duplicates-test.c0 doslingos.c0 doslingos-test.c0 sort-test.c0 sortcopy-test.c0

On autolab: https://autolab.cs.cmu.edu/15122-f13/doslingos
