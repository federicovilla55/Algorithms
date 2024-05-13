import math
import random

def f(x, n):
    return ((pow(x, 2, n)+1) % n)

def pollard_factorization(n):
    x = 2   # or random.randint(0, n - 1)
    y = 2
    d = 1
    while(d == 1):
        x = f(x, n)
        y = f(f(y, n), n)
        d = math.gcd(abs(x-y), n)
    
    return d

def prime_factorization(n):
    factors = []
    while n % 2 == 0:
        factors.append(2)
        n //= 2
    
    while n > 1:
        factor = pollard_factorization(n)
        factors.append(factor)
        n //= factor

    return factors

number = 7278395789028563753
# The factors of 7278395789028563753 are: 2374787263 and 3064862231
print(f"Factors of {number} are {prime_factorization(number)}")