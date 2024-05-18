import random

def check_primality(a, s, d, n):
    x = pow(a, d, n)
    if x == 1:
        return True
    for _ in range(s - 1):
        if x == (n - 1):
            return True
        x = pow(x, 2, n)
    return x == (n - 1)


def is_prime(n, number_of_rounds=64):
    if n <= 3:
        return (n == 2 or n == 3)
    if n % 2 == 0:
        return False
    
    s = 0
    d = n - 1
    while d % 2 == 0:
        d //= 2
        s += 1
    for _ in range(number_of_rounds):
        a = random.randrange(2, n - 1)
        if not check_primality(a, s, d, n):
            return False
    return True

if __name__ == "__main__":
    print(is_prime(5397349379528157713)) # False
    print(is_prime(2403226181)) # True
    print(is_prime(2245876573)) # True