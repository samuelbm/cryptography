import numpy as np


def gcd(a: int, b: int) -> int:
    if b > a:
        a, b = b, a
    r = [a, b]
    k = []
    while r[-1] != 0:
        k.append(int(np.floor(r[-2] / r[-1])))
        r.append(r[-2] - k[-1] * r[-1])
    return r[-2]


def verify_coprime(a, n):
    if gcd(a, n) != 1:
        print("is not coprime, will not work")


def verify_inverse(a, x, n):
    if np.mod(a * x, n) != 1:
        print("is not good inverse, will not work")


def from_factors_to_unique_factor_and_exponent(factors):
    factor = []
    exponent = []
    for index in range(len(factors)):
        element = factors[index]
        if element in factor:
            exponent[-1] += 1
        else:
            factor.append(element)
            exponent.append(1)
    return [factor, exponent]


def factorise(n):
    factors = []
    x = n
    i = 2
    while i <= int(np.floor(np.sqrt(x))):
        if np.mod(x, i) == 0:
            factors.append(i)
            x = int(x / i)
        else:
            i = i + 1
    factors.append(x)
    factor, exponent = from_factors_to_unique_factor_and_exponent(factors)
    return [factor, exponent]


def get_phi_n(factor, exponent):
    phi_n = 1
    for index in range(len(factor)):
        pi = factor[index]
        ei = exponent[index]
        phi_n *= pi ** (ei - 1) * (pi - 1)
    return phi_n


def compute_a_power_x_mod_n(a, x, n):
    x_binary = [(x >> i) & 1 for i in range(0, 1 + int(np.floor(np.log2(x))))]
    a_power_x_mod_n = 1
    squaring = np.mod(a, n)
    for index in range(len(x_binary)):
        a_power_x_mod_n = np.mod(a_power_x_mod_n * squaring ** x_binary[index], n)
        squaring = np.mod(squaring ** 2, n)
    return a_power_x_mod_n


def compute_inverse(a, n):
    verify_coprime(a, n)
    factor, exponent = factorise(n)
    phi_n = get_phi_n(factor, exponent)
    x = compute_a_power_x_mod_n(a, phi_n - 1, n)
    verify_inverse(a, x, n)
    return x


def from_letter_to_index(letter):
    alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    return alphabet.index(letter)


def from_index_to_letter(index):
    alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    return alphabet[index]
