import numpy as np
from prime_utils import*
p = 311
q = 457
e = 3943
print("p: {}, q: {}, e: {}".format(p, q, e))
print("Numéro A")
n = p*q
phi_n = get_phi_n(n)
phi_phi_n = get_phi_n(phi_n)
print("n: {}, phi_n: {}, phi_phi_n: {}".format(n, phi_n, phi_phi_n))
print("Numéro B")
d = compute_a_power_x_mod_n(e, phi_phi_n-1, phi_n)
v = np.mod(d*e, phi_n)
print("d: {}, ed mod phi_n: {}".format(d, v))
print("Numéro C")
m1 = 27873
c1 = compute_a_power_x_mod_n(m1, e, n)
d1 = compute_a_power_x_mod_n(c1, d, n)
print("m: {}, c: {}, d: {}".format(m1, c1, d1))
print("Numéro D")
c2 = 3463
d2 = compute_a_power_x_mod_n(c2, d, n)
dd2 = compute_a_power_x_mod_n(d2, e, n)
print("c: {}, d: {}, re-encrypted: {}".format(c2, d2, dd2))
