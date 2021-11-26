''' Python Implementation of the RSA asymmetric cryptography Algorithm.
    It was developed by Ron Rivest, Adi Shamir and Leonard Adleman in 1977.
    It is based on some Modular arithmetic theorems like the Fermat's little theorem
    and the Euler's theorem. '''

import numpy
import random

MAX_PRIME_NUMBER = 4000
MIN_PRIME_NUMBER = 53

def primesGenerator(n1):
    sieve = numpy.ones(n1//2, dtype=numpy.bool)
    for i in range(3, int(n1**0.5)+1, 2):
        if sieve[i//2]:
            sieve[i*i//2::i] = False
    l = 2*numpy.nonzero(sieve)[0][1::]+1
    randPrime = random.choice(l)
    while(randPrime <=MIN_PRIME_NUMBER):
        randPrime = random.choice(l)
    return  randPrime

def isCoprime(p, q):
    while q != 0:
        p, q = q, p%q
    return p == 1

def coprimeGenerator(phi):
    i = random.randrange(int(phi/5)) + 3
    found = False
    while(i<phi and (not found)):
        if(isCoprime(i, phi)):
            found= True
        else:
            i=i+1
    return i

def findD(e, phi):
    i=random.randrange(int(phi/e)) + 3
    found = False
    while(i<phi and (not(found))):
        if((i*e)%phi==1):
            found=True
        else:
            i=i+1
    return i

def RSA_encrypt(P, e, n):
    C = (P ** e) % n 
    return C

def RSA_decrypt(C, d, n):
    P = (C ** d) % n
    return P


if __name__ == "__main__":
    S = str(input("Insert a string you want to encrypt: "))
    Cryptresult=[]
    prime=[]
    prime.append(primesGenerator(random.randrange(MAX_PRIME_NUMBER) + MIN_PRIME_NUMBER))
    prime.append(primesGenerator(random.randrange(MAX_PRIME_NUMBER) + MIN_PRIME_NUMBER))

    n = prime[0]*prime[1]
    phi = (prime[0]-1) * (prime[1]-1)
    e = coprimeGenerator(phi)
    print("Public Key: (", n, ",", e, ")")
    d = findD(e, phi)
    print("Private Key: (", n, ",", d, ")")

    print("Cyphertext: ", end='')
    for letter in S:
        l = RSA_encrypt(ord(letter), e, n)
        Cryptresult.append(l)
        print(l, end='')

    print("\nDecrypted: ", end='')
    for el in Cryptresult:
        print(chr(RSA_decrypt(el, d, n)), end='')
    print("\n")

''' A more simple version of the program could be run
    to encrypt/decrypt numbers, in that case the S variable
    should receive an int and the for loop should be removed
    because nothing needs to be split. '''
