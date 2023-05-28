import numpy as np
from prime_utils import *

def string4(x: int) -> str:
    repeat = 3 - int(np.floor(np.log10(x)))
    return "0" * repeat + str(x)
p = 83
q = 59
e = 73
n = p * q
phi_n = get_phi_n(n)
d = compute_inverse(e, phi_n)
v1 = np.mod(d * e, phi_n)
print("p: {}, q: {}, e: {}, d: {}, n: {}, phi_n: {}, ed mod phi(n): {}".format(p, q, e, d, n, phi_n, v1))
print("Numéro A")
print("d: {}".format(d))
print("Numéro B")
messages = [385, 856, 237, 649]
for i, message in enumerate(messages):
    iscoprime = gcd(message, n) == 1
    ciphertext = compute_a_power_x_mod_n(message, e, n)
    decrypted = compute_a_power_x_mod_n(ciphertext, d, n)
    print("m{}: {}, c{}: {}, d{}: {}, is (m, n) coprimes: {}".format(i + 1, str(message), i + 1, string4(ciphertext),
                                                                     i + 1, str(decrypted), iscoprime))
print("Numéro C")
ciphertexts = [132, 693, 354]
for i, ciphertext in enumerate(ciphertexts):
    iscoprime = gcd(ciphertext, n) == 1
    decrypted = compute_a_power_x_mod_n(ciphertext, d, n)
    reencrypted = compute_a_power_x_mod_n(decrypted, e, n)
    print(
        "c{}: {}, d{}: {}, reencrypted{}: {}, is (m, n) coprimes: {}".format(i + 1, ciphertext, i + 1, decrypted, i + 1,
                                                                             reencrypted, iscoprime))
