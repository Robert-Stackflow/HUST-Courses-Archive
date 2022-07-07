# Sieve of Eratosthenes
# More complete example, showing one reason why we might
# care to use the sieve rather than the simple isPrime function
# we already learned how to write.

# We'll be computing the prime counting function, pi(n):
# See http://en.wikipedia.org/wiki/Prime-counting_function

# We'll do it two different ways:  once using the simple isPrime
# function, and again using the siece.  We'll time each way
# and see how it goes.

####################################################

###################
## sieve(n)
###################

# This function returns a list of prime numbers
# up to n (inclusive), using the Sieve of Eratosthenes.
# See http://en.wikipedia.org/wiki/Sieve_of_Eratosthenes

def sieve(n):
    isPrime = [ True ] * (n+1) # assume all are prime to start
    primes = [ ]
    for prime in range(2, n+1):
        if (isPrime[prime] == True):
            # we found a prime, so add it to our result
            primes += [prime]
            # and mark all its multiples as not prime
            for multiple in range(2*prime, n+1, prime):
                isPrime[multiple] = False
    return primes
    
# Here we will use the sieve to compute the prime
# counting function.  The sieve will return a list
# of all the primes up to n, so the prime counting
# function merely returns the length of this list!

def piUsingSieve(n):
    return len(sieve(n))

###################
## piUsingisPrime(n)
###################

# Here we will use the isPrime function to compute
# the prime counting function.

def piUsingIsPrime(n):
    primeCount = 0
    for n in range(n+1):
        if (isPrime(n)):
            primeCount += 1
    return primeCount

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

print "First testing functions for correctness...",
assert(piUsingSieve(10) == 4)
assert(piUsingIsPrime(10) == 4)
assert(piUsingSieve(100) == 25)
assert(piUsingIsPrime(100) == 25)
assert(piUsingSieve(1000) == 168)
assert(piUsingIsPrime(1000) == 168)
print "Passed!"

####################################################

###################
## timing code
###################

# Finally we can time each version for a large value of n
# and compare their runtimes

import time

n = 1000 * 1000  # one million

print "***************"
print "Timing piUsingIsPrime(" + str(n) + "):"
startTime = time.time()
result1 = piUsingIsPrime(n)
endTime = time.time()
time1 = endTime - startTime
print "   result = " + str(result1)
print "   time = " + str(time1) + " sec"

print "***************"
print "Timing piUsingSieve(" + str(n) + "):"
startTime = time.time()
result2 = piUsingSieve(n)
endTime = time.time()
time2 = endTime - startTime
print "   result = " + str(result2)
print "   time = " + str(time2) + " sec"

print "***************"
print "Comparison:"
print "   Same result: " + str(result1 == result2)
print "   (time of isPrime) / (time of sieve) = " + str(time1 / time2)
print "And this only gets worse, and quickly, for larger values of n."
