import random
import math

class RSA:
    KEY_BIT_SIZE = 1024

    @staticmethod
    def generate_prime(bits):
        while True:
            p = random.getrandbits(bits)
            if p % 2 == 0:
                p += 1
            if RSA.is_prime(p):
                return p

    @staticmethod
    # Miller-Rabin (with 12 rounds of testing)
    def is_prime(n, k=12):
        if n <= 3:
            return n == 2 or n == 3
        if n % 2 == 0:
            return False

        # Miller-Rabin primality test
        def check_primality(a, s, d, n):
            x = pow(a, d, n)
            if x == 1:
                return True
            for _ in range(s - 1):
                if x == n - 1:
                    return True
                x = pow(x, 2, n)
            return x == n - 1
        
        s = 0
        d = n - 1
        while d % 2 == 0:
            d //= 2
            s += 1
        for _ in range(k):
            a = random.randrange(2, n - 1)
            if not check_primality(a, s, d, n):
                return False
        return True

    @staticmethod
    def generate_coprime(phi):
        while True:
            e = random.randrange(2, phi)
            if math.gcd(e, phi) == 1:
                return e

    # Extended Euclidean Algorithm to compute modular inverse
    @staticmethod
    def extended_gcd(a, b):
        prev_x, x = 0, 1
        prev_y, y = 1, 0
        while a != 0:
            quotient, remainder = b // a, b % a
            prev_x, x = x, prev_x - quotient * x
            prev_y, y = y, prev_y - quotient * y
            b, a = a, remainder
        gcd = b
        return gcd, prev_x, prev_y


    @staticmethod
    def mod_inverse(a, m):
        gcd, x, y = RSA.extended_gcd(a, m)
        if gcd != 1:
            raise ValueError('Error: modular inverse does not exist')
        return x % m


    # Square and Multiply
    @staticmethod
    def mod_exp(base, exp, mod):
        result = 1
        base = base % mod
        while exp > 0:
            if exp % 2 == 1:
                result = (result * base) % mod
            exp = exp >> 1
            base = (base * base) % mod
        return result

    @staticmethod
    def RSA_encrypt(P, e, n):
        return RSA.mod_exp(P, e, n)

    @staticmethod
    def RSA_decrypt(C, d, n):
        return RSA.mod_exp(C, d, n)

if __name__ == "__main__":
    S = str(input("Insert a string to encrypt: "))
    
    prime1 = RSA.generate_prime(RSA.KEY_BIT_SIZE)
    prime2 = RSA.generate_prime(RSA.KEY_BIT_SIZE)
    n = prime1 * prime2
    phi = (prime1 - 1) * (prime2 - 1)
    
    e = RSA.generate_coprime(phi)
    print("Public Key: (", n, ",", e, ")")

    d = RSA.mod_inverse(e, phi)
    print("Private Key: (", n, ",", d, ")")
    
    print("Cyphertext: ", end='')
    for letter in S:
        l = RSA.RSA_encrypt(ord(letter), e, n)
        print(l, end='')
    
    print("\nDecrypted: ", end='')
    for letter in S:
        l = RSA.RSA_decrypt(RSA.RSA_encrypt(ord(letter), e, n), d, n)
        print(chr(l), end='')
    print("\n")