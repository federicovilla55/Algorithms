import math
import random

NUM_BITS = 64

class TrustedParty:
    def __init__(self):
        self.p = self.generate_prime()
        self.a = self.generate_random_number()
        self.b = self.generate_random_number()
        self.c = self.generate_random_number()
        self.users = {}

    def generate_prime(self):
        while True:
            p = random.getrandbits(NUM_BITS)
            if p % 2 == 0:
                p += 1
            if self.is_prime(p):
                return p

    @staticmethod
    def is_prime(n, k=32):
        if n <= 3:
            return n == 2 or n == 3
        if n % 2 == 0:
            return False

        def check_primality(a, s, d, n):
            x = pow(a, d, n)
            if x == 1 or x == n - 1:
                return True
            for _ in range(s - 1):
                x = pow(x, 2, n)
                if x == n - 1:
                    return True
            return False
        
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
        
    def generate_random_number(self):
        return random.getrandbits(NUM_BITS)
    
    def generate_private_number(self, identifier):
        return (self.a + self.b * identifier) % self.p, (self.b + self.c * identifier) % self.p

    def add_user(self, nick):
        identifier = self.generate_random_number()
        self.users[nick] = [
            identifier,
            self.generate_private_number(identifier)
        ]
        return self.get_private_informations(nick)

    def get_private_informations(self, nick):
        return self.users.get(nick)
    
    def get_public_informations(self, nick):
        return self.users.get(nick)[0]
    
    def get_prime(self):
        return self.p

class User:
    def __init__(self, nickname, public, private, prime):
        self.nickname = nickname
        self.public = public
        self.private = private
        self.p = prime
        self.saved_keys = {}


    def computekey(self, nickname, public):
        key = (self.private[0] + (self.private[1] * public)) % self.p
        self.saved_keys[nickname] = key
        return key
    
    def getPublicKey(self):
        return self.public
    
    def getCommonKey(self, nickname):
        return self.saved_keys[nickname]

if __name__ == "__main__":
    trusted = TrustedParty()

    data_user1 = trusted.add_user("User1")
    data_user2 = trusted.add_user("User2")

    user1 = User("User1", data_user1[0], data_user1[1], trusted.get_prime())
    user2 = User("User2", data_user2[0], data_user2[1], trusted.get_prime())

    assert user1.computekey("User2", user2.getPublicKey()) == user2.computekey("User1", user1.getPublicKey()), "Error while generating or exchanging keys"

    print("Key exchanged: ", user1.getCommonKey("User2"))