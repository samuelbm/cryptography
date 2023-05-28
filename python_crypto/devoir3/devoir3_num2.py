from prime_utils import*
from elliptic_curve import*
from graphs import*
import numpy as np

a = 2
b = 3
p = 19
curve = elliptic_curve(a, b, p)

print("numéro 2A)")
p1 = elliptic_point(1, 5, curve)
p2 = elliptic_point(9, 3, curve)
psum = p1 + p2
print("P1 + P2 = {} + {} = {}".format(p1, p2, psum))
print()

print("numéro 2B)")
p3 = elliptic_point(9, -3, curve)
p4 = p2 + p3
print("{} + {} = {} - {} = {}".format(p2, p3, p2, -p2, p4))
print()

print("numéro 2C)")
p5 = p1 - p2
print("{} - {} = {} + {} = {}".format(p1, p2, p1, -p2, p5))

print("numéro 2D)")
k = 1
while p1*k != p2:
    k = k + 1
print("k = {} tel que k*{} = {}*{} = {}".format(k, p1, k, p1, p2))
print()

print("numéro 2E)")
points = curve.compute_all_points()
print(r"La courbe {} possède {} points".format(curve, len(points)+1))
for k in range(1, 21):
    print("k(1,5) = {}{} = {}".format(k, p1, p1*k))
print()

print_all_points(points)
path = "dev3_images/graph_num2"
plot_elliptic(curve, path)