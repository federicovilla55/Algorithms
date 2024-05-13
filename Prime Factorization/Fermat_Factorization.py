import math

def fermat_factorization(num):
    # Banal case: odd value
    if num % 2 == 0:
        return 2, n//2
    
    a = math.ceil(math.sqrt(num))
    b = a**2 - num

    while math.isqrt(b)**2 != b:
        a += 1
        b = a**2 - num

    b = math.isqrt(b)
    
    return a+b, a-b

#n = 1761460793
n = 5397349379528157713
factor1, factor2 = fermat_factorization(n)
print(f"The factors of {n} are: {factor1} and {factor2}")
# The factors of 5397349379528157713 are: 2403226181 and 2245876573