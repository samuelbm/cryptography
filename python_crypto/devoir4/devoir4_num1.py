import random

from utils import *
from utils_performance import *
import numpy as np


def test(n):
    print("Pour n={}".format(n))
    count0 = 0
    factors0 = []
    while np.mod(n, 2) == 0:
        count0 = count0 + 1
        factors0.append(2)
        n = int(n / 2)
    factors1, count1 = method_factorisation(n)
    factors2, count2 = method_elliptic_curve(n)
    factors3, count3 = method_pollard(n, 1)
    factors1.extend(factors0)
    factors2.extend(factors0)
    factors3.extend(factors0)
    factors1.sort()
    factors2.sort()
    factors3.sort()
    if count0:
        print("{} facteurs triviales de 2 trouvés".format(count0))
    #print("Méthode factorisation:     {}, number of steps: {}".format(factors1, count1 + count0))
    #print("Méthode courbe elliptique: {}, number of steps: {}".format(factors2, count2 + count0))
    #print("Méthode pollard:           {}, number of steps: {}".format(factors3, count3 + count0))
    print("Méthode factorisation:     {}".format(factors1))
    print("Méthode courbe elliptique: {}".format(factors2))
    print("Méthode pollard:           {}".format(factors3))


def method_factorisation(n):
    return factorise_performance(n, 0)


def method_elliptic_curve(n):
    count = 0
    factors = []
    is_prime, count = is_prime_with_millerrabin_performance(n, count)
    if is_prime:
        factors.append(n)
    else:
        curve = elliptic_curve(1, n - 1, n)
        G = elliptic_point(1, 1, curve)
        p = G
        i = 1
        while curve.divisor == 1:
            p = p * i
            i = i + 1
        f1 = curve.divisor
        f2 = int(n / f1)
        factors1, count1 = method_elliptic_curve(f1)
        factors2, count2 = method_elliptic_curve(f2)
        factors.extend(factors1)
        factors.extend(factors2)
        count += curve.count + count1 + count2
    return factors, count


def method_pollard(n, start):
    count = 0
    factors = []
    is_prime, count = is_prime_with_millerrabin_performance(n, count)
    if is_prime:
        factors.append(n)
    else:
        x = 2
        y = 2
        d = 1
        while d == 1:
            x = g(x, n, start)
            y = g(y, n, start)
            y = g(y, n, start)
            d = gcd(np.abs(x - y), n)
        if d == n:
            factorsx, countx = method_pollard(n, start + 1)
            factors.extend(factorsx)
            count += countx
        else:
            f1 = d
            f2 = int(n / f1)
            factors1, count1 = method_pollard(f1, start)
            factors2, count2 = method_pollard(f2, start)
            count = count + count1 + count2
            factors.extend(factors1)
            factors.extend(factors2)
    return factors, count


def g(x, n, start):
    y = np.mod(x ** 2 + start, n)
    return y


def is_prime_with_millerrabin_performance(n, count):
    primes = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67,
              71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173,
              179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281,
              283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409,
              419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541]
    for prime in primes:
        if n == 2:
            return True
        else:
            a_power_x_modulo_n, count = compute_a_power_x_mod_n_performance(prime, n - 1, n, count)
            if a_power_x_modulo_n != 1 and n > prime:
                return False, count  # for sure
    return True, count  # probably


# print("Numéro 1A")
# test(1548)
# print()
#
# print("Numéro 1B")
# test(9763)
# print()
#
# print("Numéro 1C")
# test(3110657)
# print()
#
# print("Numéro 1D")
# test(5167849)
# print()
#
# print("Numéro 1E")
# test(10444817)
# print()

x = 272215255892494994533594579140612895860
factors, count = method_pollard(x, 1)
print(factors)

