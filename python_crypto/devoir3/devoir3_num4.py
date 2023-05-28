from prime_utils import*
from elliptic_curve import*
from graphs import*
import numpy as np


print("Numéro A)")
n = 3900353
a = 1
b = n-1
curve = elliptic_curve(a, b, n)
G = elliptic_point(1, 1, curve)

p = G
for i in range(1, 14):
    p = p * i
    print(i, p)

p = 1109
q = int(n/p)
print()
print("n = {} = p*q = {}*{}, p = {}, q = {}".format(n, p, q, p, q))
print()


def p_minus_1_algo(n, M):
    x = 2
    total = 500
    while x<total:
        axn = compute_a_power_x_mod_n(x, M, n)
        g = gcd(axn - 1, n)
        if g > 1:
            return g
            break
        x += 1

print("Numéro B)")
p = p_minus_1_algo(n, 40)
q = int(n/p)
print("Pollard rho-1 factorisation yield: p={}, q={} from composite number n={}".format(p, q, n))
print("factorisation de p-1 = {}: {}".format(p-1, factorise(p-1)))
print("factorisation de q-1 = {}: {}".format(q-1, factorise(q-1)))
print()


