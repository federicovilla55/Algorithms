import math

def euler_factorization(n):
    factors = []

    # Remove all even factors
    while n % 2 == 0:
        factors.append(2)
        n //= 2

    # Iterate over odd factors
    for i in range(3, int(math.sqrt(n)) + 1, 2):
        while n % i == 0:
            factors.append(i)
            n //= i

    # Add remaining factors
    if n > 2:
        factors.append(n)
    
    return factors

n = 539734379322111
factors = euler_factorization(n)
print(f"The factors of {n} are: {factors}")