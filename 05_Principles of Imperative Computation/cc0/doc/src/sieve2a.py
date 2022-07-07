def isPrime(n):
    if (n < 2): return False
    # deal with evens first (to cut time in half)
    if (n == 2): return True
    if (n % 2 == 0): return False
    # then only check odds up to the square root
    for factor in range(3, 1+int(round(n**0.5)), 2):
        if (n % factor == 0):
            return False
    return True

####################################################

###################
## test code
###################

# Before running the timing code below, let's run
# some test code to verify that the functions above
# seemingly work.  Test values are from:
# http://en.wikipedia.org/wiki/Prime-counting_function

print "Testing isPrime for correctness...",
assert(isPrime(10) == False)
assert(isPrime(17) == True)
assert(isPrime(-1) == False)
print "Passed!"
