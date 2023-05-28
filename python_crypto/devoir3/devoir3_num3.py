from prime_utils import*
from elliptic_curve import*
from graphs import*
import numpy as np

a = 7
b = 11
p = 593899
curve = elliptic_curve(a, b, p)
m = 12345

print("Numéro 3)")
exponent = int((p + 1) / 4)
nb_points_found = 0
for j in range(10):
    x = 10 * m + j
    is_quad_residue, y1, y2 = curve.is_quadratic_residue(x)
    if is_quad_residue:
        print("j = {}, possible point found at {}".format(j, elliptic_point(x, y1, curve)))
        print("j = {}, possible point found at {}".format(j, elliptic_point(x, y2, curve)))
        nb_points_found += 2
print("{} valid points found".format(nb_points_found))
print()
