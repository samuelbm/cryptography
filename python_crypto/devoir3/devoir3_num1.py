from prime_utils import*
from elliptic_curve import*
from graphs import*
import numpy as np

a = 1
b = 6
p = 11
curve = elliptic_curve(a, b, p)
points = curve.compute_all_points()
nb_points = np.size(points)

print("numéro 1A)")
print_all_points(points)
path = "dev3_images/graph_num1"
plot_elliptic(curve, path)

print("numéro 1B)")
G = elliptic_point(2, 7, curve)
for k in range(1, 14):
    print("{} x {} = {}".format(k, G, G * k))
print()
print()

print("numéro 1C)")
nb = 7
PB = G * nb
print("Bill public key Pb = nb x G = {} x {} = {}".format(nb, G, PB))
print()

print("numéro 1D)")
k = 7
kG = G * k
Pm = elliptic_point(3, 6, curve)
kPB = PB * k
P = Pm + kPB
print("Ann cryptotext is Cm = [(kG), (Pm + kPb)] = [{}, {}]".format(kG, P))
print()

print("numéro 1E)")
Pm2 = P - (kG * nb)
print("Bill with its private key nb = {} can find the message".format(nb))
print("Pm = (Pm + kPb) - nb(kG) = {} - {}{}= {}".format(P, nb, kG, Pm2))
print()