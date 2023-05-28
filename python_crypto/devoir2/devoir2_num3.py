import numpy as np
from prime_utils import*
e = 7
n = 55
factor, exponent = factorise(n)
p = factor[0]**exponent[0]
q = factor[1]**exponent[1]
phi_n = get_phi_n(n)
d = compute_inverse(e, phi_n)
m1 = 10
v1 = np.mod(d*e, phi_n)
c1 = compute_a_power_x_mod_n(m1, e, n)
d1 = compute_a_power_x_mod_n(c1, d, n)
c2 = 35
d2 = compute_a_power_x_mod_n(c2, d, n)
cc2 = compute_a_power_x_mod_n(d2, e, n)
print("e: {}, n: {}".format(e, n))
print("p: {}, q: {}, d: {}".format(p, q, d))
print("vérification ed mod phi(n): {}".format(v1))
print("numéro A")
print("m1: {}, c1: {}, d1: {}".format(m1, c1, d1))
print("numéro B")
print("c2: {}, d2: {}, ré-encryption: {}".format(c2, d2, cc2))
