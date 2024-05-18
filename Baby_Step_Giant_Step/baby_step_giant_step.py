import math

def baby_step_giant_step(a, b, p):
    N = math.ceil(math.sqrt(b-1))


    # Baby Steps
    steps = []
    tmp = 1
    for i in range(N):
        steps.append(tmp)
        tmp = (tmp * a) % p

    # Giant Steps
    giantStep = pow(a, -N, p)
    tmp = b
    for i in range(N):
        if tmp in steps:
            return i * N + steps.index(tmp)
        tmp = (tmp * giantStep) % p
    
    return None


if __name__ == "__main__":
    p = 263
    alpha = 14
    beta = 139
    # alpha ^ x (mod p) = beta

    print(f"Solving: {alpha} ^ x (mod {p}) = {beta}")
    res = baby_step_giant_step(alpha, beta, p)

    if res is not None:
        print(f"Solution found: discrete logarithm is x = {res}")
    else:
        print("No solution found")