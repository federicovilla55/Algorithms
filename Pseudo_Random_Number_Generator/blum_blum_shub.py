import random
import math

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

def arr_bits_to_int(bits):
    return int("".join(map(str, bits)), 2)


def generate_primes(bit_length, seed):
    primes = []
    candidate = 2 ** bit_length + seed

    while len(primes) < 2:
        if is_prime(candidate):
            primes.append(candidate)
        candidate += 1
    return primes


def blum_blum_shub(seed, bit_length, num_bits):
    primes = generate_primes(bit_length, seed)
    p, q = primes[0], primes[1]
    n = p * q
    x = seed
    result = []
    for _ in range(num_bits):
        x = pow(x, 2, n)
        result.append(x & 1) 

    return result


if __name__ == "__main__":
    seed = 12345678901234
    bit_length = 64
    num_bits = 64
    random_bits = blum_blum_shub(seed, bit_length, num_bits)
    print("Random bits:", random_bits)
    print("Random value:", arr_bits_to_int(random_bits))